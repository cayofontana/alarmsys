#ifndef ULTRASSOM_H
#define ULTRASSOM_H

#include "Sensor.h"

class Ultrassom: public Sensor
{
public:
        Ultrassom(uint8_t pinoEcho, uint8_t pinoTrigger, uint16_t frequencia, uint16_t intervalo, uint16_t distancia, uint16_t limiteDeteccoes);
        void detectar(void);

private:
        uint8_t pinoTrigger;
      	const float velocidadeSom = 0.034;
      	unsigned long distanciaEcoada;
      	uint16_t distancia;
      	
      	void executar(void);
};

#endif
