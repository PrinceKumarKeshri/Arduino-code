/*
 * generate testcard similar to BMP
 */
#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBoldOblique18pt7b.h>


#include<MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#define BLACK  0x0000 
#define WHITE  0xFFFF
#define BLUE   0x001F

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
  
  tft.setTextColor(WHITE);
  
  tft.setTextSize(1);

  
  tft.fillRect(40,138+6,6*65, 35, BLUE);
   
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
