#include <vector>
#include "SensorUltrasonico.h"

using namespace std;

vector<SensorUltrasonico> sensoresUltrasonicos;
const uint8_t pinoSirene = 4;

void setup()
{
        Serial.begin(115200);
        pinMode(pinoSirene, OUTPUT);

        sensoresUltrasonicos.reserve(2);
        sensoresUltrasonicos.push_back(SensorUltrasonico(12, 13, 50, 5000));
        sensoresUltrasonicos.push_back(SensorUltrasonico(5, 2, 50, 5000));
}

void loop()
{
        bool detectou;
        
        for (vector<SensorUltrasonico>::iterator sensorUltrasonico = sensoresUltrasonicos.begin(); sensorUltrasonico != sensoresUltrasonicos.end(); ++sensorUltrasonico)
        {
                if (!sensorUltrasonico->detectar())
                {
                        detectou = false;
                        break;
                }
                else
                        detectou = true;
        }

        if (detectou)
                digitalWrite(pinoSirene, HIGH);
        else
                digitalWrite(pinoSirene, LOW);
}

