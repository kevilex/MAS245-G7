#include <FlexCAN.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ADXL335.h>

CAN_message_t TX, RX; //lager CAN format meldinger


int count = 0; // teller variabel meldinger

//verdier for å formatere can-meldingen
String convert;
bool sendval;
String conv1, conv2, conv3;
int split1, split2, split3;


//definerer pins og variabel for LED skjerm
#define OLED_DC     6
#define OLED_CS     10
#define OLED_RESET  5
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

//definerer pins og varabler for gyro
#define X_AXIS_PIN A9
#define Y_AXIS_PIN A8
#define Z_AXIS_PIN A7
ADXL335 acc;
float ax, ay, az;



void setup() {
  Serial.begin(9600); //starter serial
  acc.begin(); //starter akselerometeret
  
  //starter displayet og klarerer det.
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  //justerer tekst til minste størrelse og til fargen hvit
  display.setTextSize(0);
  display.setTextColor(WHITE);
  //lager den hvite rammen
  display.drawRect(0,0,128,32,WHITE);
  //setter inn den "permanente teksten"
  display.setCursor(2,2);
  display.print("MAS247-gruppe7");
  
  display.setCursor(2,12);
  display.print("Received: ");
  
  display.setCursor(2,22);
  display.print("LID: ");
  
  display.setCursor(50, 22);
  display.print("AZ:");
  
  display.setCursor(95,22);
  display.print("m/s^2");

  display.display();


  Can0.begin(250000); //Blir med på CANbussen
  Can1.begin(250000); //på begge kanaler, har fått feil ved å bare starte en.
  delay(1000);
}


void loop() {
  
  //leser om det er en ledig melding.
  if (Can1.available()){
      Can1.read(RX); //leser meldingen og skriver til RX
      
      display.fillRect(30,20,20,10, BLACK); //svart firkant tegnes over ID området
      display.setCursor(30,22); //velger hvor den skal starte å skrive ved neste print
      display.print(RX.id);
      count = count+1;
      display.setCursor(60,12); //velger hvor den skal starte å skrive neste print
      display.fillRect(58,10,30,10, BLACK); //svart firkant tegnes over teller området
      display.print(count);

      //sjekker om id'en er 0x21 eller ikke
      if (RX.id == 33){
        sendval = true;
      }else{
        sendval = false;
      }
      
  }

  delay(1000);
  
  //henter ut akselerasjonsverdiene
  acc.getAcceleration(&ax, &ay, &az);

  //om den tidligere id verdien var 0x21
  if (sendval == true){
  convert = String(az); //konverterer ifra float til 
  //tar ut verdiene jeg har lyst til å sende, her limiterer vi oss selv med tanke på desimaler og lengde.
  conv1 = convert[0];
  conv2 = convert[2];
  conv3 = convert[3];
  
  //gjør de oppdelte verdiene av stringen om til integer verdier
  split1 = conv1.toInt();
  split2 = conv2.toInt();
  split3 = conv3.toInt();
  
  //setter verdiene til can bufferen
  TX.buf[0] = split1;
  TX.buf[1] = split2;
  TX.buf[2] = split3;
  
  TX.len = 3; //setter lengden på can-meldingen 
  TX.id = 0x22; //setter id'en som den skal svare med
  Can1.write(TX); //sender meldingen
  }
  
  display.setCursor(70,22); //velger hvor den skal skrive akselerasjonen
  display.fillRect(70,22,25,7, BLACK); //svart boks på det skrevne området
  display.print(az); //skriver verdien
  display.display();  //oppdaterer displayet
}
