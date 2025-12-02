# 🌱 Soil Moisture & Temperature Monitor (Arduino)
Project ini adalah sistem monitoring **kelembaban tanah** dan **suhu lingkungan** menggunakan:
- Arduino Uno
- Capacitive Soil Moisture Sensor (lebih awet & akurat)
- Sensor suhu waterproof **DS18B20**
- LCD I2C 16x2

Cocok untuk project:
- Smart Garden
- Monitoring tanaman
- Sistem penyiraman otomatis
- Belajar dasar IoT & sensor

---

## 📌 Fitur
- Membaca **kelembaban tanah (0–100%)**
- Membaca **suhu tanah/air dengan DS18B20**
- Menampilkan data di **LCD I2C 16x2**
- Capacitive sensor → tahan korosi, akurat, stabil
- Code simple, mudah dikembangkan

---

## 🛠️ Komponen yang Dibutuhkan
| No | Komponen | Jumlah |
|----|----------|--------|
| 1 | Arduino Uno | 1 |
| 2 | **Capacitive Soil Moisture Sensor** | 1 |
| 3 | **DS18B20 Waterproof** | 1 |
| 4 | Resistor **4.7kΩ** (untuk DS18B20 pull-up) | 1 |
| 5 | LCD 16x2 + Modul I2C | 1 |
| 6 | Kabel jumper (M–M & M–F) | - |
| 7 | Breadboard 400 holes | 1 |

---

## 🔌 Wiring

### **1. DS18B20 Waterproof**
| DS18B20 | Arduino |
|--------|---------|
| Merah (VCC) | 5V |
| Hitam (GND) | GND |
| Kuning (DATA) | D2 |

➡️ Pasang **resistor 4.7kΩ** antara DATA ↔ VCC

---

### **2. Capacitive Soil Moisture Sensor**
| Soil Sensor | Arduino |
|-------------|---------|
| AO          | A0 |
| VCC         | 5V |
| GND         | GND |

*(Kelebihan: sensor ini tidak berkarat seperti tipe resistive.)*

---

### **3. LCD I2C (0x27)**
| LCD I2C | Arduino |
|---------|---------|
| VCC     | 5V |
| GND     | GND |
| SDA     | A4 |
| SCL     | A5 |

---

## 📦 Library yang Dibutuhkan
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
