#include <vector>
#include "SensorUltrasonico.h"

std::vector<SensorUltrasonico> sensoresUltrasonicos;
const uint8_t pinoSirene = 4;

void setup()
{
        Serial.begin(115200);
        pinMode(pinoSirene, OUTPUT);

        sensoresUltrasonicos.push_back(SensorUltrasonico(12, 13, 300, 15000));
        sensoresUltrasonicos.push_back(SensorUltrasonico(5, 2, 300, 15000));
        sensoresUltrasonicos.push_back(SensorUltrasonico(14, 16, 300, 15000));
}

void loop()
{
        bool objetoDetectado;
        
        for (std::vector<SensorUltrasonico>::iterator sensorUltrasonico = sensoresUltrasonicos.begin(); sensorUltrasonico != sensoresUltrasonicos.end(); ++sensorUltrasonico)
                sensorUltrasonico->detectar();

        for (std::vector<SensorUltrasonico>::iterator sensorUltrasonico = sensoresUltrasonicos.begin(); sensorUltrasonico != sensoresUltrasonicos.end(); ++sensorUltrasonico)
        {
                if (!sensorUltrasonico->existeObjeto())
                {
                        objetoDetectado = false;
                        break;
                }
                objetoDetectado = true;
        }

        if (objetoDetectado)
                digitalWrite(pinoSirene, HIGH);
        else
                digitalWrite(pinoSirene, LOW);
}
