#ifndef INFRAVERMELHO_H
#define INFRAVERMELHO_H

#include "Sensor.h"

class InfraVermelho: public Sensor
{
public:
	InfraVermelho(uint8_t pinoEcho, uint16_t frequencia, uint16_t intervalo, uint16_t tempoCalibracao, uint16_t limiteDeteccoes);
	void detectar(void);

private:
	uint16_t tempoCalibracao;
	void executar(void);
}