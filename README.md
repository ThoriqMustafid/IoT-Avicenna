# 🌱 Soil Moisture & Temperature Monitor (Arduino)

This project is a monitoring system for **soil moisture** and **environment temperature**, built using:

- Arduino Uno
- Capacitive Soil Moisture Sensor (more durable & accurate)
- Waterproof **DS18B20** temperature sensor
- 16x2 LCD with I2C module

Perfect for:

- Smart Garden system
- Plant monitoring
- Automatic watering control
- Learning basic IoT & sensor integration

---

## 📌 Features

- Reads **soil moisture (0–100%)**
- Reads **temperature** using DS18B20
- Displays data on **I2C 16x2 LCD**
- Capacitive sensor → corrosion-proof, stable, accurate
- Simple code, easy to customize

---

## 🛠️ Required Components

| No | Component | Qty |
| --- | --- | --- |
| 1 | Arduino Uno | 1 |
| 2 | **Capacitive Soil Moisture Sensor** | 1 |
| 3 | **DS18B20 Waterproof Sensor** | 1 |
| 4 | 4.7kΩ Resistor (for DS18B20 pull-up) | 1 |
| 5 | I2C LCD 16x2 | 1 |
| 6 | Jumper wires (M–M & M–F) | - |
| 7 | 400-hole Breadboard | 1 |

---

## 🔌 Wiring Guide

### **1. DS18B20 Waterproof Sensor**

| DS18B20 Wire | Arduino Pin |
| --- | --- |
| Red (VCC) | 5V |
| Black (GND) | GND |
| Yellow (DATA) | D2 |

➡️ Add a **4.7kΩ resistor** between DATA ↔ VCC.

---

### **2. Capacitive Soil Moisture Sensor**

| Sensor Pin | Arduino Pin |
| --- | --- |
| AO | A0 |
| VCC | 5V |
| GND | GND |

*(This capacitive type doesn’t rust like resistive sensors.)*

---

### **3. I2C LCD (Address: 0x27)**

| LCD Pin | Arduino Pin |
| --- | --- |
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

---

## 📦 Required Libraries

Install via **Arduino IDE → Tools → Manage Libraries**:

- `LiquidCrystal_I2C`
- `DallasTemperature`
- `OneWire`

---

## 📜 Source Code

```cpp
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
  lcd.print("Temp: ");
  lcd.print(tempC);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Moist: ");
  lcd.print(soilPercent);
  lcd.print("%");

  delay(1000);
}

```

---
