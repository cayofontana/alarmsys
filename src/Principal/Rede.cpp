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

  Serial.print("Conectando em: ");
  Serial.println(nome);

  if (estahConectado())
  {
    Serial.println("Já está conectado.");
    
    return (true);
  }
  else
  {
    criarConexao();

    Serial.print("Conectando");   
    for (i = 0; i < 20; i++)
    {
      if (!estahConectado())
      {
        Serial.print(".");
        delay(500);
      }
      else
      {
        Serial.print("\nConectado! IP: ");
        Serial.println(WiFi.localIP());

        return (true);
      }
    }

    desconectar();
    Serial.println("\nConexão falhou. :´(");

    return (false);
  }
}

bool
Rede::enviarDados(char *endereco, uint8_t porta, char *arquivo, char *mensagem)
{
  WiFiClient cliente;
  String line;
  bool conectou = false;

  if (cliente.connect(endereco, porta))
  {
    Serial.println("Enviando mensagem");

    cliente.print(
    String("GET /") + arquivo + "?umidade=" + mensagem + " HTTP/1.1\r\n" +
    "Host: " + endereco + "\r\n" +
    "Connection: close\r\n" +
    "\r\n"
    );

    Serial.println("Resposta do servidor:");   
    while (cliente.connected())
    {
      if (cliente.available())
      {
        line = cliente.readStringUntil('\n');
        Serial.println(line);
      }
    }
    Serial.println("\n");

    conectou = true;
  }
  else
    Serial.println("Erro na tentativa de conexão.");

  cliente.stop();

  return (conectou);
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
