//classe principal
#ifndef OMNICRYSTAL_H
#define OMNICRYSTAL_H

#include <Arduino.h>
#include <Print.h>
#include <stdint.h>
#include <interface/defultmodules.h>
#include <interface/lcdinterface.h>

enum BusType {Bus4Bits, Bus8Bits};

//comandos do LCD
enum LCDCommand {
    LCDClear = 0x01,
    LCDReset = 0x02,
    LCDShiftCursotLeft = 0x10,
    LCDShiftCursotRight = 0x14,
    LCDShiftDisplayLeft = 0x18,
    LCDShiftDisplayRight = 0x1C,
};


class Omnicrystal : public Print{
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

        //envia o codigo dos comandos
        Omnicrystal& command(LCDCommand);
        //funçoes para enviar cada um dos comandos
        Omnicrystal& clear();
        Omnicrystal& reset();
        Omnicrystal& move_cursor_left();
        Omnicrystal& move_cursor_right();
        Omnicrystal& move_display_left();
        Omnicrystal& move_display_right();


        Omnicrystal& begin();
        virtual size_t write(uint8_t);
};

#endif
