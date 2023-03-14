//classe principal
#ifndef OMNICRYSTAL_H
#define OMNICRYSTAL_H

#include <Arduino.h>
#include <Print.h>
#include <stdint.h>
#include <interface/defultmodules.h>
#include <interface/lcdinterface.h>

enum BusType {
    Bus4Bits,
    Bus8Bits = 0x10,
};

//comandos do LCD
enum LCDCommand {
    LCDClear = 0x01,
    LCDReset = 0x02,
    LCDShiftCursotLeft = 0x10,
    LCDShiftCursotRight = 0x14,
    LCDShiftDisplayLeft = 0x18,
    LCDShiftDisplayRight = 0x1C,
};


enum LCDEntryMode{
    LCDShiftMode = 0x01,
    LCDDirection = 0x02,
};

enum LCDDisplayControl{
    LCDBlink = 0x01,
    LCDCursor = 0x02,
    LCDDisplay = 0x04,

};

enum LCDFunctionSet{
    LCDChar = 0x04,
    LCDLines = 0x08,
    LCDBits = 0x10,
};

enum LCDCharSize {
    Char5x8,
    Char5x10 = 0x04,
};

class Omnicrystal : public Print{
    private:
        const uint8_t addrs[4] = {0x80, 0xC0, 0x80+20, 0xC0+20}; //endereços para LCD 16x2 e 20x4
        LCDInterface &_bridge;
        const BusType _bus; // tipo de comunicação 4 ou 8 bits
        const uint8_t _line; // quantidade de linhas no display
        const uint8_t _col; //quantidade de colunas por linhas

        // variaveis de configuração inicializadas com a configuração padrão
        uint8_t entry_mode{0x06}; // shift Off, escrita da esquerda pra direita
        uint8_t display_control{0x0C}; //display ligado, cursor desligado, cursor piscando desligado
        uint8_t function_set{0}; // configurado no construtor

        void send4Bits(uint8_t data, uint8_t RS_state);
        void send8Bits(uint8_t data, uint8_t RS_state);
        void send(uint8_t data, uint8_t RS_state);

    public:
        Omnicrystal(LCDInterface &bridge, const BusType bus, uint8_t line, uint8_t col, LCDCharSize size = Char5x8) : _bridge{bridge}, _bus{bus},
            _line{line}, _col{col}{
            if(_line >= 2){
                function_set = 0x20 | 0x08 | _bus | size;
            }else{
                function_set = 0x20 | _bus | size;
            }
        }

        //envia o codigo dos comandos
        Omnicrystal& command(LCDCommand);
        //funçoes para enviar cada um dos comandos
        Omnicrystal& clear();
        Omnicrystal& reset();
        Omnicrystal& move_cursor_left();
        Omnicrystal& move_cursor_right();
        Omnicrystal& move_display_left();
        Omnicrystal& move_display_right();

        //funçoes para enviar configuração
        Omnicrystal& shift_on();
        Omnicrystal& shift_off();
        Omnicrystal& increment();
        Omnicrystal& decrement();
        Omnicrystal& cursor_blink_on();
        Omnicrystal& cursor_blink_off();
        Omnicrystal& cursor_on();
        Omnicrystal& cursor_off();
        Omnicrystal& display_on();
        Omnicrystal& display_off();
        Omnicrystal& set_cursor(uint8_t line, uint8_t col);

        Omnicrystal& create_char(uint8_t c[8], uint8_t pos);

        Omnicrystal& begin();
        virtual size_t write(uint8_t);
};

#endif
