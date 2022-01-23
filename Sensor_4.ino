
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
int sensorThres = 1023;
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
  tft.fillScreen(BLACK);
  tft.setFont(&FreeMonoBoldOblique18pt7b);
  tft.setRotation(1);
  
  
  tft.setTextSize(1);

  tft.fillScreen(CYAN);
  
  
  }

  void loop(){
    sensors.requestTemperatures();
     
    Celsius = sensors.getTempCByIndex(0);
    tft.fillRect(0,5+6,6*78, 40, WHITE);
    tft.setCursor(0, 40);
    tft.print("Temperature  :");
    tft.print(Celsius);
    tft.print(" °C");
    delay(100);
 
  
  
temp();
smoke();
jhatke();
}
void temp()
{ if(Celsius>=20)
 { 
   tft.setTextColor(BLUE);
   digitalWrite(40, HIGH);
   digitalWrite(27, HIGH);
   tone(buzzer, 1000, 0);
   delay(1000);
   
   digitalWrite(27, LOW);
   delay(100);
  
   
   
   }
  else
  { 
    tft.setTextColor(ORANGE); 
    noTone(buzzer);
    digitalWrite(27, LOW);
    digitalWrite(40, LOW);
    }
    ;}
void smoke()
{ int analogSensor = analogRead(smokeA0);
  tft.fillRect(0,62.5+6,6*78, 40, WHITE);
  tft.setCursor(0, 97.5);
  tft.print("Smoke        :");
  tft.print(analogSensor);
  tft.print(" ppm");
  delay(100);
  
  if (analogSensor > sensorThres)
  {
    tft.setTextColor(BLUE);
   
   digitalWrite(27, HIGH);
   delay(100);
   digitalWrite(27, LOW);
   delay(100);
    tone(buzzer, 1000, 2000);
   digitalWrite(42, HIGH);
  }
  else
  {
    tft.setTextColor(ORANGE);
    noTone(buzzer);
   digitalWrite(27, LOW);
   digitalWrite(42, LOW);
   }
  }
  void jhatke()
  {
  long measurement =vibration();
 
  tft.fillRect(0,120+6,6*78, 40, WHITE);
  tft.setCursor(0, 155);
  tft.print("Vibration Lvl:");
  tft.print(measurement);
  tft.print(" Hz");
  delay(100);
  
  if (measurement > 50){
    tft.setTextColor(BLUE);
    digitalWrite(27, HIGH);
    delay(100);
    digitalWrite(27, HIGH);
    delay(100);
    tone(buzzer, 1000, 2000);
    digitalWrite(44, HIGH);
  }
  else{
    tft.setTextColor(ORANGE);
    digitalWrite(27, LOW);
    noTone(buzzer);
    digitalWrite(44,LOW);
    
  }
 
}
long vibration(){
 long measurement=pulseIn (vs, HIGH);
  return measurement;
}
