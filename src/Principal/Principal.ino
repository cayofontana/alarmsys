#include "SensorUltrasonico.h"

#define LIMITE 50

SensorUltrasonico SensorUltrasonico(16, 14);
const uint8_t pinoSirene = 4;

void setup()
{
        Serial.begin(115200);
        
        inicializarPinos();
}

void loop()
{
        if (SensorUltrasonico.obterMedicao() < LIMITE)
                digitalWrite(pinoSirene, HIGH);
        else
                digitalWrite(pinoSirene, LOW);
}

void inicializarPinos()
{
        pinMode(SensorUltrasonico.getPinoEcho(), OUTPUT);
        pinMode(SensorUltrasonico.getPinoTrigger(), INPUT);
        pinMode(pinoSirene, OUTPUT);
}

