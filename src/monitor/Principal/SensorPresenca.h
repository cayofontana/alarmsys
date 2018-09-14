#ifndef SENSORPRESENCA_H
#define SENSORPRESENCA_H

#include "Sensor.h"

class SensorPresenca: public Sensor
{
public:
	SensorPresenca(uint8_t pinoEcho, uint16_t frequencia, uint16_t intervalo, uint16_t tempoCalibracao, uint16_t limiteDeteccoes);
	void detectar(void);

private:
	uint16_t tempoCalibracao;
	void executar(void);
}