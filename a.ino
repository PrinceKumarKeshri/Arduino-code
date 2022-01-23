#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

// Configure software serial port
SoftwareSerial SIM900(8,9);
//Variable to save incoming SMS characters
String incoming_char;

void setup() {
  // Define the dimensions of the LCD display
  lcd.begin(16, 2);
  // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
  // Make sure that corresponds to the baud rate of your module
  SIM900.begin(19200);
  // For serial monitor
  Serial.begin(19200);
  // AT command to set SIM900 to SMS mode
  lcd.init();
  lcd.backlight();
  SIM900.print("AT+CMGF=1\r");
  delay(100);
  // Set module to send SMS data to serial out upon receipt
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
}

void loop() {
  // Display any text that the GSM shield sends out on the serial monitor
  if(SIM900.available() >0) {
    incoming_char=SIM900.readString();
    //Print the incoming character to the terminal
    Serial.print(incoming_char);
    //Write sms data on lcd display
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(incoming_char.substring(49));
  }
}
