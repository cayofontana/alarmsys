#ifndef REDE_H
#define REDE_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

class Rede
{
public:
        Rede(const char *nome, const char *senha);
        
        bool conectar(void);
        bool enviarDados(const char *endereco, uint16_t porta, const char *arquivo, uint16_t valor);
        void desconectar(void);

private:
        const char *nome;
        const char *senha;
        
        void criarConexao(void);
        bool estahConectado(void);
};

#endif
