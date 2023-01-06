#include "Arduino.h"
#include "mqtt_SIM7600.h"

// Variáveis
String aux2; // String auxiliar2
String a;
int MAXTRIES = 10;

// Objeto 
SoftwareSerial mySerial(3, 2); // Objeto mySerial nos pinos 2 e 3

mqtt_SIM7600::mqtt_SIM7600(int num)
{
  Serial.begin(9600); // Inicia a serial
  mySerial.begin(9600); // Inicia a mySerial
}

void mqtt_SIM7600::rssi()
{
  mySerial.println("AT+CSQ"); //AT Command for Setting up the Subscribe Topic Name 
  delay(3000);
  Serial.println("Lendo retorno do comando.");
  //Receiving MODEM Response
  while(mySerial.available()>0)
  {
    Serial.println("Entrou no while(mySerial.available)");
    delay(10);
    a = mySerial.readString();
    Serial.println(a);
    Serial.println(a.length());
  }
}
 
int mqtt_SIM7600::publica(String host, String token, String topico, String payload)
{
  int tries=0;
  mySerial.println("AT+CRESET"); // Inicia o modem
  delay(20000);
  Serial.println("Lendo retorno do comando.");
  //Receiving MODEM Response
  while(mySerial.available()>0)
  {
    delay(10);
    a = mySerial.readString();
    Serial.println(a);
    Serial.println(a.length());
  }
  while(a.indexOf("OK") == -1 && tries <= MAXTRIES){
    tries++;
    Serial.println("Erro ao iniciar modem!");
    mySerial.println("AT+CRESET"); // Inicia o modem
    delay(3000);
    Serial.println("Lendo retorno do comando.");
    //Receiving MODEM Response
    while(mySerial.available()>0)
    {
      delay(10);
      a = mySerial.readString();
      Serial.println(a);
      Serial.println(a.length());
    }
  }
  if(tries == MAXTRIES){
    Serial.println("Erro fatal. Resetar modem");
    return 1;
  }

  tries = 0;
  mySerial.println("ATE1"); // Inicia o modem
  delay(3000);
  Serial.println("Lendo retorno do comando.");
  //Receiving MODEM Response
  while(mySerial.available()>0)
  {
    delay(10);
    a = mySerial.readString();
    Serial.println(a);
    Serial.println(a.length());
  }
  Serial.println(a);
  Serial.println(a.length());
  while(a.indexOf("OK") == -1 && tries <= MAXTRIES){
    tries++;
    Serial.println("Erro ao iniciar modem!");
    Serial.print("Tentativa"); Serial.println(tries);
    mySerial.println("ATE1"); // Inicia o modem
    delay(3000);
    Serial.println("Lendo retorno do comando.");
    //Receiving MODEM Response
    while(mySerial.available()>0)
    {
      delay(10);
      a = mySerial.readString();
      Serial.println(a);
      Serial.println(a.length());
    }
  }
  if(tries == MAXTRIES){
    Serial.println("Erro fatal. Resetar modem");
    return 1;
  }
  
  tries=0;
  mySerial.println("AT+CMQTTSTART"); // Inicia conexão MQTT
  delay(3000);
  Serial.println("Lendo retorno do comando.");
  //Receiving MODEM Response
  while(mySerial.available()>0)
  {
    delay(10);
    a = mySerial.readString();
    Serial.println(a);
    Serial.println(a.length());
  }
  while(a.indexOf("OK") == -1 && tries <= MAXTRIES){
    tries++;
    Serial.println("Erro ao iniciar MQTT!");
    mySerial.println("AT+CMQTTSTART"); // Inicia o MQTT
    delay(3000);
    Serial.println("Lendo retorno do comando.");
    //Receiving MODEM Response
    while(mySerial.available()>0)
    {
      delay(10);
      a = mySerial.readString();
      Serial.println(a);
    Serial.println(a.length());
    }
  }
  if(tries == MAXTRIES){
    Serial.println("Erro fatal. Resetar modem");
    return 1;
  }

  tries=0;
  mySerial.println("AT+CMQTTACCQ=0,\"Client d\""); // Client ID
  delay(3000);
  Serial.println("Lendo retorno do comando.");
  //Receiving MODEM Response
  while(mySerial.available()>0)
  {
    delay(10);
    a = mySerial.readString();
    Serial.println(a);
    Serial.println(a.length());
  }
  while(a.indexOf("OK") == -1 && tries <= MAXTRIES){
    tries++;
    Serial.println("Erro ao iniciar cliente MQTT!");
    mySerial.println("AT+CMQTTACCQ=0,\"Client d\""); // Client ID
    delay(3000);
    Serial.println("Lendo retorno do comando.");
    //Receiving MODEM Response
    while(mySerial.available()>0)
    {
      delay(10);
      a = mySerial.readString();
      Serial.println(a);
    Serial.println(a.length());
    }
  }
  if(tries == MAXTRIES){
    Serial.println("Erro fatal. Resetar modem");
    return 1;
  }

  String msg;
  msg = "AT+CMQTTCONNECT=0,\"" + host + "\",90,1,\"" + token + "\"";
  Serial.println(msg);

  tries=0;
  mySerial.println(msg); // Conecta ao Servidor MQTT
  //"AT+CMQTTCONNECT=0,\"tcp://demo.thingsboard.io:1883\",90,1,\"uz8xZMgFQkltIc7VpL4A\""
  delay(3000);
  Serial.println("Lendo retorno do comando.");
  //Receiving MODEM Response
  while(mySerial.available()>0)
  {
    delay(10);
    a = mySerial.readString();
    Serial.println(a);
    Serial.println(a.length());
  }
  while(a.indexOf("OK") == -1 && tries <= MAXTRIES){
    tries++;
    Serial.println("Erro ao conectar com servidor MQTT");
    mySerial.println(msg); // Conecta ao Servidor MQTT
    delay(3000);
    Serial.println("Lendo retorno do comando.");
    //Receiving MODEM Response
    while(mySerial.available()>0)
    {
      delay(10);
      a = mySerial.readString();
      Serial.println(a);
    Serial.println(a.length());
    }
  }
  if(tries == MAXTRIES){
    Serial.println("Erro fatal. Resetar modem");
    return 1;
  }

  tries=0;
  mySerial.println("AT+CMQTTTOPIC=0," + String(topico.length())); // Tamanho do nome do topico
  Serial.println("AT+CMQTTTOPIC=0," + String(topico.length()));
  delay(3000);
  Serial.println("Lendo retorno do comando.");
  //Receiving MODEM Response
  while(mySerial.available()>0)
  {
    delay(10);
    a = mySerial.readString();
    Serial.println(a);
    Serial.println(a.length());
  }
  while(a.indexOf("OK") == -1 && tries <= MAXTRIES){
    tries++;
    Serial.println("Erro ao definir tamanho do topico!");
    mySerial.println("AT+CMQTTTOPIC=0," + String(topico.length())); // Tamanho do nome do topico
    delay(3000);
    Serial.println("Lendo retorno do comando.");
    //Receiving MODEM Response
    while(mySerial.available()>0)
    {
      delay(10);
      a = mySerial.readString();
      Serial.println(a);
    Serial.println(a.length());
    }
  }
  if(tries == MAXTRIES){
    Serial.println("Erro fatal. Resetar modem");
    return 1;
  }

  tries=0;
  mySerial.println(topico); // Topico
  Serial.println(topico);
  delay(3000);
  Serial.println("Lendo retorno do comando.");
  //Receiving MODEM Response
  while(mySerial.available()>0)
  {
    delay(10);
    a = mySerial.readString();
    Serial.println(a);
    Serial.println(a.length());
  }
  while(a.indexOf("OK") == -1 && tries <= MAXTRIES){
    tries++;
    Serial.println("Erro ao setar topico!");
    mySerial.println(topico); // Topico
    delay(3000);
    Serial.println("Lendo retorno do comando.");
    //Receiving MODEM Response
    while(mySerial.available()>0)
    {
      delay(10);
      a = mySerial.readString();
      Serial.println(a);
    Serial.println(a.length());
    }
  }
  if(tries == MAXTRIES){
    Serial.println("Erro fatal. Resetar modem");
    return 1;
  }

  tries=0;
  aux2 = "AT+CMQTTPAYLOAD=0," + String(payload.length());
  mySerial.println(aux2); // Define tamanho da payload
  Serial.println(aux2);
  delay(3000);
  Serial.println("Lendo retorno do comando.");
  //Receiving MODEM Response
  while(mySerial.available()>0)
  {
    delay(10);
    a = mySerial.readString();
    Serial.println(a);
    Serial.println(a.length());
  }
  while(a.indexOf("OK") == -1 && tries <= MAXTRIES){
    tries++;
    Serial.println("Erro ao setar tamanho da payload");
    mySerial.println(aux2); // Define tamanho da payload
    delay(3000);
    Serial.println("Lendo retorno do comando.");
    //Receiving MODEM Response
    while(mySerial.available()>0)
    {
      delay(10);
      a = mySerial.readString();
      Serial.println(a);
    Serial.println(a.length());
    }
  }
  if(tries == MAXTRIES){
    Serial.println("Erro fatal. Resetar modem");
    return 1;
  }

  tries=0;

  mySerial.println(payload); // Payload
  Serial.println(payload);
  delay(3000);
  Serial.println("Lendo retorno do comando.");
  //Receiving MODEM Response
  while(mySerial.available()>0)
  {
    delay(10);
    a = mySerial.readString();
    Serial.println(a);
    Serial.println(a.length());
  }
  while(a.indexOf("OK") == -1 && tries <= MAXTRIES){
    tries++;
    Serial.println("Erro ao setar payload");
    mySerial.println(payload); // Payload
    delay(3000);
    Serial.println("Lendo retorno do comando.");
    //Receiving MODEM Response
    while(mySerial.available()>0)
    {
      delay(10);
      a = mySerial.readString();
      Serial.println(a);
    Serial.println(a.length());
    }
  }
  if(tries == MAXTRIES){
    Serial.println("Erro fatal. Resetar modem");
    return 1;
  }

  tries=0;

  mySerial.println("AT+CMQTTPUB=0,1,60"); // Publica a payload
  delay(3000);
  Serial.println("Lendo retorno do comando.");
  //Receiving MODEM Response
  while(mySerial.available()>0)
  {
    delay(10);
    a = mySerial.readString();
    Serial.println(a);
    Serial.println(a.length());
  }
  while(a.indexOf("OK") == -1 && tries <= MAXTRIES){
    tries++;
    Serial.println("Erro ao publicar payload!");
    mySerial.println("AT+CMQTTPUB=0,1,60"); // Publica a payload
    delay(3000);
    Serial.println("Lendo retorno do comando.");
    //Receiving MODEM Response
    while(mySerial.available()>0)
    {
      delay(10);
      a = mySerial.readString();
      Serial.println(a);
    Serial.println(a.length());
    }
  }
  if(tries == MAXTRIES){
    Serial.println("Erro fatal. Resetar modem");
    return 1;
  }

  tries=0;
  mySerial.println("AT+CMQTTDISC=0,60"); // Disconecta o cliente
  delay(3000);
  Serial.println("Lendo retorno do comando.");
  //Receiving MODEM Response
  while(mySerial.available()>0)
  {
    delay(10);
    a = mySerial.readString();
    Serial.println(a);
    Serial.println(a.length());
  }
  while(a.indexOf("OK") == -1 && tries <= MAXTRIES){
    tries++;
    Serial.println("Erro ao disconectar cliente MQTT!");
    mySerial.println("AT+CMQTTDISC=0,60"); // Disconecta o cliente
    delay(3000);
    Serial.println("Lendo retorno do comando.");
    //Receiving MODEM Response
    while(mySerial.available()>0)
    {
      delay(10);
      a = mySerial.readString();
      Serial.println(a);
    Serial.println(a.length());
    }
  }
  if(tries == MAXTRIES){
    Serial.println("Erro fatal. Resetar modem");
    return 1;
  }

  tries=0;

  mySerial.println("AT+CMQTTREL=0"); // Release o servidor
  delay(3000);
  Serial.println("Lendo retorno do comando.");
  //Receiving MODEM Response
  while(mySerial.available()>0)
  {
    delay(10);
    a = mySerial.readString();
    Serial.println(a);
    Serial.println(a.length());
  }
  while(a.indexOf("OK") == -1 && tries <= MAXTRIES){
    tries++;
    Serial.println("Erro ao release!");
    mySerial.println("AT+CMQTTREL=0"); // Release o servidor
    delay(3000);
    Serial.println("Lendo retorno do comando.");
    //Receiving MODEM Response
    while(mySerial.available()>0)
    {
      delay(10);
      a = mySerial.readString();
      Serial.println(a);
    Serial.println(a.length());
    }
  }
  if(tries == MAXTRIES){
    Serial.println("Erro fatal. Resetar modem");
    return 1;
  }

  tries=0;
  mySerial.println("AT+CMQTTSTOP"); // Encerra conexão MQTT
  delay(3000);
  Serial.println("Lendo retorno do comando.");
  //Receiving MODEM Response
  while(mySerial.available()>0)
  {
    delay(10);
    a = mySerial.readString();
    Serial.println(a);
    Serial.println(a.length());
  }
  while(a.indexOf("OK") == -1 && tries <= MAXTRIES){
    tries++;
    Serial.println("Erro ao encerrar MQTT!");
    mySerial.println("AT+CMQTTSTOP"); // Encerra conexão MQTT
    delay(3000);
    Serial.println("Lendo retorno do comando.");
    //Receiving MODEM Response
    while(mySerial.available()>0)
    {
      delay(10);
      a = mySerial.readString();
      Serial.println(a);
    Serial.println(a.length());
    }
  }
  if(tries == MAXTRIES){
    Serial.println("Erro fatal. Resetar modem");
    return 1;
  }

  Serial.println("Encerrou MQTT");
  return 0;
}