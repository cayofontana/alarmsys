#include "Rede.h"

Rede::Rede(const char *nome, const char *senha)
{
        this->nome = nome;
        this->senha = senha;
}

bool
Rede::conectar(void)
{
        if (estahConectado())
                return (true);

        criarConexao();
                
        while (!estahConectado())
                delay(500);
        
        return (true);
}

bool
Rede::enviarDados(const char *endereco, uint16_t porta, const char *arquivo, uint16_t valor)
{
        HTTPClient clienteHTTP;
        
        clienteHTTP.begin((String)"http://" + endereco + (String)":" + porta + (String)"/" + arquivo + (String)"?distancia_media=" + (String)valor);
        int codigoRetornoHTTP = clienteHTTP.GET();
        
        if (codigoRetornoHTTP > 0)
                Serial.println("Erro:" + (String)clienteHTTP.getString());
        
        clienteHTTP.end();
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
