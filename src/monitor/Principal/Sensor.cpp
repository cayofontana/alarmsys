#include "Sensor.h"

Sensor::Sensor(uint8_t pinoEcho, uint8_t pinoTrigger, uint16_t frequencia, uint16_t intervalo, uint16_t limiteDeteccoes)
{
      	this->pinoEcho = pinoEcho;
      	this->pinoTrigger = pinoTrigger;
      	this->frequencia = frequencia;
      	this->intervalo = intervalo;
        this->limiteDeteccoes = limiteDeteccoes;
        deteccoes = 0;
      	objetoDetectado = false;
      	pinMode(pinoEcho, INPUT);
      	pinMode(pinoTrigger, OUTPUT);
}

uint16_t
Sensor::getFrequencia()
{
        return (frequencia);
}

uint8_t
Sensor::getPinoEcho()
{
        return (pinoEcho);
}

uint8_t
Sensor::getPinoTrigger()
{
        return (pinoTrigger);
}

bool
Sensor::existeObjeto(void)
{
        return (objetoDetectado);
}

void
Sensor::aumentarDeteccoes()
{
        deteccoes++;
}

void Sensor::resetarDeteccoes()
{
        deteccoes = 0;
}

void
Sensor::detectar(void)
{
        // ESTE BLOCO DE CÓDIGO É USADO APENAS PARA TESTE DE SENSIBILIDADE
        // DOS SENSORES, E DEVERÁ SER REMOVIDO APÓS A CONCLUSÃO DO PROJETO.
        Serial.print("Pinos ");
        Serial.print(pinoEcho);
        Serial.print(" e ");
        Serial.print(pinoTrigger);
        Serial.print(": ");
        Serial.println(deteccoes);
        
        if (deteccoes == limiteDeteccoes)
        {
                setIntervalo(intervalo);
                deteccoes = 0;
                objetoDetectado = true;

                // ESTE BLOCO DE CÓDIGO É USADO APENAS PARA TESTE DE SENSIBILIDADE
                // DOS SENSORES, E DEVERÁ SER REMOVIDO APÓS A CONCLUSÃO DO PROJETO.
                Serial.print("OBJETO DETECTADO! Pinos ");
                Serial.print(pinoEcho);
                Serial.print(" e ");
                Serial.print(pinoTrigger);
                Serial.println(". Inativo por 15 segundos.");                        
        }
        else
                objetoDetectado = false;
}
