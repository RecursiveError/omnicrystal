#include "defultmodules.h"

void LCDParallel::init_pins(){
    pinMode(EN_pin, OUTPUT);
    pinMode(RS_pin, OUTPUT);
    for(size_t i = pins_offset; i < 8; i++){
        pinMode(com_pins[i], OUTPUT);
    }
}

void LCDParallel::send(uint8_t config, uint8_t data){
    digitalWrite(RS_pin, config & 0x01);
    for(size_t i = pins_offset; i < 8; i++){
        digitalWrite(com_pins[i], data & (1 << i));
    }
    digitalWrite(EN_pin, config & 0x04);
}

void LCDPCF8754::send(uint8_t config, uint8_t data){
    uint8_t package = (config & 0b00000111) | (data & 0xF0) | 0x08; //organiza os bits corretamente e envia o pacote
    Wire.beginTransmission(_addr);
    Wire.write(package);
    Wire.endTransmission();
}
