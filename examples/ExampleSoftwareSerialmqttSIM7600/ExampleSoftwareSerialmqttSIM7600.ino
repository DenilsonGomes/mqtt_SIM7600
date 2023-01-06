#include <mqtt_SIM7600.h>

mqtt_SIM7600 teste(13);

String host = "tcp://demo.thingsboard.io:1883";
String token = "EKx0Da1Zjiue6N9XkVLf";
String topico = "v1/devices/me/telemetry";
String msg = "{\"A\":90}";
#define MAXTRIES 10
int tries;
int ret;

void setup() {
  Serial.begin(9600);
  delay(30000);
}

void loop() {
  teste.rssi();
  //delay(3000);

//  tries=0;
//  ret = teste.publica(host, token, topico, msg);
//  while(ret && tries <= MAXTRIES){
//    Serial.println(ret);
//    tries++;
//  }
//  if(tries >= MAXTRIES){
//    Serial.println("Não conseguiu publicar.");
//  }else{
//    Serial.println("Publicado com sucesso!");
//  }
  
  delay(300000);
}
