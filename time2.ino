/*
 * generate testcard similar to BMP
 */
#include <Adafruit_GFX.h>
#if defined(_GFXFONT_H_)           //are we using the new library?
#include <Fonts/FreeSans9pt7b.h>
#define ADJ_BASELINE 11            //new fonts setCursor to bottom of letter
#else
#define ADJ_BASELINE 0             //legacy setCursor to top of letter
#endif




#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#define BLACK   0x0000
#define WHITE   0xFFFF 
#define BLUE    0x001F
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
    
    
    
     

    
#if defined(_GFXFONT_H_)
    tft.setFont(&FreeSans9pt7b);
#endif
    hh = conv2d(__TIME__);
    mm = conv2d(__TIME__ + 3);
    ss = conv2d(__TIME__ + 6);
}

void loop(void)
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
