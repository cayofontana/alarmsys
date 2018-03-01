#include <vector>
#include "SensorUltrasonico.h"
#include "Rede.h"

std::vector<SensorUltrasonico> sensoresUltrasonicos;
Rede rede("CAYO", "abc@123.");
const uint8_t pinoSirene = 4;

void setup()
{
        Serial.begin(115200);
        pinMode(pinoSirene, OUTPUT);

        rede.desconectar();

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

        if (objetoDetectado && digitalRead(pinoSirene) == LOW)
        {
                digitalWrite(pinoSirene, HIGH);
                if (rede.conectar())
                        rede.enviarDados("192.168.0.102", 80, "cadastrodeteccao.php", 10);
        }
        else if (!objetoDetectado)
                digitalWrite(pinoSirene, LOW);
}
