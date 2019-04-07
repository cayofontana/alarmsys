// MONITOR - SEAM: Programa Principal
// Descrição: este programa possui uma lista de sensores onde a cada laço (loop)
//            do programa (função loop()), cada elemento (objeto sensor) da lista 
//            verifica se algum objeto foi sensoriado (capturado). Caso todos os 
//            Sensores acusem a presença de um objeto, simultanemanete em um 
//            determinado período, um LED é ligado para informar a detecção conjunta
//            e uma mensagem é enviada ao servidor.

#include <vector>
#include "Sensor.h"
#include "Ultrassom.h"
#include "InfraVermelho.h"
#include "Rede.h"

std::vector<std::shared_ptr<Sensor>> sensores;
Rede rede("CAYO", "abc@123.");
const uint8_t pinoLEDAlarme = 15;

void setup() {
        Serial.begin(115200);
        pinMode(pinoLEDAlarme, OUTPUT);
        digitalWrite(pinoLEDAlarme, LOW);

        sensores.push_back(std::make_shared<Ultrassom>(5, 300, 15000, 4, 50, 20));
        sensores.push_back(std::make_shared<Ultrassom>(13, 300, 15000, 12, 50, 20));
        sensores.push_back(std::make_shared<InfraVermelho>(10, 10, 15000));
}

void loop() {
        bool objetoDetectado = false;
        
        for (std::vector<std::shared_ptr<Sensor>>::iterator sensor = sensores.begin(); sensor != sensores.end(); ++sensor)
                (*sensor)->detectar();

        for (std::vector<std::shared_ptr<Sensor>>::iterator sensor = sensores.begin(); sensor != sensores.end(); ++sensor) {
                if (!(*sensor)->existeObjeto()) {
                        objetoDetectado = false;
                        break;
                }
                objetoDetectado = true;
        }

        if (objetoDetectado && rede.conectar()) {
                rede.enviarDados("192.168.0.102", 8080, "cadastrodeteccao.jsp", 10);
                objetoDetectado = !objetoDetectado;
                digitalWrite(pinoLEDAlarme, HIGH);
        }
        else
                digitalWrite(pinoLEDAlarme, LOW);
}