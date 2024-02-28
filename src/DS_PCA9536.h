#ifndef DS_PCA9536_h
#define DS_PCA9536_h

#include "Arduino.h"
#include <Wire.h>

#define PCA_ADDRESS 0x41    //Default I2C Address

//Commands
#define INPUT_PORT 0x00     // Input Port register
#define OUTPUT_PORT 0x01    // Output Port register
#define POLARITY_INV 0x02   // Polarity Inversion register
#define CONFIG 0x03         // Configuration register

//Pin Values
#define INPUT 1         // Set pin as an input
#define OUTPUT 0        // Set pin as an output

#define INVERT 1        // Invert pin polarity
#define NORMAL 0        // Normal pin polarity

struct PCA9536Data {
    bool bit0;
    bool bit1;
    bool bit2;
    bool bit3;
};

class PCA9536
{
    public:
        PCA9536();
        virtual ~PCA9536(){};

        bool begin(void);
        void reset(void);

        bool read(PCA9536Data&);
        void write(bool, bool, bool, bool);

        void invert(bool, bool, bool, bool);
        void config(bool, bool, bool, bool);
};

extern PCA9536Data pcadata;

#endif