#ifndef SENSORULTRASONICO_H
#define SENSORULTRASONICO_H

#include "Thread.h"

class SensorUltrasonico: public Thread
{
public:
        SensorUltrasonico(uint8_t pinoEcho, uint8_t pinoTrigger, uint16_t frequencia, uint16_t intervalo, uint16_t distancia, uint16_t limiteDeteccoes);
        bool existeObjeto(void);
        void detectar(void);

private:
      	const float velocidadeSom = 0.034;
      	uint8_t pinoEcho;
      	uint8_t pinoTrigger;
      	unsigned long distanciaEcoada;
      	uint16_t frequencia;
      	uint16_t intervalo;
        uint16_t distancia;
        uint16_t limiteDeteccoes;
      	uint8_t deteccoes;
      	bool objetoDetectado;
      	
      	void executar();
};

#endif
