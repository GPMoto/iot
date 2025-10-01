#include "DHT.h"

#define DHTPIN 2       
#define DHTTYPE DHT22 
#define LED 10
#define BUTTON 11
#define BUZZER 9

bool estado = false;              
bool ultimoBotao = HIGH;          
unsigned long ultimoTempo = 0;    

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT); 
  Serial.begin(9600);
  dht.begin(); 

  Serial.println("Sistema iniciado");
}

void loop() {
  int leitura = digitalRead(BUTTON);


  if (leitura == 0 && ultimoBotao == 1) {
    estado = !estado;
    Serial.print("Toggle! Novo estado: ");
    Serial.println(estado ? "LIGADO" : "DESLIGADO");
  }

  ultimoBotao = leitura;

  digitalWrite(LED, estado ? HIGH : LOW);
  digitalWrite(BUZZER, estado ? 1 : 0);



  if (millis() - ultimoTempo >= 10000) {
    ultimoTempo = millis();

    float temperatura = dht.readTemperature();
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

  delay(50);
}
