#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTTYPE DHT22
#define DHT1PIN 7
#define DHT2PIN 8
#define WATERPIN A1
#define COLUNAS_LCD 16
#define LINHAS_LCD 2
#define ENDERECO_LCD 0x3F

LiquidCrystal_I2C lcd(ENDERECO_LCD, COLUNAS_LCD, LINHAS_LCD);

// Sensor de umidade e temperatura
DHT dht1(DHT1PIN, DHTTYPE);
DHT dht2(DHT2PIN, DHTTYPE);

// Sensor de umidade de solo
const int SOLOPIN = A0;
int umidade_solo;
int analogSoloSeco = 400;
int analogSoloMolhado = 150;
int percSoloSeco = 0;
int percSoloMolhado = 100;

// Rele
int RELEPIN = 9;

void setup() {
  Serial.begin(9600);

  // Inicializa os sensores DHT22
  dht1.begin();
  dht2.begin();

  // Inicializa o rele
  pinMode(RELEPIN, OUTPUT);

  // Inicializa o LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Aguarda tudo ficar pronto
  delay(5000);
}

void loop() {
  float umidade_dht_1 = dht1.readHumidity();
  float temperatura_dht_1 = dht1.readTemperature();
  float umidade_dht_2 = dht2.readHumidity();
  float temperatura_dht_2 = dht2.readTemperature();

  umidade_solo = constrain(analogRead(SOLOPIN), analogSoloMolhado, analogSoloSeco);
  umidade_solo = map(umidade_solo, analogSoloMolhado, analogSoloSeco, percSoloMolhado, percSoloSeco);

  int nivel_agua = analogRead(WATERPIN);

  lcd.setCursor(0, 0);
  lcd.print("Umidade & Temp");
  lcd.setCursor(0, 1);
  lcd.print(String(umidade_dht_1) + "% " + String(temperatura_dht_1) + "C\t | " + String(umidade_dht_2) + "% " + String(temperatura_dht_2) + "C");
  delay(5000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Umidade solo");
  lcd.setCursor(0, 1);
  lcd.print("Solo: " + String(umidade_solo) + "%");
  delay(5000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Nivel de agua");
  lcd.setCursor(0, 1);
  lcd.print(String(nivel_agua));
  delay(5000);
  lcd.clear();

  // Verifica a temperatura e controla o rele
  if (temperatura_dht_1 >= 30 || temperatura_dht_2 >= 30) {
    digitalWrite(RELEPIN, HIGH);
  } else {
    digitalWrite(RELEPIN, LOW);
  }
}
