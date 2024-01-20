#include <DHT.h>

#define DHTTYPE DHT22
#define DHT1PIN 7
#define DHT2PIN 8
#define SOIL_MOISTURE_PIN A0
#define sensorsinal A1

DHT dht1(DHT1PIN, DHTTYPE);
DHT dht2(DHT2PIN, DHTTYPE);
const int pinoSensor = A0;
int valorLido; 

int analogSoloSeco = 400;
int analogSoloMolhado = 150;
int percSoloSeco = 0;
int percSoloMolhado = 100;

void setup() {
  Serial.begin(9600);
  Serial.println("Inicializando");

  dht1.begin();
  dht2.begin();
  delay(2000);
}

void loop() {
  delay(10000);

  float umidade_dht_1 = dht1.readHumidity();
  float temperatura_dht_1 = dht1.readTemperature();
  float umidade_dht_2 = dht2.readHumidity();
  float temperatura_dht_2 = dht2.readTemperature();

  valorLido = constrain(analogRead(pinoSensor),analogSoloMolhado,analogSoloSeco);
  valorLido = map(valorLido,analogSoloMolhado,analogSoloSeco,percSoloMolhado,percSoloSeco);

  Serial.println("UMIDADE DO AR");
  Serial.print("Sensor 1: ");
  Serial.print(umidade_dht_1);
  Serial.println(" %\t");
  Serial.print("Sensor 2: ");
  Serial.print(umidade_dht_2);
  Serial.println(" %\t");

  Serial.println("TEMPERATURA");
  Serial.print("Sensor 1: ");
  Serial.print(temperatura_dht_1);
  Serial.println(" °C");
  Serial.print("Sensor 2: ");
  Serial.print(temperatura_dht_2);
  Serial.println(" °C");

  Serial.print("UMIDADE DO SOLO: ");
  Serial.print(valorLido);
  Serial.println("%");

  int level = analogRead(sensorsinal);
  Serial.print("NÍVEL DE ÁGUA: ");
  Serial.println(level);
}
