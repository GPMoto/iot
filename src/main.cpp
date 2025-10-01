#include "DHT.h"

#define DHTPIN 2       // Pino de dados do DHT22
#define DHTTYPE DHT22  // Tipo do sensor
#define LED 10
#define BUTTON 11
#define BUZZER 9

bool estado = false;              // começa desligado
bool ultimoBotao = HIGH;          // último estado lido do botão
unsigned long ultimoTempo = 0;    // para controle de 10s

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT); // botão com pull-up interno
  Serial.begin(9600);
  dht.begin(); // inicializa o DHT22

  Serial.println("Sistema iniciado");
}

void loop() {
  // Lê o botão
  int leitura = digitalRead(BUTTON);


  // Detecta borda de descida (HIGH -> LOW) para toggle
  if (leitura == 0 && ultimoBotao == 1) {
    estado = !estado;
    Serial.print("Toggle! Novo estado: ");
    Serial.println(estado ? "LIGADO" : "DESLIGADO");
  }

  // Atualiza o estado anterior do botão
  ultimoBotao = leitura;

  // Liga/desliga LED e buzzer
  digitalWrite(LED, estado ? HIGH : LOW);
  digitalWrite(BUZZER, estado ? 1 : 0);

  // Log do estado do LED e buzzer


  // A cada 10 segundos, lê e mostra temperatura/umidade
  if (millis() - ultimoTempo >= 10000) {
    ultimoTempo = millis();

    float temperatura = dht.readTemperature(); // Celsius
    float umidade = dht.readHumidity();

    if (isnan(temperatura) || isnan(umidade)) {
      Serial.println("Falha ao ler do sensor DHT22!");
    } else {
      Serial.print("Temperatura: ");
      Serial.print(temperatura);
      Serial.println(" °C");

      Serial.print("Umidade: ");
      Serial.print(umidade);
      Serial.println(" %");
    }
  }

  delay(50); // pequeno atraso para não poluir o Serial
}
