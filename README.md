
# IOT - GPSMottu 

[Vídeo demonstrativo da solução](https://youtu.be/4bZLAtOSI-M)

## Descrição da Solução:
O Java API - Gestão de Motos é uma aplicação desenvolvida em Java com foco em auxiliar operadores e gestores de filiais no controle e monitoramento de motos, funcionários e setores da empresa.

O sistema oferece funcionalidades para:

-	Gestão de motos: cadastro, atualização de status e rastreamento em diferentes filiais.
-	Controle via QR Code: associação de motos a QR Codes, permitindo rápida identificação e verificação no momento de entrada, saída ou movimentação.
-	Mapeamento de setores e filiais: estruturação de áreas internas da empresa para facilitar a localização e organização.
-	Gestão de funcionários: registro de colaboradores vinculados a cada filial, integrando informações relevantes para a operação.

## Benefícios para o Negócio

Com essas funcionalidades, a empresa consegue implementar um controle mais eficiente sobre as motos e sua localização, alcançando objetivos estratégicos como:
-	Redução de perdas e prejuízos: evitar que motos sejam extraviadas ou deixem de ser monitoradas.
-	Melhor comunicação interna: facilitar a troca de informações sobre a frota entre funcionários e gestores.
-	Maior rastreabilidade: garantir que cada moto esteja sempre associada a uma filial, setor e responsável.


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

