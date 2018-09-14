#ifndef SENSOR_H
#define SENSOR_H

#include "Thread.h"

class Sensor: public Thread
{
public:
        Sensor(uint8_t pinoEcho, uint8_t pinoTrigger, uint16_t frequencia, uint16_t intervalo, uint16_t limiteDeteccoes);

        uint16_t getFrequencia();
        uint8_t getPinoEcho();
        
        bool existeObjeto(void);
        void detectar(void);

        void aumentarDeteccoes();
        void resetarDeteccoes();

private:
        uint8_t pinoEcho;
        uint16_t frequencia;
        uint16_t intervalo;
        uint16_t limiteDeteccoes;
	uint8_t deteccoes;
        bool objetoDetectado;
};

#endif
