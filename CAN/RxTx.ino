#include <FlexCAN.h>


CAN_message_t testout, testin; //lager CAN format meldinger
int RXcount = 0; // teller for mengden meldinger jeg har fått

int aval;

void setup() {
  Serial.begin(9600); //starter serial
  Can0.begin(500000); //Blir med på CANbussen
  Can1.begin(500000);
  delay(1000);
}

void loop() {
   if (Can1.available()){
      Can1.read(testin);
      Serial.print("ID: ");
      Serial.println(testin.id);
      Serial.print("BUF: ");
      Serial.println(testin.buf[0]);
    }
  delay(100);
  testout.buf[1] = 0xff;
  testout.len = 1;
  testout.id = 5;
  Can1.write(testout);
  Serial.println("sendt mld");
  

    
    
  

}
