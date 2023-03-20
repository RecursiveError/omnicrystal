# omnicrystal
[English version](https://github.com/RecursiveError/omnicrystal/blob/main/README_EN.md)

Biblioteca modular para LCD alfanuméricos compatíveis com HITACHI HD44780 feita com CoreArduino

Essa Biblioteca permite que usuario escolha e crie a interface de comunicação com o display LCD, Essa Biblioteca vem com duas interfaces por padrão: paralela e PCF8754(Wire)

(PCF6754 NÃO ESTÁ IMPLEMTENTADA PARA PLATAFORMA SEM SUPORTE A I2C, use o exemplo de softI2C nessas plataformas)

### Criando sua propria interface 
para criar sua propria interface é bem simples, basta implementar a interface "LCDInterface" com a função send publica.

A função "send" recebe dois parametros uint8_t, "data" e "config", em que seus Bits representam:

| BITS | BIT7 | BIT6 |BIT5| BIT4| BIT3| BIT2| BIT1| BIT0|
| :------ | :------ | :------|  :------| :------| :------| :------| :------| :------|
| DATA | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
| CONFIG | Reserved | Reserved | Reserved | Reserved | EN2 | EN | RW | RS |

o estado de cada bit representa o estado da porta: 1 == HIGH | 0 == LOW

conecte cada bit a sua respectiva porta e pronto voce já tem uma interface funcional
(para trabalhar com PCF8754 voce pode copiar essa linha ```uint8_t package = (config & 0b00000111) | (data & 0xF0) | 0x08; ``` e enviar pela sua biblioteca I2C de sua escolha)
#### exemplo soft_i2c
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
