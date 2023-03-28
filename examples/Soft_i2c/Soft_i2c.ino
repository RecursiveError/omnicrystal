/*soft_i2c cunstom interface Exemple
Author: Guilherme Silva Schultz
Data: 2023-03-22

this example uses the library:
https://github.com/felias-fogg/SoftI2CMaster

*/

//made to run on arduino uno
//change settings according to your board

//Arduino Uno pin 13
#define SCL_PIN 5
#define SCL_PORT PORTB

//Arduino Uno pin 12
#define SDA_PIN 4
#define SDA_PORT PORTB

#include <omnicrystal.h>
#include <SoftI2CMaster.h>

//Implements LCDinterface
class LCDPCF8574_SOFT : public LCDInterface{
  private:
    const uint8_t _addr;
  public:
    LCDPCF8574_SOFT(const uint8_t addr) : _addr{addr}
    {i2c_init();}
    void send(uint8_t config, uint8_t data){
      /*
      The first 3 Low Bits of PCF8574 correspond respectively
      RS - R/W - EN

      0x08 is the backlight

      the last 4 high bits correspond to the data pins
      */
      uint8_t package = (config & 0b00000111) | (data & 0xF0) | 0x08;
      i2c_start((_addr<<1)|I2C_WRITE);
      i2c_write(package);
      i2c_stop();
  }
};

//that's all you need to create a custom interface, now just use it.
LCDPCF8574_SOFT interface(0x27);
Omnicrystal lcd(interface, Bus4Bits, 2, 16);

void setup() {
  lcd.begin();
  lcd.print("hello SoftI2C!!");
}

void loop() {
}
