#include "Sirene.h"

Sirene::Sirene(uint8_t pino) : pino(pino)
{
        pinMode(pino, OUTPUT);
        digitalWrite(pino, LOW);
}

void
Sirene::ligar(void)
{
        digitalWrite(pino, HIGH);
}

void
Sirene::desligar(void)
{
        digitalWrite(pino, HIGH);
}
