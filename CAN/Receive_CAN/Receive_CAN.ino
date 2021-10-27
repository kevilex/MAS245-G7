#include <FlexCAN.h>
FlexCAN myCAN(5000); //transieveren støtter 1mbps - https://www.microchip.com/en-us/product/MCP2562
CAN_message_t testout, testin; //lager CAN format meldinger
int RXcount = 0; // teller for mengden meldinger jeg har fått
uint32_t ids;

void setup() {
  Serial.begin(9600); //starter serial
  myCAN.begin(); //Blir med på CANbussen
}

void loop() {
    delay(1000);
    myCAN.read(testin);
    ids = testin.id;
    Serial.println(ids);
    Serial.print("message number ");
    Serial.println(RXcount); //printer den ut hvor mange meldinger den har fått
    RXcount++;
  

}
