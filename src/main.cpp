#include <Arduino.h>
#include "DHT.h"

#define DHTPIN 2       // Pino SDA → ligado no pino digital 2
#define DHTTYPE DHT22  // Tipo do sensor
#define LED 13
#define BUTTON 12
#define BUZZER 9

bool estado = false;        // começa desligado (0)
int leituraAnterior = HIGH; // leitura anterior do botão
unsigned long ultimoTempo = 0; // para controle do tempo de 10s
unsigned long ultimoDebounce = 0; 
const unsigned long debounceDelay = 50;

// Instancia o sensor DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP); // botão com pull-up interno
  Serial.begin(9600);

  dht.begin(); // inicializa o DHT22
}

void loop() {
  int leituraAtual = digitalRead(BUTTON);

  // debounce
  if (leituraAtual != leituraAnterior) {
    ultimoDebounce = millis();
  }

  if ((millis() - ultimoDebounce) > debounceDelay) {
    // Detecta apenas borda de descida (HIGH -> LOW)
    if (leituraAnterior == HIGH && leituraAtual == LOW) {
      estado = !estado; // flip (toggle)
      Serial.print("Novo estado: ");
      Serial.println(estado);
    }
  }

  leituraAnterior = leituraAtual;

  // Controle do LED e Buzzer
  if (estado) {
    digitalWrite(LED, HIGH);
    digitalWrite(BUZZER, HIGH);
  } else {
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);
  }

  // A cada 10 segundos, printar temperatura e umidade
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
}
