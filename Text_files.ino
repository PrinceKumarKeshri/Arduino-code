/*
 * generate testcard similar to BMP
 */
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

void setup(void) {
  Serial.begin(9600);
  tft.reset();
  ID=tft.readID();
  tft.begin(ID);
  tft.setRotation(1);
  tft.setFont(NULL);
  tft.fillScreen(BLACK);
  tft.setFont(&FreeMonoBoldOblique18pt7b);
  
  tft.setTextColor(BLUE);
  
  tft.setTextSize(1);

  tft.fillScreen(CYAN);
  
  tft.fillRect(40,138+6,6*68, 65, WHITE);
   
  tft.setCursor(40, 170);
  tft.print("CHANDIGARH GROUP OF");
  
  tft.setCursor(90, 200);
  tft.print("   COLLEGE");
  delay(500);

  tft.fillScreen(RED);
  
  tft.fillRect(40,138+6,6*65, 35, WHITE);
   
  tft.setCursor(40, 170);
  tft.print("TEAM");
  
  delay(500);
  tft.setCursor(120, 170);
  tft.print(" THUNDER");
  delay(500);
  tft.setCursor(280, 170);
  tft.print(" RIDERS");
  delay(500);
  }

void loop() {
  
 
}
