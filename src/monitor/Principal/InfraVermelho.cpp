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

                Serial.println("Tentando detectar.");
                if (objetoDetectado)
                        setIntervalo(getIntervalo());
        }
}

void
InfraVermelho::executar(void)
{
        int valorEntrada = digitalRead(getPinoEntrada());
        Serial.println(valorEntrada);
        if (valorEntrada > 0)
        {
                objetoDetectado = true;
                Serial.print("OBJETO DETECTADO! Pino ");
                Serial.print(getPinoEntrada());
                Serial.print(". Inativo por ");
                Serial.print(getIntervalo() / 1000);
                Serial.println(" segundos.");
        }
        else
                objetoDetectado = false;
        
        executado();
}
