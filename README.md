# 🔐 Fechadura com RFID

Sistema de controle de acesso utilizando ESP32-C3, leitor RFID RC522 e servo motor, com dashboard web em tempo real integrado ao Supabase.

# 🔗 Links de Acesso

| Recurso | Link |
|---|---|
| Repositório GitHub | [github.com/Eduardo-Melo-010/Fechadura_Inteligente-IoT](https://github.com/Eduardo-Melo-010/Fechadura_Inteligente-IoT) |
| Dashboard (deploy) | [fechadura.netlify.app](https://fechadura.netlify.app) |
| Apresentação (slides) | [inserir link] |

## 📋 Sobre o Projeto

O sistema permite o controle de acesso físico por meio de cartões/tags RFID. Ao aproximar uma tag do leitor, o ESP32 verifica se o UID está autorizado e aciona um servo motor para abrir ou negar o acesso. Cada tentativa de acesso é registrada no Supabase e exibida em tempo real no dashboard web.

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
