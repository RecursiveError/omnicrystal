#include <omnicrystal.h>

//selecione a interface que deseja usar
/*
#deifne RS 6
#deifne EN 7
#deifne D4 8
#deifne D5 9
#deifne D6 10
#deifne D7 10

LCDParallel LcdInter(RS,EN,D4,D5,D6,D7);
*/
LCDPCF8754 LcdInter(0x27);
Omnicrystal lcd(LcdInter, Bus4Bits, 2, 16);

void setup() {
  lcd.begin().print("Hello World!!!");
}

void loop(){
}
