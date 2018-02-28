#ifndef REDE_H
#define REDE_H

#include <ESP8266WiFi.h>
#include <stdint.h>

class Rede
{
  public:
    Rede(char *nome, char *senha);
    bool conectar(void);
    bool enviarDados(char *endereco, uint8_t porta, char *arquivo, char *mensagem);
    void desconectar(void);

  private:
    char *nome;
    char *senha;
    void criarConexao(void);
    bool estahConectado(void);
};

#endif
