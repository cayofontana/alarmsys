#include "InfraVermelho.h"

InfraVermelho::InfraVermelho(uint8_t pinoEntrada, uint16_t frequencia, uint16_t intervalo) : Sensor(pinoEntrada, frequencia, intervalo)
{
}

void
InfraVermelho::detectar(void)
{
        if (deveExecutar())
        {
                setIntervalo(getFrequencia());
                executar();

                if (objetoDetectado)
                        setIntervalo(getIntervalo());
        }
}

void
InfraVermelho::executar(void)
{
        if (digitalRead(getPinoEntrada()) > 0)
        {
                objetoDetectado = true;
                Serial.print("OBJETO DETECTADO! Pino ");
                Serial.print(getPinoEntrada());
                Serial.println(". Inativo por 15 segundos.");
        }
        else
                objetoDetectado = false;
        
        executado();
}
