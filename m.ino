#include <Wire.h>


#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 16, 2);
void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Booting....");
  lcd.setCursor(0, 1);
  lcd.print("****************");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Checking GSM");
  lcd.setCursor(0, 1);
  lcd.print("connectivity..");
  
}
void loop() {
}
