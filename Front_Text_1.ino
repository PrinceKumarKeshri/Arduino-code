
#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBoldOblique18pt7b.h>


#include<MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#define BLACK   0x0000 
#define WHITE   0xFFFF
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define GREY    0x8410
#define ORANGE  0xE880

#include <stdio.h>
uint16_t ID;


#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
#include <MQ2.h>

#define ONE_WIRE_BUS 22
int buzzer = 26;
int smokeA0 = 49;
int sensorThres = 400;
int vs =33;
long  measurement;


 
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

float Celsius = 0;

void setup()
  { sensors.begin();
  pinMode(vs, INPUT);
  pinMode(27, OUTPUT);
   pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
   pinMode(40, OUTPUT);
   pinMode(42, OUTPUT);
   pinMode(44, OUTPUT);
  Serial.begin(9600);
  tft.reset();
  ID=tft.readID();
  tft.begin(ID);
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  tft.setFont(&FreeMonoBoldOblique18pt7b);
  delay(800);
  tft.setTextSize(0.25);
  tft.fillScreen(CYAN);
  tft.setTextColor(BLUE);
  tft.setTextSize(1);
  tft.fillRect(40,138+6,6*68, 65, WHITE);
  delay(800);
  tft.setCursor(40, 170);
  tft.print("CHANDIGARH GROUP OF");
  delay(800);
  tft.setCursor(90, 200);
  tft.print("   COLLEGE");
  delay(800);

  tft.fillScreen(RED);
  delay(800);
  tft.fillRect(40,138+6,6*65, 35, WHITE);
   
  tft.setCursor(40, 170);
  tft.print("TEAM");
  
  delay(800);
  tft.setCursor(120, 170);
  tft.print(" THUNDER");
  delay(800);
  tft.setCursor(280, 170);
  tft.print(" RIDERS");
  delay(800);
  tft.fillScreen(CYAN);
  tft.setCursor(0, 25);
  tft.setTextColor(BLACK);
  tft.setTextSize(1.5);
  tft.print("THUNDER RIDER");
  tft.setCursor(80, 310);
  tft.setTextColor(RED);
  tft.setTextSize(0.25);
  tft.print("Enjoy Your Ride");
  tft.setTextColor(BLUE);
  tft.setTextSize(1);
 
  }

  void loop(){
    sensors.requestTemperatures();
     
    Celsius = sensors.getTempCByIndex(0);
    tft.fillRect(0,62.5+6,6*78, 40, WHITE);
    tft.setCursor(0, 97.5);
    tft.print("Temperature  :");
    tft.print(Celsius);
    tft.print(" °C");
    delay(100);
 
  
  
temp();
smoke();
jhatke();
}
void temp()
{ if(Celsius>=30)
 { 
   digitalWrite(40, HIGH);
   digitalWrite(27, HIGH);
   tone(buzzer, 1000, 0);
   delay(1000);
   
   digitalWrite(27, LOW);
   delay(100);
  
   
   
   }
  else
  {  noTone(buzzer);
    digitalWrite(27, LOW);
    digitalWrite(40, LOW);
    }
    ;}
void smoke()
{ int analogSensor = analogRead(smokeA0);
  tft.fillRect(0,120+6,6*78, 40, WHITE);
  tft.setCursor(0, 155);
  tft.print("Smoke        :");
  tft.print(analogSensor);
  tft.print(" ppm");
  delay(100);
  
  if (analogSensor > sensorThres)
  {
   
   digitalWrite(27, HIGH);
   delay(100);
   digitalWrite(27, LOW);
   delay(100);
    tone(buzzer, 1000, 2000);
   digitalWrite(42, HIGH);
  }
  else
  {
    noTone(buzzer);
   digitalWrite(27, LOW);
   digitalWrite(42, LOW);
   }
  }
  void jhatke()
  {
  long measurement =vibration();

  
  tft.fillRect(0,175+6,6*78, 40, WHITE);
  tft.setCursor(0, 210);
  tft.print("Vibration Lvl:");
  tft.print(measurement);
  tft.print(" Hz");
  delay(100);
  
  if (measurement > 50){
    digitalWrite(27, HIGH);
    delay(100);
    digitalWrite(27, HIGH);
    delay(100);
    tone(buzzer, 1000, 2000);
    digitalWrite(44, HIGH);
  }
  else{
    digitalWrite(27, LOW);
    noTone(buzzer);
    digitalWrite(44,LOW);
    
  }
 
}
long vibration(){
 long measurement=pulseIn (vs, HIGH);
  return measurement;
}
