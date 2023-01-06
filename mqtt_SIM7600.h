#ifndef mqtt_SIM7600_H
#define mqtt_SIM7600_H
 
#include "Arduino.h"
#include "SoftwareSerial.h" // Biblioteca SoftwareSerial
 
class mqtt_SIM7600
{
   public:
      mqtt_SIM7600(int num); 
      //void iniciaMQTT(String host, String token);
      //void inscreve(String topico);
      int publica(String host, String token, String topico, String payload);
      //void encerraMQTT();
      //void retornoAT();
      void rssi();
   
   private:
   
}; 
#endif