#include "InfraVermelho.h"

InfraVermelho::InfraVermelho(uint8_t pinoEntrada, uint16_t frequencia, uint16_t intervalo) : Sensor(pinoEntrada, frequencia, intervalo)
{
}

void
InfraVermelho::detectar(void)
{
        if (deveExecutar())
        {
                setIntervalo(getIntervalo());
                executar();
        }
}

void
InfraVermelho::executar(void)
{
        if (digitalRead(getPinoEntrada()) > 0)
        {
                objetoDetectado = true;
                Serial.print("Pino ");
                Serial.print(getPinoEntrada());
                Serial.print(" detectou!");
        }
        else
                objetoDetectado = false;
        
        executado();
}
