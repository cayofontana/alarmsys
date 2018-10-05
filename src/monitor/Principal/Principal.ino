#include <vector>
#include "Sensor.h"
#include "Ultrassom.h"
#include "InfraVermelho.h"
#include "Rede.h"

std::vector<std::shared_ptr<Sensor>> sensores;
Rede rede("CAYO", "abc@123.");
const uint8_t pinoSirene = 4;

void setup()
{
        Serial.begin(115200);
        pinMode(pinoSirene, OUTPUT);

        sensores.push_back(std::make_shared<Ultrassom>(12, 300, 15000, 13, 50, 20));
        sensores.push_back(std::make_shared<Ultrassom>(5, 300, 15000, 4, 50, 20));
        sensores.push_back(std::make_shared<InfraVermelho>(14, 10, 15000));
}

void loop()
{
        bool objetoDetectado = false;
        
        for (std::vector<std::shared_ptr<Sensor>>::iterator sensor = sensores.begin(); sensor != sensores.end(); ++sensor)
                (*sensor)->detectar();

        for (std::vector<std::shared_ptr<Sensor>>::iterator sensor = sensores.begin(); sensor != sensores.end(); ++sensor)
        {
                if (!(*sensor)->existeObjeto())
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
