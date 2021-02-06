#ifndef REDE_H
#define REDE_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

class Rede
{
public:
        Rede(const char *, const char *);
        
        bool conectar(void);
        bool enviarDados(const char *, uint16_t, const char *, uint16_t);
        void desconectar(void);

private:
        const char *nome;
        const char *senha;
        
        void criarConexao(void);
        bool estahConectado(void);
};

#endif
