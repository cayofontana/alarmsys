#include "SensorUltrasonico.h"

SensorUltrasonico::SensorUltrasonico(uint8_t pinoEcho, uint8_t pinoTrigger, uint16_t frequencia, uint16_t intervalo)
{
	this->pinoEcho = pinoEcho;
	this->pinoTrigger = pinoTrigger;
	this->frequencia = frequencia;
	this->intervalo = intervalo;
	distanciaEcoada = deteccoes = 0;
	objetoDetectado = false;
	pinMode(pinoEcho, INPUT);
	pinMode(pinoTrigger, OUTPUT);
}

bool
SensorUltrasonico::detectar(void)
{
	if (shouldRun())
	{
		setInterval(frequencia);
		run();

		if (deteccoes > MINIMO_DETECCAO)
		{
			setInterval(intervalo);
			objetoDetectado = true;
		}
		else
			objetoDetectado = false;
	}

	return (objetoDetectado);
}

void
SensorUltrasonico::run()
{
	digitalWrite(pinoTrigger, LOW);
	delayMicroseconds(2);

	digitalWrite(pinoTrigger, HIGH);
	delayMicroseconds(10);
	digitalWrite(pinoTrigger, LOW);

	distanciaEcoada = pulseIn(pinoEcho, HIGH);
	distanciaEcoada *= velocidadeSom / 2;

	if (distanciaEcoada < MAXIMA_DISTANCIA)
		deteccoes++;
	else
		deteccoes = 0;

	runned();
}