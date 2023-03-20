# omnicrystal

Modular library for alphanumeric LCD compatible with HITACHI HD44780 made with CoreArduino

This Library allows the user to choose and create the communication interface with the LCD display, This Library comes with two interfaces by default: parallel and PCF8754(Wire)

(PCF6754 IS NOT IMPLEMENTED FOR PLATFORM WITHOUT I2C SUPPORT, use softI2C example on these platforms)

### Creating your own interface 
to create your own interface is very simple, just implement the "LCDInterface" interface with the public send function.

The "send" function receives two uint8_t parameters, "data" and "config", in which their Bits represent:

| BITS | BIT7 | BIT6 |BIT5| BIT4| BIT3| BIT2| BIT1| BIT0|
| :------ | :------ | :------|  :------| :------| :------| :------| :------| :------|
| DATA | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
| CONFIG | Reserved | Reserved | Reserved | Reserved | EN2 | EN | RW | RS |

the state of each bit represents the state of the port: 1 == HIGH | 0 == LOW

connect each bit to its respective port and that's it you already have a functional interface
(to work with PCF8754 you can copy this line ```uint8_t package = (config & 0b00000111) | (data & 0xF0) | 0x08; ``` and send it through I2C library of your choice)

#### example soft_i2c
```c++
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
class LCDPCF8754_SOFT : public LCDInterface{
  private:
    const uint8_t _addr;
  public:
    LCDPCF8754_SOFT(const uint8_t addr) : _addr{addr}
    {i2c_init();}
    void send(uint8_t config, uint8_t data){
      /*
      The first 3 Low Bits of PCF8754 correspond respectively
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
LCDPCF8754_SOFT interface(0x27);
Omnicrystal lcd(interface, Bus4Bits, 2, 16);

void setup() {
  lcd.begin();
  lcd.print("hello SoftI2C!!");
}

void loop() {
}

```
