#include <WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>
#include <HTTPClient.h>
#include "config.h"

// Pinos
#define SS_PIN       2
#define RST_PIN      10
#define LED_BRANCO   8
#define LED_VERMELHO 9
#define SERVO_PIN    6

//UIDS
const String UID_TAG = "2B879602";
const String UID_CARTAO = "0347CAFD";

MFRC522 rfid(SS_PIN, RST_PIN);
Servo servoFechadura;

void conectarWifi() {
  Serial.print("Conectando ao WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int tentativas = 0;
  while (WiFi.status() != WL_CONNECTED && tentativas < 20) {
    delay(500);
    Serial.print(".");
    tentativas++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✓ WiFi conectado!");
    Serial.print("  IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("  RSSI (sinal): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
  } else {
    Serial.println("\n✗ Falha ao conectar no WiFi");
  }
}

String obterUID() {
  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) uid += "0";
    uid += String(rfid.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();
  return uid;
}

void testarServo() {
  Serial.println("Testando servo...");
  servoFechadura.write(90);
  delay(1000);
  servoFechadura.write(0);
  delay(1000);
  Serial.println("✓ Servo OK");
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n=== TESTE DE HARDWARE ===");

  pinMode(LED_BRANCO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  digitalWrite(LED_BRANCO, HIGH);
  digitalWrite(LED_VERMELHO, HIGH);
  delay(800);
  digitalWrite(LED_BRANCO, LOW);
  digitalWrite(LED_VERMELHO, LOW);
  Serial.println("✓ LEDs OK");

  conectarWifi();

  // Servo
  servoFechadura.attach(SERVO_PIN);
  servoFechadura.write(0);
  testarServo();

  // RFID
  SPI.begin(3, 5, 4, 2);  // SCK, MISO, MOSI, SS
  rfid.PCD_Init();
  delay(100);
  byte versao = rfid.PCD_ReadRegister(MFRC522::VersionReg);
  if (versao == 0x91 || versao == 0x92) {
    Serial.print("✓ RFID RC522 OK (versão 0x");
    Serial.print(versao, HEX);
    Serial.println(")");
  } else {
    Serial.print("✗ RFID não detectado (versão 0x");
    Serial.print(versao, HEX);
    Serial.println(") — verifique a fiação SPI");
  }

  Serial.println("\n=== Aproxime um cartão para testar ===");
}

void registrarAcesso(String uid, bool liberado) {

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Sem WiFi. Não foi possível registrar no Supabase.");
    return;
  }

  HTTPClient http;

  http.begin(SUPABASE_URL);

  http.addHeader("Content-Type", "application/json");
  http.addHeader("apikey", SUPABASE_KEY);
  http.addHeader("Authorization", String("Bearer ") + SUPABASE_KEY);
  http.addHeader("Prefer", "return=minimal");

  String json =
    "{\"uid\":\"" + uid +
    "\",\"liberado\":" + (liberado ? "true" : "false") +
    "}";

  int httpResponseCode = http.POST(json);

  Serial.print("Supabase HTTP Code: ");
  Serial.println(httpResponseCode);

  if (httpResponseCode > 0) {
    Serial.println("Registro enviado com sucesso.");
  } else {
    Serial.print("Erro ao enviar: ");
    Serial.println(http.errorToString(httpResponseCode));
  }

  http.end();
}

void loop() {
  // Mantém WiFi vivo e mostra status a cada 10s
  static unsigned long ultimo = 0;
  if (millis() - ultimo > 10000) {
    ultimo = millis();
    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("[WiFi OK] IP: ");
      Serial.print(WiFi.localIP());
      Serial.print(" | RSSI: ");
      Serial.print(WiFi.RSSI());
      Serial.println(" dBm");
    } else {
      Serial.println("[WiFi] Desconectado — tentando reconectar...");
      WiFi.reconnect();
    }
  }

  // Verifica cartão
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  String uid = obterUID();

  Serial.print("UID lido: ");
  Serial.println(uid);

  if (uid == UID_TAG || uid == UID_CARTAO) {

    Serial.println("=== ACESSO LIBERADO ===");

    digitalWrite(LED_BRANCO, HIGH);
    digitalWrite(LED_VERMELHO, LOW);

    servoFechadura.write(90);

    delay(3000);

    registrarAcesso(uid, true);

    servoFechadura.write(0);
    digitalWrite(LED_BRANCO, LOW);

  } else {

    Serial.println("=== ACESSO NEGADO ===");

    digitalWrite(LED_VERMELHO, HIGH);

    delay(3000);

    registrarAcesso(uid, false);

    digitalWrite(LED_VERMELHO, LOW);
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}