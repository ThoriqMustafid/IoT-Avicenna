#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2      
#define SOIL_PIN A0          

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin(16, 2);
  lcd.backlight();

  sensors.begin();

  lcd.setCursor(0, 0);
  lcd.print("Soil Monitor");
  delay(1500);
}

void loop() {
  int rawSoil = analogRead(SOIL_PIN);
  
  int soilPercent = map(rawSoil, 1023, 300, 0, 100);
  soilPercent = constrain(soilPercent, 0, 100);

  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
  lcd.print(tempC);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Kelemb: ");
  lcd.print(soilPercent);
  lcd.print("%");

  delay(1000);
}
