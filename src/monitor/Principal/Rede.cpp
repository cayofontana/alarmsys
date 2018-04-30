#include "Rede.h"

Rede::Rede(char *nome, char *senha)
{
        this->nome = nome;
        this->senha = senha;
}

bool
Rede::conectar(void)
{
        uint8_t i;
        
        if (estahConectado())
                return (true);
        else
        {
                criarConexao();
                
                for (i = 0; i < 20; i++)
                {
                        if (!estahConectado())
                        {
                                delay(500);
                                continue;
                        }

                        return (true);
                }
                
                desconectar();
                
                return (false);
        }
}

bool
Rede::enviarDados(char *endereco, uint8_t porta, char *arquivo, uint16_t valor)
{
        WiFiClient cliente;
        
        if (cliente.connect(endereco, porta))
        {
                cliente.print(
                String("GET /") + arquivo + ":" + porta + "?distancia_media=" + valor + " HTTP/1.1\r\n" +
                "Host: " + endereco + "\r\n" +
                "Connection: close\r\n" +
                "\r\n"
                );
                
                return (true);
        }
        
        cliente.stop();
        
        return (false);
}

void
Rede::desconectar(void)
{
        WiFi.disconnect();
}

void
Rede::criarConexao(void)
{
        WiFi.mode(WIFI_STA);
        WiFi.begin(nome, senha);
}

bool
Rede::estahConectado(void)
{
        return (WiFi.status() == WL_CONNECTED);
}
