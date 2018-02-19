#ifndef SENSORULTRASONICO_H
#define SENSORULTRASONICO_H

#include <Arduino.h>
#include <stdint.h>

#define LIMITE 50

class SensorUltrasonico
{
public:
	SensorUltrasonico(uint8_t pinoEcho, uint8_t pinoTrigger);
	uint16_t obterMedicao(void);
	uint8_t getPinoEcho(void);
	uint8_t getPinoTrigger(void);

private:
	const float velocidadeSom = 0.034;
	uint8_t pinoEcho;
	uint8_t pinoTrigger;
	unsigned long intervalo;
};

#endif