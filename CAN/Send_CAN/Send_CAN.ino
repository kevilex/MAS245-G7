#include <FlexCAN.h>
#include <kinetis_flexcan.h>

const int baudRate = 5000; //Setter baudraten, men i pcan må nominal-bit rate være 250kbit/s

FlexCAN myCAN(baudRate); //setter baudrate

CAN_message_t message; //lager can-melding i riktig format


void setup() {
  Serial.begin(9600); //åpner serial forbindelse, ctrl + shift + m for å sjekke hva som blir skrevet
  myCAN.begin(); // hiver seg på can-bussen
  

}
void loop() {
     delay(1000);
     message.buf[6] = 0xff; //hva som skal være i meldingen
     message.len = 7; // lengden på meldingen, max 8 hexadesimaler
     message.id = 80085; // CAN-ID
     myCAN.write(message); //sender meldingen ut på canbus
     Serial.println("message Sent"); //skriver i serial at den har sendt en melding.

     
}
