#ifndef INFRAVERMELHO_H
#define INFRAVERMELHO_H

#include "Sensor.h"

class InfraVermelho: public Sensor
{
public:
        InfraVermelho(uint8_t, uint16_t, uint16_t);
        
        void detectar(void);

private:
        int valorEntrada;
        void executar(void);
};

#endif
