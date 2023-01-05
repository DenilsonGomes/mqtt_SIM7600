#include "Arduino.h"
#include "mqtt_SIM7600.h"

// Variáveis
int tensaoA; // Variavel para leitura analógica
String aux1; // String auxiliar1
String aux2; // String auxiliar2
String a;
int flag = 1;
int flag1 = 0;

// Objeto 
SoftwareSerial mySerial(3, 2); // Objeto mySerial nos pinos 2 e 3

mqtt_SIM7600::mqtt_SIM7600(int num)
{
  Serial.begin(9600); // Inicia a serial
  mySerial.begin(9600); // Inicia a mySerial
}

void mqtt_SIM7600::retornoAT(){
  Serial.println("Lendo retorno do comando.");
  //Receiving MODEM Response
  while(mySerial.available()>0)
  {
    delay(10);
    a = mySerial.readString();
    Serial.println(a);
    if(flag==0)
    {
      //Serial.println(a);
    flag = 1;
    }
    //Serial.println(b);
    if(a.indexOf("PAYLOAD") != -1)
    {
      Serial.println(a);
      flag = 0;
      int new1 = a.indexOf("PAYLOAD");
      String neww = a.substring(new1);
      int new2 = neww.indexOf('\n');
      String new3 = neww.substring(new2+1);
      int new4 = new3.indexOf('\n');
      String new5 = new3.substring(0,new4);
       
      //Serial.println("Topic: led/subscribe");
      Serial.print("Message is: ");
      Serial.println(new5);
      new5.remove(new5.length()-1);
      Serial.println(new5);
    }     
  }
} 

void mqtt_SIM7600::iniciaMQTT(String host, String token)
{
  mySerial.println("ATE0"); // Inicia o modem
  delay(2000);
  mySerial.println("AT+CMQTTSTART"); // Inicia conexão MQTT
  delay(2000); 
  mySerial.println("AT+CMQTTACCQ=0,\"Client d\""); // Client ID
  delay(2000);
  String msg;
  msg = "AT+CMQTTCONNECT=0,\"" + host + "\",90,1,\"" + token + "\"";
  Serial.println(msg);
  mySerial.println(msg); // Conecta ao Servidor MQTT
  //"AT+CMQTTCONNECT=0,\"tcp://demo.thingsboard.io:1883\",90,1,\"uz8xZMgFQkltIc7VpL4A\""
  delay(3000);
}
 
void mqtt_SIM7600::inscreve(String topico)
{
  mySerial.println("AT+CMQTTSUBTOPIC=0,9,1"); //AT Command for Setting up the Subscribe Topic Name 
  delay(2000);
  mySerial.println(topico); //Topic Name
  delay(2000);
  mySerial.println("AT+CMQTTSUB=0,4,1,1"); //Length of message
  delay(2000);
  mySerial.println("HAII"); //message
  delay(2000);
}
 
void mqtt_SIM7600::publica(String topico, String payload)
{
  mySerial.println("AT+CMQTTTOPIC=0," + String(topico.length())); // Tamanho do nome do topico
  Serial.println("AT+CMQTTTOPIC=0," + String(topico.length()));
  delay(2000);
  
  mySerial.println(topico); // Topico
  Serial.println(topico);
  delay(2000);
  
  aux2 = "AT+CMQTTPAYLOAD=0," + String(payload.length());
  mySerial.println(aux2); // Define tamanho da payload
  delay(2000);
  mySerial.println(payload); // Payload
  delay(2000);
  mySerial.println("AT+CMQTTPUB=0,1,60"); // Publica a payload
  delay(3000);
  Serial.println(aux2);
  Serial.println(payload);
}

void mqtt_SIM7600::encerraMQTT()
{
  mySerial.println("AT+CMQTTDISC=0,60"); // Disconecta o cliente
  delay(2000);
  mySerial.println("AT+CMQTTREL=0"); // Release o servidor
  delay(2000);
  mySerial.println("AT+CMQTTSTOP"); // Encerra conexão MQTT
  delay(3000);
  Serial.println("Encerrou MQTT");
}
