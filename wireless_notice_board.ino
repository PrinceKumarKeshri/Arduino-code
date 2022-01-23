#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int led=13;

int temp=0,i=0,x=0,k=0;
char str[100],msg[32];

void setup() 
{
  lcd.begin(16,2);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  lcd.print("GSM Initilizing...");

  lcd.setCursor(0,0);
  lcd.print("Wireless Notice");
  lcd.setCursor(0,1);
  lcd.print("    Board      ");
  delay(2000);
  lcd.clear();
  lcd.print("Technolab creation");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("System Ready");
  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(100);
  Serial.println("AT+CMGF=1");
  delay(1000);
  digitalWrite(led, LOW);
}

void loop()    
{
  for(unsigned int t=0;t<60000;t++)
  {
    serialEvent();
  if(temp==1)
  {
    x=0,k=0,temp=0;
    while(x<i)
    {
      while(str[x]=='#')
      {
        x++;
        while(str[x]!='*')
        {
          msg[k++]=str[x++];
        }
      }
      x++;
    }
    msg[k]='\0';
    lcd.clear();
    lcd.print(msg);
    delay(1000);
    temp=0;
    i=0;
    x=0;
    k=0;
  }
  }
  lcd.scrollDisplayLeft();
}
void serialEvent()
{
  while(Serial.available())
  {
    char ch=(char)Serial.read();
    str[i++]=ch;
    if(ch == '*')
    {
      temp=1;
      lcd.clear();
      lcd.print("Message Received");
      delay(1000);
    }
  }
}
