
# IOT - GPSMottu 

Esse projeto foi feito com Wokwi simulando Arduino + Protoboard + Led + Buzzer + Sensor DHT22 (Temperatura e Umidade).

O código à ser executado está presente em `src/main.cpp`.


O fluxo principal que eu espero que você use é:

- Abra o `diagram.json` na raiz do projeto no VS Code;
- Use a extensão do Wokwi (ou o Wokwi CLI) para executar a simulação a partir desse `diagram.json` — a extensão transforma o `diagram.json` em uma simulação executável dentro do VS Code e permite interagir com botões, displays e outros componentes.

Este README mantém também instruções para configurar o ambiente (PlatformIO e Wokwi) e para trabalhar com a placa via PlatformIO caso queira compilar/upload localmente.

## Execução a partir de `diagram.json` (recomendada)

Ordem recomendada de execução:

1) Primeiro faça o build do firmware com PlatformIO (obrigatório antes de simular):

```bash
# builda todos os ambientes configurados no project
pio run
# se precisar buildar um ambiente específico:
# pio run -e <nome-do-ambiente>
```

2) Abra o projeto no VS Code:

```bash
code /home/gustavo/projects/iot/gpsmottu-sprint2
```

3) Instale a extensão do Wokwi no VS Code (Marketplace). Essa extensão lê o `diagram.json` e oferece um botão/controle para iniciar a simulação dentro do editor.

4) Abra `diagram.json`. Depois de feito o build (passo 1), a extensão normalmente exibirá um botão ou um painel "Run" / "Simulate". Clique para iniciar a simulação. Você poderá interagir com os componentes virtuais (botões, LEDs, displays) diretamente.

## Pré-requisitos (resumido)
- Node.js + npm (para `wokwi-cli` e extensões que dependam de nodetools)
- Python 3 + pip (para PlatformIO CLI)
- VS Code

Se preferir também compilar/rodar na placa física, mantenho abaixo os passos para PlatformIO.

## Instalar PlatformIO CLI
Recomendo instalar usando o pip (Python). No terminal (zsh):

```bash
python3 -m pip install --user -U platformio
```

Verifique:

```bash
pio --version
```

## Instalar Wokwi CLI (opcional)
```bash
npm install -g @wokwi/cli
```

## Comandos PlatformIO úteis
- Compilar:

```bash
pio run
```

- Upload:

```bash
pio run -t upload
```

- Monitor serial:

```bash
pio device monitor -b 115200
```

## RESULTADOS OBTIDOS

Aqui estão alguns resultados obtidos via terminal:
```bash
Sistema iniciado
Toggle! Novo estado: LIGADO
Temperatura: 24.00 °C
Umidade: 40.00 %
Temperatura: 24.00 °C
Umidade: 40.00 %
Toggle! Novo estado: DESLIGADO
Temperatura: 24.00 °C
Umidade: 40.00 %
```

![alt text](arduino.png)

