#ifndef SENSORULTRASONICO_H
#define SENSORULTRASONICO_H

#include <Arduino.h>
#include <stdint.h>

#define MAXIMA_DISTANCIA 50
#define MINIMO_DETECCAO 30

class SensorUltrasonico
{
public:
	SensorUltrasonico(uint8_t pinoEcho, uint8_t pinoTrigger);
	bool existeObjeto(void);

private:
	const float velocidadeSom = 0.034;
	uint8_t pinoEcho;
	uint8_t pinoTrigger;
	unsigned long intervalo;
	uint8_t deteccoes;
	void inicializar(void);
	uint16_t obterMedicao(void);
};

#endif