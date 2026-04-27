# 🔐 Smart Lock Senac - Fechadura Inteligente IoT

[![Platform](https://img.shields.io/badge/Platform-ESP32-blue)](https://www.espressif.com/)
[![Protocol](https://img.shields.io/badge/Protocol-MQTT-brightgreen)](https://mqtt.org/)
[![IDE](https://img.shields.io/badge/IDE-Arduino%20IDE-orange)](https://www.arduino.cc/)
[![License](https://img.shields.io/badge/License-MIT-yellow)](LICENSE)

> **MVP - Controle de Acesso Inteligente para a Faculdade Senac PE**

---

## 📌 Índice

- [Sobre o Projeto](#sobre-o-projeto)
- [Problema e Solução](#problema-e-solução)
- [Arquitetura](#arquitetura)
- [Hardware Necessário](#hardware-necessário)
- [Esquema de Ligação](#esquema-de-ligação)
- [Configuração e Instalação](#configuração-e-instalação)
- [Código Fonte](#código-fonte)
- [Protótipo Mobile](#protótipo-mobile)
- [Backlog do Produto](#backlog-do-produto)
- [Equipe](#equipe)
- [Licença](#licença)

---

## 🎯 Sobre o Projeto

Este repositório contém o protótipo funcional (Prova de Conceito) de uma **fechadura inteligente** desenvolvida para a **Faculdade Senac Pernambuco**. O sistema substitui o modelo tradicional de chaves físicas por uma solução integrada de IoT que oferece:

- ✅ Acesso via **tag RFID** (crachá institucional)
- ✅ **Registro automático** de todos os acessos
- ✅ Controle de permissões por **perfil de usuário**
- ✅ **Monitoramento em tempo real** via aplicativo mobile
- ✅ Conformidade com a **LGPD**

---

## ❌ Problema e Solução

### Problemas Identificados
| Problema | Impacto |
|----------|---------|
| Perda e extravio de chaves | Custos recorrentes com reposição |
| Ausência de rastreabilidade | Investigação comprometida em caso de furto |
| Filas na portaria | Atraso no início das aulas |
| Cópias não autorizadas | Segurança institucional fragilizada |

### Nossa Solução
| Camada | Implementação |
|--------|---------------|
| **Hardware** | ESP32 + RFID RC522 + Sensor magnético + Solenoide |
| **Comunicação** | Protocolo MQTT (broker HiveMQ) |
| **Nuvem** | Firebase para logs e permissões (planejado) |
| **Mobile** | App com dashboard, logs e alertas |

---

## 🏗️ Arquitetura
