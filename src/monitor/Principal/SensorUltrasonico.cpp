#include "SensorUltrasonico.h"

SensorUltrasonico::SensorUltrasonico(uint8_t pinoEcho, uint8_t pinoTrigger, uint16_t frequencia, uint16_t intervalo, uint16_t distancia, uint16_t limiteDeteccoes)
    : Sensor(pinoEcho, pinoTrigger, frequencia, intervalo, limiteDeteccoes)
{
      	this->distancia = distancia;
      	distanciaEcoada = 0;
}

void
SensorUltrasonico::detectar(void)
{
        if (deveExecutar())
        {
                setIntervalo(getFrequencia());
                executar();
                Sensor::detectar();
        }
}

void
SensorUltrasonico::executar()
{
        digitalWrite(getPinoTrigger(), LOW);
        delayMicroseconds(2);
        
        digitalWrite(getPinoTrigger(), HIGH);
        delayMicroseconds(10);
        digitalWrite(getPinoTrigger(), LOW);
        
        distanciaEcoada = pulseIn(getPinoEcho(), HIGH);
        distanciaEcoada *= velocidadeSom / 2;
        
        if (distanciaEcoada < distancia)
                aumentarDeteccoes();
        else
                resetarDeteccoes();
        
        executado();
}
