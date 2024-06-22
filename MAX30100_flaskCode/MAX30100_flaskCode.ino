          
  
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <LiquidCrystal_I2C.h>

#define REPORTING_PERIOD_MS 1000

LiquidCrystal_I2C lcd(0x3F, 16, 2); // Initialize LCD with I2C address 0x3F, 16 columns, and 2 rows

PulseOximeter pox;
uint32_t tsLastReport = 0;

void setup()
{
  Serial.begin(9600);
  
  lcd.init();        // Initialize the LCD
  lcd.backlight();  // Turn on the backlight
  
  if (!pox.begin()) {
    Serial.println("FAILED");
    while (1);
  } else {
    Serial.println("SUCCESS");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
}

void loop()
{
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    int heartRate = pox.getHeartRate();
    int oxygenLevel = pox.getSpO2();
    
    if (heartRate >= 50 && oxygenLevel >= 60) {
      // Display on LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Heart Rate: ");
      lcd.print(heartRate);
      lcd.setCursor(0, 1);
      lcd.print("Oxygen Level: ");
      lcd.print(oxygenLevel);
      
      String data = "{\"HR\":" + String(pox.getHeartRate()) + ",\"SpO2\":" + String(pox.getSpO2()) + "}";
    Serial.println(data); // Send heart rate and oxygen levels via serial
    } else {
      // Display "Invalid Readings" on LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Invalid Readings");
    }

    tsLastReport = millis();
  }
}
