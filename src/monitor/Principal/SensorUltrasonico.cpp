#include "SensorUltrasonico.h"

SensorUltrasonico::SensorUltrasonico(uint8_t pinoEcho, uint8_t pinoTrigger, uint16_t frequencia, uint16_t intervalo, uint16_t distancia, uint16_t limiteDeteccoes)
{
      	this->pinoEcho = pinoEcho;
      	this->pinoTrigger = pinoTrigger;
      	this->frequencia = frequencia;
      	this->intervalo = intervalo;
        this->distancia = distancia;
        this->limiteDeteccoes = limiteDeteccoes;
      	distanciaEcoada = deteccoes = 0;
      	objetoDetectado = false;
      	pinMode(pinoEcho, INPUT);
      	pinMode(pinoTrigger, OUTPUT);
}

bool
SensorUltrasonico::existeObjeto(void)
{
        return (objetoDetectado);
}

void
SensorUltrasonico::detectar(void)
{
        if (deveExecutar())
        {
                setIntervalo(frequencia);
                executar();

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
}

void
SensorUltrasonico::executar()
{
        digitalWrite(pinoTrigger, LOW);
        delayMicroseconds(2);
        
        digitalWrite(pinoTrigger, HIGH);
        delayMicroseconds(10);
        digitalWrite(pinoTrigger, LOW);
        
        distanciaEcoada = pulseIn(pinoEcho, HIGH);
        distanciaEcoada *= velocidadeSom / 2;
        
        if (distanciaEcoada < distancia)
                deteccoes++;
        else
                deteccoes = 0;
        
        executado();
}
