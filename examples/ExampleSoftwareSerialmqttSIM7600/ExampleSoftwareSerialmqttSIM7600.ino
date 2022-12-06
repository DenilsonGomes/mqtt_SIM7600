#include <mqtt_SIM7600.h>

mqtt_SIM7600 teste(13);
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  teste.iniciaMQTT();
  teste.publica();
  teste.encerraMQTT();
  delay(60000);
}
