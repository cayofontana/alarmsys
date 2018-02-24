#include "SensorUltrasonico.h"

SensorUltrasonico::SensorUltrasonico(uint8_t pinoEcho, uint8_t pinoTrigger)
{
	deteccoes = 0;
	this->pinoEcho = pinoEcho;
	this->pinoTrigger = pinoTrigger;
	inicializar();
}

bool
SensorUltrasonico::existeObjeto(void)
{
	if (obterMedicao() < MAXIMA_DISTANCIA)
		deteccoes++;
	else
		deteccoes = 0;

	if (deteccoes > MINIMO_DETECCAO)
		return (true);
	return (false);
}

void
SensorUltrasonico::inicializar(void)
{
	pinMode(pinoEcho, INPUT);
	pinMode(pinoTrigger, OUTPUT);
}

uint16_t
SensorUltrasonico::obterMedicao(void)
{
	digitalWrite(pinoTrigger, LOW);
	delayMicroseconds(2);

	digitalWrite(pinoTrigger, HIGH);
	delayMicroseconds(10);
	digitalWrite(pinoTrigger, LOW);

	intervalo = pulseIn(pinoEcho, HIGH);

	return (intervalo * velocidadeSom / 2);
}