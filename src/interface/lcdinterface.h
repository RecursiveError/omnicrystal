//Interface customizavel para displays LCD alfanumericos
#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#include <stdint.h>

struct LCDInterface{
    virtual void send(uint8_t config, uint8_t data) = 0;
};

#endif