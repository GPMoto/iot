#define THINGER_SERIAL_DEBUG
#include <ThingerESP32.h>
#include "DHTesp.h"
#include <Wire.h>
#include <WebServer.h>
#include <HTTPClient.h>

#define USERNAME "felipeRibeiro12981957420984"
#define DEVICE_ID "esp32_dht"
#define DEVICE_CREDENTIAL "&y%yLg2RbM#wuOaU"

#define SSID "Wokwi-GUEST"
#define SSID_PASSWORD ""

#define PIN_LED 26
#define PIN_LED_MOTO 27
#define BUZZER 14
const int DHT_PIN = 15;

float temp = 0;
int hum = 0;

DHTesp dhtSensor;
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

// ==================== ESTRUTURAS ====================
struct Distrito {
  String nome;
  float posicaoX;
  float posicaoY;
};

struct Moto {
  String nome;
  String condicao;
  Distrito distrito;
  String descricaoDeEstado;
};

// ==================== BANCO DE DADOS ====================
const int MAX_MOTOS = 20;
Moto bancoDados[MAX_MOTOS];
int totalMotos = 0;

// ==================== DISTRITOS PRÉ-DEFINIDOS ====================
Distrito getDistritoOficina() {
  Distrito d = {"Oficina", -43.5507, -16.6335};
  return d;
}

Distrito getDistritoPatio() {
  Distrito d = {"Patio", -73.5505, -46.6333};
  return d;
}

Distrito getDistritoGaragem() {
  Distrito d = {"Garagem", -18.5509, -71.6331};
  return d;
}

Distrito getDistritoRua() {
  Distrito d = {"Rua", -78.5515, -34.6320};
  return d;
}

Distrito getDistritoEstacionamento() {
  Distrito d = {"Estacionamento", -13.8565, -86.6333};
  return d;
}

// ==================== FUNÇÕES DO BANCO ====================
void adicionarMoto(String nome, String condicao, Distrito distrito, String descricao) {
  if(totalMotos < MAX_MOTOS) {
    bancoDados[totalMotos].nome = nome;
    bancoDados[totalMotos].condicao = condicao;
    bancoDados[totalMotos].distrito = distrito;
    bancoDados[totalMotos].descricaoDeEstado = descricao;
    totalMotos++;
    Serial.println("Moto adicionada: " + nome);
  } else {
    Serial.println("Banco cheio! Limite: " + String(MAX_MOTOS));
  }
}

void inicializarBancoDados() {
  adicionarMoto("Sport", "Em uso", getDistritoPatio(), "Disponivel para uso");
  adicionarMoto("Sport", "Parada", getDistritoPatio(), "Aguardando documentacao");
  adicionarMoto("Urban", "Manutencao", getDistritoOficina(), "Manutencao preventiva");
  adicionarMoto("Urban", "Manutencao", getDistritoOficina(), "Troca de oleo e pneus");
  adicionarMoto("Eletric", "Parada", getDistritoGaragem(), "Reservada para cliente VIP");
  adicionarMoto("Eletric", "Em uso", getDistritoRua(), "Em uso - Cliente ID 1234");
  
  Serial.println("===================================");
  Serial.println("Banco de dados inicializado!");
  Serial.println("Total de motos: " + String(totalMotos));
  Serial.println("===================================");
}

void atualizarCondicao(int index, String novaCondicao) {
  if(index >= 0 && index < totalMotos) {
    bancoDados[index].condicao = novaCondicao;
    Serial.println("Condicao atualizada para: " + novaCondicao);
  }
}

void moverMoto(int index, Distrito novoDistrito) {
  if(index >= 0 && index < totalMotos) {
    bancoDados[index].distrito = novoDistrito;
    Serial.println("Moto movida para: " + novoDistrito.nome);
  }
}

// ==================== SETUP ====================
void setup() {
  thing.add_wifi(SSID, SSID_PASSWORD);
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_LED_MOTO, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  inicializarBancoDados();
  
  thing["GPIO_26"] << digitalPin(26);
  thing["temp"] >> outputValue(temp);
  thing["hum"] >> outputValue(hum);
  
  // Listar todas as motos
  thing["motos"] >> [](pson& out) {
    for(int i = 0; i < totalMotos; i++) {
      char key[10];
      sprintf(key, "m%d", i);
      out[key]["id"] = i;
      out[key]["nome"] = bancoDados[i].nome;
      out[key]["condicao"] = bancoDados[i].condicao;
      out[key]["distrito"]["nome"] = bancoDados[i].distrito.nome;
      out[key]["distrito"]["posicaoX"] = bancoDados[i].distrito.posicaoX;
      out[key]["distrito"]["posicaoY"] = bancoDados[i].distrito.posicaoY;
      out[key]["descricaoDeEstado"] = bancoDados[i].descricaoDeEstado;
    }
    out["total"] = totalMotos;
  };
  
  // Buscar moto específica
  thing["buscarMoto"] = [](pson& in, pson& out) {
    int id = in;
    if(id >= 0 && id < totalMotos) {
      out["id"] = id;
      out["nome"] = bancoDados[id].nome;
      out["condicao"] = bancoDados[id].condicao;
      out["distrito"]["nome"] = bancoDados[id].distrito.nome;
      out["distrito"]["posicaoX"] = bancoDados[id].distrito.posicaoX;
      out["distrito"]["posicaoY"] = bancoDados[id].distrito.posicaoY;
      out["descricaoDeEstado"] = bancoDados[id].descricaoDeEstado;
    } else {
      out["erro"] = "ID invalido";
    }
  };
  
  thing["ligarLedMoto"] = [](pson& in, pson& out) {
    
    int decision = in;
    if(decision == 0) {
      digitalWrite(PIN_LED_MOTO, LOW);
      digitalWrite(BUZZER, LOW);
      out["message"] = "Led e buzzer da moto desligado!";
    } else {
      digitalWrite(PIN_LED_MOTO, HIGH);
      digitalWrite(BUZZER, HIGH);
      out["message"] = "Led e buzzer da moto ligado!";
    }
  };
  
  // Estatísticas
  thing["stats"] >> [](pson& out) {
    int oficina = 0, patio = 0, garagem = 0, rua = 0, estacionamento = 0;
    
    for(int i = 0; i < totalMotos; i++) {
      String dist = bancoDados[i].distrito.nome;
      if(dist == "Oficina") oficina++;
      else if(dist == "Patio") patio++;
      else if(dist == "Garagem") garagem++;
      else if(dist == "Rua") rua++;
      else if(dist == "Estacionamento") estacionamento++;
    }
    
    out["total"] = totalMotos;
    out["oficina"] = oficina;
    out["patio"] = patio;
    out["garagem"] = garagem;
    out["rua"] = rua;
    out["estacionamento"] = estacionamento;
  };
}

// ==================== LOOP ====================
void loop() {
  thing.handle();
  
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  hum = dhtSensor.getHumidity();
  temp = dhtSensor.getTemperature();
  
  Serial.print("Umidade: ");  
  Serial.println(data.humidity, 1);
  Serial.print("Temp: ");  
  Serial.println(data.temperature, 0);
  
  thing["temp"] >> outputValue(temp);

  
  delay(2000);
}