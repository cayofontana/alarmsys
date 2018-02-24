#include "SensorUltrasonico.h"

SensorUltrasonico sensorUltrasonico(12, 13);
const uint8_t pinoSirene = 4;

void setup()
{
        Serial.begin(115200);
        pinMode(pinoSirene, OUTPUT);
}

void loop()
{
        if (sensorUltrasonico.existeObjeto())
        {
                digitalWrite(pinoSirene, HIGH);
                delay(5000);
        }
        else
                digitalWrite(pinoSirene, LOW);
}
