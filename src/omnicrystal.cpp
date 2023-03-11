#include <omnicrystal.h>

void Omnicrystal::send8Bits(uint8_t data, uint8_t RS_state){
    _bridge.send(RS_state, data);
    _bridge.send(RS_state | 0b00000100, data);
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
        send(0x28, 0);
    }else{
        send(0x38, 0);
    }
    send(0x01, 0); //limpa o LCD
    delay(2);
    send(0x02,0); //Reinicia variaveis internas
    delay(2);
    send(0x06,0); //liga modo incremental do display
    send(0x0F,0); //LCD on, cursor on, cursor piscando
    return *this;
}

size_t Omnicrystal::write(uint8_t data){
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

inline Omnicrystal& Omnicrystal::move_cursor_left(){
    command(LCDShiftCursotLeft);
    return *this;
}

inline Omnicrystal& Omnicrystal::move_cursor_right(){
    command(LCDShiftCursotRight);
    return *this;
}

inline Omnicrystal& Omnicrystal::move_display_left(){
    command(LCDShiftDisplayLeft);
    return *this;
}

inline Omnicrystal& Omnicrystal::move_display_right(){
    command(LCDShiftCursotRight);
    return *this;
}

/* ----------------- FIM DOS COMANDOS DO DISPLAY ---------------------*/
