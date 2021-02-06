#ifndef SIRENE_H
#define SIRENE_H

#include <Arduino.h>

class Sirene
{
public:
        Sirene(uint8_t);

        void ligar(void);
        void desligar(void);
private:
        uint8_t pino;
};

#endif
