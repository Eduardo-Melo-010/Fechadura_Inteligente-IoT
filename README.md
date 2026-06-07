# 🔐 Fechadura com RFID

Sistema de controle de acesso utilizando ESP32-C3, leitor RFID RC522 e servo motor, com dashboard web em tempo real integrado ao Supabase.

## 🔗 Links de Acesso

| Recurso | Link |
|---|---|
| Repositório GitHub | [github.com/Eduardo-Melo-010/Fechadura_Inteligente-IoT](https://github.com/Eduardo-Melo-010/Fechadura_Inteligente-IoT) |
| Dashboard (deploy) | [fechadura.netlify.app](https://fechadura.netlify.app) |
| Apresentação (slides) | [https://canva.link/m085wwr8tr9r6zr](https://canva.link/m085wwr8tr9r6zr) |
| Link do Wokwi | [https://wokwi.com/projects/46612028162286796](https://wokwi.com/projects/466139587252499457) |

## 👥 Equipe

| Nome |
|---|
| EDUARDO JOSÉ SILVA DE MELO | 
| HEITOR LEONARDO NOVAES PINTINO | 
| ISABELLA GEOVANA DO NASCIMENTO SILVA | 
| JOÃO VICTOR LUIZ DE MORAES CHAGAS |
| RENATHA ALVES DE LIMA |
| SÁVIO TORRES DA SILVA LIRA |
| VANESSA TREZENA DE AMORIM |


**Curso:** Análise e Desenvolvimento de Sistemas — 4º Período
**Faculdade:** Senac/PE | **Orientador:** Professor Arnott Caiado | 

## 📋 Sobre o Projeto

Este trabalho apresenta um sistema de controle de acesso físico a armários, baseado em IoT, utilizando um microcontrolador ESP32-C3 e um leitor RFID RC522. O sistema verifica se um cartão ou tag RFID está autorizado e aciona um servo motor para liberar ou negar o acesso ao armário. Todas as tentativas de acesso são registradas automaticamente em um banco de dados na nuvem Supabase (PostgreSQL) e monitoradas em tempo real por meio de um dashboard web desenvolvido em Angular e publicado no Netlify.

## 🌐 Abstract

This work presents an IoT-based physical access control system for classroom and laboratory lockers, developed using an ESP32-C3 microcontroller and an RC522 RFID reader. Upon detecting an RFID card or tag, the system verifies the UID against an authorized list and actuates a servo motor to grant or deny access. Each access attempt whether authorized or not is automatically transmitted via HTTPS to a Supabase (PostgreSQL) cloud database and monitored in real time through a web dashboard built with Angular 21 and deployed on Netlify. The proposed solution addresses the lack of automated traceability in academic environments, offering a low-cost, scalable, and secure alternative to conventional lock systems.

---

## 🛠️ Materiais Utilizados

| Componente | Descrição |
|---|---|
| ESP32-C3 Super Mini | Microcontrolador principal |
| RFID RC522 | Leitor de cartões RFID |
| Servo SG90 | Motor para acionamento da fechadura |
| MB102 | Fonte de alimentação para protoboard |
| 2 LEDs | Indicadores de acesso liberado/negado |
| Jumpers | Conexões entre componentes |
| Cabo USB-A + USB-C | Alimentação e programação do ESP32 |

---

## 🏗️ Arquitetura do Projeto

```
Projeto-fechadura-com-RFID/
├── Arduino/          # Código do ESP32 (C++)
├── Front-Fechadura/
│   └── controle-acesso-rfid/   # Dashboard Angular
└── README.md
```
---

### Arquitetura lógica (camadas)

| Camada | Componentes |
|---|---|
| Percepção (borda) | ESP32-C3 Super Mini + RC522 (SPI) + Servo SG90 + LEDs |
| Rede | Wi-Fi 2.4 GHz — HTTP REST (HTTPS) com payload JSON |
| Nuvem / Aplicação | Supabase (PostgreSQL + API REST) + Angular 21 + Netlify |

> O dashboard Angular consome a API REST do Supabase via polling a cada 3 segundos, exibindo o histórico de acessos em tempo real.

---

### Diagrama de arquitetura

>  <img width="1007" height="563" alt="image" src="https://github.com/user-attachments/assets/ff8d6d23-21b6-4f2a-ae4b-6176f9df56c1" />

---

### Fluxograma do firmware
```
[INÍCIO — setup()]
|
v
+------------------+
|  Teste de LEDs   |
|  branco + verm.  |
+------------------+
|
v
+------------------+
|  Conectar Wi-Fi  |
|  (até 20 tent.)  |
+------------------+
|
v
+------------------+
| Inicializar RFID |
|   e Servo SG90   |
+------------------+
|
v
═══════════════════════════════════
loop()
═══════════════════════════════════
|
v
+------------------+
| Aguardar tag     |
|    RFID          |
+------------------+
|
v
+------------------+
|   Ler UID        |
+------------------+
|
v
/------------
|  UID         |
| autorizado?  |
------------/
|       |
SIM      NÃO
|         |
v         v
+-------+  +--------+
|LED    |  |LED     |
|branco |  |verm.   |
|Servo  |  |Servo   |
|90°    |  |0°      |
|3s     |  |3s      |
+-------+  +--------+
|         |
v         v
+-------+  +--------+
|POST   |  |POST    |
|Supabase  |Supabase|
|true   |  |false   |
+-------+  +--------+
|         |
v         v
+------------------+
|  PICC_HaltA()    |
|  Encerra leitura |
+------------------+
|
v
[volta ao início do loop]
```
---

### 🔌 Esquema Elétrico — Pinagem

| Componente / Pino | Pino ESP32-C3 | Observação |
|---|---|---|
| RC522 — SDA (SS) | GPIO 2 | SPI — Chip Select |
| RC522 — SCK | GPIO 3 | SPI — Clock |
| RC522 — MOSI | GPIO 4 | SPI — Master Out |
| RC522 — MISO | GPIO 5 | SPI — Master In |
| RC522 — RST | GPIO 10 | Reset do módulo RFID |
| Servo SG90 — Sinal | GPIO 6 | PWM — controle de posição |
| LED branco | GPIO 8 | Saída digital — acesso liberado |
| LED vermelho | GPIO 9 | Saída digital — acesso negado |
---

## 🖥️ Dashboard Web

Frontend desenvolvido em **Angular** com atualização automática a cada 3 segundos, exibindo o histórico de acessos em tempo real.

- **Deploy:** [fechadura.netlify.app](https://fechadura.netlify.app)
- **Banco de dados:** Supabase (PostgreSQL)

### Como rodar localmente

**Pré-requisitos:** Node.js e Angular CLI instalados.

```bash
# Entre na pasta do frontend
cd Front-Fechadura/controle-acesso-rfid

# Instale as dependências
npm install

# Rode o servidor de desenvolvimento
ng serve
```

Acesse `http://localhost:4200` no navegador.

---

## ⚙️ Configuração do ESP32

### Pré-requisitos

- Arduino IDE
- Biblioteca **MFRC522** instalada
- Biblioteca **ESP32Servo** instalada

### Como carregar o código

1. Abra a pasta `Arduino/` na Arduino IDE
2. Selecione a placa **ESP32C3 Dev Module**
3. Configure o Wi-Fi e as credenciais do Supabase no código
4. Faça o upload usando o cabo USB-C

---

## 🗄️ Banco de Dados (Supabase)

A tabela `acessos` armazena cada tentativa de acesso:

| Campo | Tipo | Descrição |
|---|---|---|
| `id` | int | Identificador único |
| `uid` | text | UID da tag RFID |
| `data_hora` | timestamp | Data e hora do acesso |
| `liberado` | boolean | `true` = liberado, `false` = negado |

---

## 🚦 Como Funciona

1. O usuário aproxima uma tag RFID do leitor RC522
2. O ESP32 lê o UID da tag
3. Se o UID estiver na lista de autorizados:
   - LED branca acende
   - Servo motor abre a fechadura
4. Se o UID não estiver autorizado:
   - LED vermelho acende
   - Acesso é negado
5. O ESP32 registra o acesso no Supabase
6. A página web atualiza automaticamente exibindo o novo registro

---

## 👩‍💻 Tecnologias Utilizadas

- **Hardware:** ESP32-C3, RFID RC522, Servo SG90, MB102
- **Firmware:** C++ (Arduino IDE)
- **Frontend:** Angular 21
- **Banco de dados:** Supabase (PostgreSQL)
- **Deploy:** Netlify
---

## 🔐 Segurança e Integridade Acadêmica

As credenciais do projeto (Wi-Fi e Supabase) são armazenadas em um arquivo `config.h`
separado, que **não é versionado no repositório**.

### Como configurar

1. Abra o `config.h` e preencha com suas credenciais reais:
```cpp
   #define WIFI_SSID     "SEU_WIFI"
   #define WIFI_PASSWORD "SUA_SENHA"
   #define SUPABASE_URL  "https://SEU_PROJETO.supabase.co/rest/v1/acessos"
   #define SUPABASE_KEY  "SUA_CHAVE_API"
```

2. O arquivo `config.h` está listado no `.gitignore` — suas credenciais nunca serão enviadas ao GitHub.

### Como as credenciais são carregadas no código

O arquivo principal importa o `config.h` localmente:

```cpp
#include "config.h"

// As variáveis são usadas diretamente pelo firmware:
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
http.addHeader("apikey", SUPABASE_KEY);
```

Nenhuma credencial real aparece no código versionado.

### .gitignore
