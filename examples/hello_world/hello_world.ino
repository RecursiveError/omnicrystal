#include <omnicrystal.h>

//select the interface you want to use
/*
#define RS 6
#define EN 7
#define D4 8
#define D5 9
#define D6 10
#define D7 10

LCDParallel LcdInter(RS,EN,D4,D5,D6,D7);
*/
LCDPCF8574 LcdInter(0x27);
Omnicrystal lcd(LcdInter, Bus4Bits, 2, 16);

void setup() {
  lcd.begin().print("Hello World!!!");
}

void loop(){
}
