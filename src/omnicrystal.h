//classe principal
#ifndef OMNICRYSTAL_H
#define OMNICRYSTAL_H

#include <Arduino.h>
#include <stdint.h>
#include <interface/defultmodules.h>
#include <interface/lcdinterface.h>

enum BusType {Bus4Bits, Bus8Bits};

class Omnicrystal{
    private:
        LCDInterface &_bridge;
        const BusType _bus; // tipo de comunicação 4 ou 8 bits
        const uint8_t _line; // quantidade de linhas no display
        const uint8_t _col; //quantidade de colunas por linhas
        void send4Bits(uint8_t data, uint8_t RS_state);
        void send8Bits(uint8_t data, uint8_t RS_state);
        void send(uint8_t data, uint8_t RS_state);

    public:
        Omnicrystal(LCDInterface &bridge, const BusType bus, uint8_t line, uint8_t col) : _bridge{bridge}, _bus{bus},
            _line{line}, _col{col}{}
        Omnicrystal& begin();
        Omnicrystal& write(const char *text);
};

#endif
