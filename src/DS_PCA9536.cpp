#include "Arduino.h"
#include <Wire.h>
#include "DS_PCA9536.h"

PCA9536::PCA9536(void){};

bool PCA9536::begin(void)
{
    Wire.begin();
    delay(100);
    Wire.beginTransmission(PCA_ADDRESS);
    bool error = Wire.endTransmission();
    if(error == 0){
        Wire.beginTransmission(PCA_ADDRESS);
        Wire.write(POLARITY_INV);
        Wire.write(0x00);   // Set all pins to normal polarity
        Wire.endTransmission();
        delay(10);
        Wire.beginTransmission(PCA_ADDRESS);
        Wire.write(CONFIG);
        Wire.write(0xFF);   // Set all pins to be inputs
        Wire.endTransmission();
        return true;
    }
    else{
        return false;
    }
}

void PCA9536::reset(void)
{
    Wire.beginTransmission(PCA_ADDRESS);
    Wire.write(POLARITY_INV);
    Wire.write(0x00);   // Set all pins to normal polarity
    Wire.endTransmission();
    delay(10);
    Wire.beginTransmission(PCA_ADDRESS);
    Wire.write(CONFIG);
    Wire.write(0xFF);   // Set all pins to be inputs
    Wire.endTransmission();
}

bool PCA9536::read(PCA9536Data_t &pcadata)
{
    Wire.beginTransmission(PCA_ADDRESS);
    Wire.write(INPUT_PORT);
    Wire.endTransmission();
    Wire.requestFrom(PCA_ADDRESS, 1);
    if(!Wire.available()){
        return -1, -1, -1, -1;
    }
    uint8_t incomingByte = Wire.read();
    bool bit0, bit1, bit2, bit3;
    pcadata.bit0 = (incomingByte & 0x01);
    pcadata.bit1 = (incomingByte & 0x02);
    pcadata.bit2 = (incomingByte & 0x03);
    pcadata.bit3 = (incomingByte & 0x04);

    return pcadata.bit0, pcadata.bit1, pcadata.bit2, pcadata.bit3;
}

void PCA9536::write(bool bit0, bool bit1, bool bit2, bool bit3)
{
    uint8_t outgoingByte = (bit0 << 0) | (bit1 << 1) | (bit2 << 2) | (bit3 << 3) | 0xF0;
    Wire.beginTransmission(PCA_ADDRESS);
    Wire.write(OUTPUT_PORT);
    Wire.write(outgoingByte);
    Wire.endTransmission();
}

void PCA9536::invert(bool bit0, bool bit1, bool bit2, bool bit3)
{
    uint8_t outgoingByte = (bit0 << 0) | (bit1 << 1) | (bit2 << 2) | (bit3 << 3);
    Wire.beginTransmission(PCA_ADDRESS);
    Wire.write(POLARITY_INV);
    Wire.write(outgoingByte);
    Wire.endTransmission();
}

void PCA9536::config(bool bit0, bool bit1, bool bit2, bool bit3)
{
    uint8_t outgoingByte = (bit0 << 0) | (bit1 << 1) | (bit2 << 2) | (bit3 << 3) | 0xF0;
    Wire.beginTransmission(PCA_ADDRESS);
    Wire.write(CONFIG);
    Wire.write(outgoingByte);
    Wire.endTransmission();
}