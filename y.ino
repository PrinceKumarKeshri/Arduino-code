#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
int buzzer=11;
int temp=0;
LiquidCrystal_I2C lcd(0x3F, 16, 2);                 
String  Grsp;
SoftwareSerial gsm(8,9); // RX, TX

void setup() {
  Serial.begin(9600);
  gsm.begin(9600);
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
    lcd.print("Wireless Notice");
      delay(500);
      lcd.setCursor(0,1);
      lcd.print("Board");
      delay(2000);
      lcd.clear();
    pinMode(buzzer,OUTPUT);
  gsm.print("AT"); //checking
  
  gsm.print("AT+CMGF=1");  //Set to Text mode
  gsm.print("AT+CNMI=2,2,0,0,0"); //Set to notification for new message, New message indication
  
}

void loop() {
  if(gsm.available()) {
    //Check if GSM Send any data
    Grsp = gsm.readString(); //Read data received from SIM800L GSM Module
     
      Serial.print(Grsp);
      
         lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(Grsp); //Print string which received from GSM (sms, sender, sms index, receive time, etc)
        delay(1000);
        if(Grsp)
        {
           tone(buzzer, 8000, 4000);
          }
         else{
           noTone(buzzer);
          }
          delay(1000);
      
    }
    
              delay(700);

           lcd.scrollDisplayLeft();

}
