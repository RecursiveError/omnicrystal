#include <omnicrystal.h>

void Omnicrystal::send8Bits(uint8_t data, uint8_t RS_state){
    _bridge.send(RS_state, data);
    _bridge.send(RS_state | enable_set, data);
    delayMicroseconds(1);
    _bridge.send(RS_state, data);
}

//divide 8 bits em dois pacotes de 4bits
//(Ex: tranforma 0b01101001 em 0b01100000 e 0b10010000)
void Omnicrystal::send4Bits(uint8_t data, uint8_t RS_state){
    uint8_t high_nibble = data & 0xF0;
    uint8_t low_nibble = data << 4;
    send8Bits(high_nibble, RS_state);
    delayMicroseconds(1);
    send8Bits(low_nibble, RS_state);
}

void Omnicrystal::send(uint8_t data, uint8_t RS_state){
    if(_bus == Bus8Bits){
        send8Bits(data, RS_state);
    }else{
        send4Bits(data, RS_state);
    }

    if(RS_state == 1){
        delayMicroseconds(2);
    }
    else{
        delayMicroseconds(40);
    }
}

Omnicrystal& Omnicrystal::begin(){
    delay(50);//aguarda o LCD iniciar
    send8Bits(0x30, 0);
    delayMicroseconds(4100);
    send8Bits(0x30, 0);
    delayMicroseconds(100);
    send8Bits(0x30, 0);
    delayMicroseconds(100);

    //configura o modo de comunicação corretamente
    if(_bus == Bus4Bits){
        send8Bits(0x20, 0);
    }

    //envias as configuraçoes padroes do LCD
    send(function_set, 0);
    clear();
    reset();
    send(entry_mode, 0); //liga modo incremental do display
    send(display_control, 0); //LCD on, cursor on, cursor piscando
    selectLcd(0);
    return *this;
}

size_t Omnicrystal::write(uint8_t data){
    if((data == '\n') || (data == '\r')){
        return 0;
    }
    send(data, 1);
    return 1;
}

/* ----------------- COMANDOS DO DISPLAY ---------------------*/
//envia comandos para o display
inline Omnicrystal& Omnicrystal::command(LCDCommand command){
    send(command, 0); //0 indica RS em low, significa que vamos envar um comando
    return *this; //apenas para encadeamento de metodos
}

Omnicrystal& Omnicrystal::clear(){
    command(LCDClear);
    delay(2); //clear e reset demoram 1.52ms para executar
    return *this;
}

Omnicrystal& Omnicrystal::reset(){
    command(LCDReset);
    delay(2); //clear e reset demoram 1.52ms para executar
    return *this;
}

inline Omnicrystal& Omnicrystal::moveCursorLeft(){
    command(LCDShiftCursotLeft);
    return *this;
}

inline Omnicrystal& Omnicrystal::moveCursorRight(){
    command(LCDShiftCursotRight);
    return *this;
}

inline Omnicrystal& Omnicrystal::moveDisplayLeft(){
    command(LCDShiftDisplayLeft);
    return *this;
}

inline Omnicrystal& Omnicrystal::moveDisplayRight(){
    command(LCDShiftCursotRight);
    return *this;
}

/* ----------------- FIM DOS COMANDOS DO DISPLAY ---------------------*/

/* ------------------ CONFIGURAÇÃO DO DISPLAY ------------------------*/

/*
essas funçoes recebem a posição em bit da flag na enum de cada configuração
liga os bits de acordo com a configuração, "on" coloca o bit em 1, "off" coloca o bit wm 0
*/

//configura o autoshift
Omnicrystal& Omnicrystal::shiftOn(){
    entry_mode |= LCDShiftMode;
    send(entry_mode, 0);
    return *this;
}

Omnicrystal& Omnicrystal::shiftOff(){
    entry_mode &= ~LCDShiftMode;
    send(entry_mode, 0);
    return *this;
}

//diz se ele aumenta ou diminue a posição apos cada letra
Omnicrystal& Omnicrystal::increment(){
    entry_mode |= LCDDirection;
    send(entry_mode,0);
    return *this;
}

Omnicrystal& Omnicrystal::decrement(){
    entry_mode &= ~LCDDirection;
    send(entry_mode,0);
    return *this;
}

//liga e desliga se o cursor piscando
Omnicrystal& Omnicrystal::cursorBlinkOn(){
    display_control |= LCDBlink;
    send(display_control,0);
    return *this;
}

Omnicrystal& Omnicrystal::cursorBlinkOff(){
    display_control &= ~LCDBlink;
    send(display_control,0);
    return *this;
}

//liga e desliga o cursor
Omnicrystal& Omnicrystal::cursorOn(){
    display_control |= LCDCursor;
    send(display_control,0);
    return *this;
}

Omnicrystal& Omnicrystal::cursorOff(){
    display_control &= ~LCDCursor;
    send(display_control,0);
    return *this;
}

//liga e desliga a exibição
Omnicrystal& Omnicrystal::displayOn(){
    display_control |= LCDDisplay;
    send(display_control,0);
    return *this;
}

Omnicrystal& Omnicrystal::displayOff(){
    display_control &= ~LCDDisplay;
    send(display_control,0);
    return *this;
}
/*------------------- FIM CONFIGURAÇÃO DO DISPLAY ---------------------*/

Omnicrystal& Omnicrystal::setCursor(uint8_t line, uint8_t col){
    if(line < _line){
        if(col < _col){
            send(addrs[line]+col, 0);
        }
    }
    return *this;
}

Omnicrystal& Omnicrystal::createChar(uint8_t c[8], uint8_t pos){
    pos &= 0b00000111;
    send(0x40 | (pos<<3), 0);
    for(size_t i = 0; i < 8; i++){
        send(c[i], 1);
    }
    return *this;
}


Omnicrystal& Omnicrystal::echo(){
    enable_set = 0b1100;
    return *this;
}

Omnicrystal& Omnicrystal::selectLcd(uint8_t enable){
    if(enable < 2){
        enable_set = 0b100<<enable;
    }
    return *this;
}
