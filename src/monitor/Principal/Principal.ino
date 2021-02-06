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
#include "Sirene.h"

std::vector<std::shared_ptr<Sensor>> sensores;
Rede rede("CAYO", "cayo220383");
Sirene sirene(15);
bool dadosEnviados;

void setup() {
        Serial.begin(115200);

        sensores.push_back(std::make_shared<Ultrassom>(5, 300, 15000, 4, 50, 20));
        sensores.push_back(std::make_shared<Ultrassom>(13, 300, 15000, 12, 50, 20));
        sensores.push_back(std::make_shared<InfraVermelho>(10, 10, 15000));
        
        dadosEnviados = false;
}

void loop() {
        bool objetoDetectado = false;
        
        for (std::vector<std::shared_ptr<Sensor>>::iterator sensor = sensores.begin(); sensor != sensores.end(); ++sensor)
                (*sensor)->detectar();

        for (std::vector<std::shared_ptr<Sensor>>::iterator sensor = sensores.begin(); sensor != sensores.end(); ++sensor) {
                if (!(*sensor)->existeObjeto()) {
                        objetoDetectado = false;
                        dadosEnviados = false;
                        break;
                }
                objetoDetectado = true;
        }

        enviarMensagem(objetoDetectado, dadosEnviados);
}

void enviarMensagem(bool objetoDetectado, bool dadosEnviados) {
        if (objetoDetectado && !dadosEnviados && rede.conectar()) {
                sirene.ligar();
                rede.enviarDados("192.168.0.121", 8080, "cadastrodeteccao.jsp", 10);
                dadosEnviados = !dadosEnviados;
                rede.desconectar();
        }
        else
                sirene.desligar();
}
