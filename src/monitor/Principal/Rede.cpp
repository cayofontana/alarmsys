#include "Rede.h"

Rede::Rede(const char *nome, const char *senha) : nome(nome), senha(senha)
{
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
        WiFiClient clienteWiFi;
        int codigoRetornoHTTP;
        bool dados_Enviados;

        clienteHTTP.begin(clienteWiFi, (String)"http://" + endereco + (String)":" + porta + (String)"/" + arquivo + (String)"?distancia_media=" + (String)valor);
        codigoRetornoHTTP = clienteHTTP.GET();
        dados_Enviados = (codigoRetornoHTTP < 0 || codigoRetornoHTTP != HTTP_CODE_OK) ? false : true;
        clienteWiFi.stop();
        clienteHTTP.end();

        return (dados_Enviados);
}

void
Rede::desconectar(void)
{
        WiFi.disconnect(true);
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
