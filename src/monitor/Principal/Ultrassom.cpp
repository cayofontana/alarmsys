#include "Ultrassom.h"

Ultrassom::Ultrassom(uint8_t pinoEcho, uint8_t pinoTrigger, uint16_t frequencia, uint16_t intervalo, uint16_t distancia, uint16_t limiteDeteccoes)
    : Sensor(pinoEcho, frequencia, intervalo, limiteDeteccoes)
{
        this->pinoTrigger = pinoTrigger;
        this->distancia = distancia;
        distanciaEcoada = 0;
}

void
Ultrassom::detectar(void)
{
        if (deveExecutar())
        {
                setIntervalo(getFrequencia());
                executar();
                Sensor::detectar();
        }
}

void
Ultrassom::executar(void)
{
        digitalWrite(pinoTrigger, LOW);
        delayMicroseconds(2);
        
        digitalWrite(pinoTrigger, HIGH);
        delayMicroseconds(10);
        digitalWrite(pinoTrigger, LOW);
        
        distanciaEcoada = pulseIn(getPinoEcho(), HIGH);
        distanciaEcoada *= velocidadeSom / 2;
        
        if (distanciaEcoada < distancia)
                aumentarDeteccoes();
        else
                resetarDeteccoes();
        
        executado();
}