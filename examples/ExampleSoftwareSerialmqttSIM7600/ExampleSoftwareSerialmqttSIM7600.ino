#include <mqtt_SIM7600.h>

mqtt_SIM7600 teste(13);

String host = "tcp://demo.thingsboard.io:1883";
String token = "EKx0Da1Zjiue6N9XkVLf";
String topico = "v1/devices/me/telemetry";
String msg = "{\"A\":90}";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  teste.iniciaMQTT(host, token);
  delay(3000);
//  teste.retornoAT();
  
  //teste.inscreve(topico);
  //delay(3000);
//  teste.retornoAT();
  
  teste.publica(topico, msg);
  delay(3000);
//  teste.retornoAT();
  
  teste.encerraMQTT();
  delay(3000);
//  teste.retornoAT();
  
  delay(60000);
}
