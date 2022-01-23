
#include <Adafruit_GFX.h>
#if defined(_GFXFONT_H_)
#include <Fonts/FreeMonoBoldOblique18pt7b.h>
#define ADJ_BASELINE 11            //new fonts setCursor to bottom of letter
#else
#define ADJ_BASELINE 0             //legacy setCursor to top of letter
#endif

#include<MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#define BLACK   0x0000 
#define WHITE   0xFFFF
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENssssssssssssssssssssssssssssssssssssssssssssssssssssssssTA 0xF81F
#define YELLOW  0xFFE0
#define GREY    0x8410
#define ORANGE  0xE880

#include <stdio.h>
uint16_t ID;

uint8_t hh, mm, ss ; //containers for current time
uint8_t conv2d(const char* p)
{
    uint8_t v = 0;
    if ('0' <= *p && *p <= '9') v = *p - '0';
    return 10 * v + *++p - '0';
}


#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
#include <MQ2.h>

#define ONE_WIRE_BUS 22
int buzzer = 26;
int smokeA0 = 49;
int sensorThres = 1023;
int vs =33;


 
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
    tft.fillScreen(CYAN);
    tft.setRotation(1);
    tft.setTextColor(BLUE); 
    tft.setTextSize(1);
    tft.setFont(&FreeMonoBoldOblique18pt7b);

    hh = conv2d(__TIME__);
    mm = conv2d(__TIME__ + 3);
    ss = conv2d(__TIME__ + 6);
  }

  void loop(){
    sensors.requestTemperatures();
     
    Celsius = sensors.getTempCByIndex(0);
    tft.fillRect(0,62.5+6,6*78, 40, WHITE);
    tft.setCursor(0, 97.5);
    tft.print("Temperature  :");
    tft.print(Celsius);
    tft.print(" C");
    delay(100);
  
   
temp();
smoke();
jhatke();
samay(); 
}



void temp()
{ if(Celsius>=20)
 { 
   digitalWrite(40, HIGH);
   digitalWrite(27, HIGH);
   tone(buzzer, 1000, 0);
   delay(100);
   
   digitalWrite(27, LOW);
   delay(100);
  
   
   
   }
  else
  { 
    noTone(buzzer);
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
  ;}
  void jhatke()
  {
   long measurement =vibration();
 
  tft.fillRect(0,215+6,6*78, 40, WHITE);
  tft.setCursor(0, 250);
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
void samay()
{
   tft.setTextColor(WHITE, BLACK);
    tft.setFont(NULL);
    tft.setTextSize(4);
    while (1) {
       if (++ss > 59) {
            ss = 0;
            mm++;
            if (mm > 59) {
                mm = 0;
                hh++;
                if (hh > 23) hh = 0;
            }
        }
        char buf[20];
        sprintf(buf, "%02d:%02d:%02d", hh, mm,ss);
        tft.fillRect(0,15*(-12)+6,6*35, 33, BLUE);
        
        tft.setCursor(0, -12 + ADJ_BASELINE);
        tft.print(buf);
        delay(1000);
    }
  }
