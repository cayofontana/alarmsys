#ifndef SENSORULTRASONICO_H
#define SENSORULTRASONICO_H

#include <Arduino.h>
#include <stdint.h>

#include "Thread.h"

#define MAXIMA_DISTANCIA 50
#define MINIMO_DETECCAO 30

class SensorUltrasonico: public Thread
{
public:
        SensorUltrasonico(uint8_t pinoEcho, uint8_t pinoTrigger, uint16_t frequencia, uint16_t intervalo);
        bool existeObjeto(void);
        void detectar(void);

private:
      	const float velocidadeSom = 0.034;
      	uint8_t pinoEcho;
      	uint8_t pinoTrigger;
      	unsigned long distanciaEcoada;
      	uint16_t frequencia;
      	uint16_t intervalo;
      	uint8_t deteccoes;
      	bool objetoDetectado;
      	
      	void run();
};

#endif
