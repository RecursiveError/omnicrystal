/*
Author: Guilherme Silva Schultz
data: 2023-03-21

//////////////////////////////////////////////////////////////////////////////
// This example is part of an Eletrogate blog post                          //
//                                                                          //
// Electrogate blog: https://blog.eletrogate.com                            //
//                                                                          //
// Post: https://blog.eletrogate.com/criando-uma-biblioteca-para-arduino/   //
//////////////////////////////////////////////////////////////////////////////

*/

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

//character array for each part of the Eletrogate logo
byte eletrogateChar[] = {
  B00110,
  B00110,
  B11110,
  B11111,
  B00011,
  B00001,
  B00000,
  B11000
};

byte eletrogateChar2[] = {
  B01010,
  B01010,
  B00000,
  B00000,
  B10001,
  B11011,
  B11011,
  B00000
};

byte eletrogateChar3[] = {
  B01100,
  B01100,
  B01111,
  B11111,
  B11000,
  B10000,
  B00000,
  B00011
};

byte eletrogateChar4[] = {
  B11000,
  B00000,
  B00001,
  B00011,
  B11111,
  B11110,
  B00110,
  B00110
};

byte eletrogateChar5[] = {
  B00000,
  B11011,
  B11011,
  B10001,
  B00000,
  B00000,
  B01010,
  B01010
};

byte eletrogateChar6[] = {
  B00011,
  B00000,
  B10000,
  B11000,
  B11111,
  B01111,
  B01100,
  B01100
};

void setup() {
  lcd.begin(); // start the display

  //loads each array into display memory
  lcd.createChar(eletrogateChar,0)
    .createChar(eletrogateChar2,1)
    .createChar(eletrogateChar3,2)
    .createChar(eletrogateChar4,3)
    .createChar(eletrogateChar5,4)
    .createChar(eletrogateChar6,5);

  //repositioning the cursor (this action is necessary every time a custom character is loaded)
  lcd.setCursor(0, 0);


  //write the first 3 chars of the logo
  lcd.write(0);
  lcd.write(1);
  lcd.write(2);

  //moving to line 2
  lcd.setCursor(1, 0);

  //write the last 3 chars of the logo
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);


  lcd.print("ELETROGATE");
  lcd.setCursor(0, 3);
  lcd.print("Blog");

}

void loop(){
}
