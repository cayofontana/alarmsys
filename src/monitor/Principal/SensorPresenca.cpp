#include "SensorPresenca.h"

SensorPresenca::SensorPresenca(uint8_t pinoEcho, uint8_t pinoTrigger, uint16_t frequencia, uint16_t intervalo, uint16_t tempoCalibracao, uint16_t limiteDeteccoes)
	: Sensor(pinoEcho, pinoTrigger, frequencia, intervalo, limiteDeteccoes)
{
	this.tempoCalibracao = tempoCalibracao;
}

void
SensorPresenca::detectar(void)
{
	if (deveExecutar())
    {
            setIntervalo(getFrequencia());
            executar();
            Sensor::detectar();
    }
}

void
SensorPresenca::executar(void)
{
	if (tempoCalibracao == 0)
	{
		leituraSensor = digitalRead(getPinoEcho());
		if (leituraSensor == 1)
			aumentarDeteccoes();
		else
			resetarDeteccoes();
	}
  else
      tempoCalibracao--;
}
