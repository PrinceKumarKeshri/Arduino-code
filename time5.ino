/*
 * generate testcard similar to BMP
 */
#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBoldOblique18pt7b.h>




#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#define BLACK   0x0000
#define WHITE   0xFFFF 
#define BLUE    0x001F
#define CYAN    0x07FF
#include <stdio.h>
uint16_t ID;
uint8_t hh, mm, ss ; //containers for current time
uint8_t conv2d(const char* p)
{
    uint8_t v = 0;
    if ('0' <= *p && *p <= '9') v = *p - '0';
    return 10 * v + *++p - '0';
}

void setup(void)
{
    Serial.begin(9600);
    tft.reset();
    ID=tft.readID();
    tft.begin(ID);
    tft.setRotation(1);
    tft.fillScreen(BLACK);
    tft.fillScreen(CYAN);
    
    
    tft.setFont(&FreeMonoBoldOblique18pt7b);

    hh = conv2d(__TIME__);
    mm = conv2d(__TIME__ + 3);
    ss = conv2d(__TIME__ + 6);
}

void loop(void)
{
    tft.setTextColor(BLACK,CYAN);
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
        
        tft.setCursor(288.5, 2.5 );
        tft.print(buf);
        delay(1000);
    }
}
