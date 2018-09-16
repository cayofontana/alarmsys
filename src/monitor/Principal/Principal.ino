#include <vector>
#include "Sensor.h"
#include "Rede.h"

std::vector<Sensor> sensores;
Rede rede("CAYO", "abc@123.");
const uint8_t pinoSirene = 4;

void setup()
{
        Serial.begin(115200);
        pinMode(pinoSirene, OUTPUT);

        sensores.push_back(Ultrassom(12, 13, 300, 15000, 50, 20));
        sensores.push_back(Ultrassom(5, 2, 300, 15000, 50, 20));
        sensores.push_back(Ultrassom(14, 16, 300, 15000, 50, 20));
}

void loop()
{
        bool objetoDetectado;
        
        for (std::vector<Sensor>::iterator sensor = sensores.begin(); sensor != sensores.end(); ++sensor)
                sensor->detectar();

        for (std::vector<Sensor>::iterator sensor = sensores.begin(); sensor != sensores.end(); ++sensor)
        {
                if (!sensor->existeObjeto())
                {
                        objetoDetectado = false;
                        break;
                }
                objetoDetectado = true;
        }

        if (objetoDetectado && digitalRead(pinoSirene) == LOW)
        {
                digitalWrite(pinoSirene, HIGH);
                if (rede.conectar())
                        rede.enviarDados("192.168.0.102", 8080, "cadastrodeteccao.jsp", 10);
        }
        else if (!objetoDetectado)
                digitalWrite(pinoSirene, LOW);
}