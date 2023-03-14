//Modulos Pre-definos para nossa lib
#ifndef DEFULT_MODULES_H
#define DEFULT_MODULES_H

#include <stdint.h>
#include "lcdinterface.h"
#include "Arduino.h"
#include "Wire.h"

class LCDParallel : public LCDInterface{
    private:
        const uint8_t RS_pin;
        const uint8_t EN_pin;
        const uint8_t com_pins[8];
        const uint8_t pins_offset;

        //inicia os pinos usados no LCD
        void init_pins();
    public:
        LCDParallel(uint8_t RS, uint8_t EN, uint8_t D4,uint8_t D5,uint8_t D6, uint8_t D7):
        RS_pin{RS},
        EN_pin{EN},
        com_pins{255, 255, 255, 255, D4, D5, D6, D7},
        pins_offset{4}
        {
            init_pins();
        }
        LCDParallel(uint8_t RS, uint8_t EN, uint8_t D0,uint8_t D1,uint8_t D2, uint8_t D3,
                uint8_t D4, uint8_t D5, uint8_t D6, uint8_t D7):
        RS_pin{RS},
        EN_pin{EN},
        com_pins{D0, D1, D2, D3, D4, D5, D6, D7},
        pins_offset{0}
        {
            init_pins();
        }
        void send(uint8_t config, uint8_t data);
};

//Funciona apenas no mode de 4BITS!!!
class LCDPCF8754 : public LCDInterface{
    private:
        const uint8_t _addr; //endereço I2C
    public:
        LCDPCF8754(const uint8_t addr): _addr{addr}{
            Wire.begin(); //Inicia o I2C do hardware
        }
        void send(uint8_t config, uint8_t data);
};

#endif
