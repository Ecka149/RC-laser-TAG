/*------------------------------------------
Thanks for contributing to this project, if you have any suggestions, or bug fixes, pm me at github.
This is just a prototype, with IR module. Needs RGB led for an indication of what is happening, and of course a button, for enablng calibration.
Calibrations is done by five steps, which sets the five coresponding codes, which should be the shot code.

/----------------------------------------*/
#include <IRremote.h>

int CAL=2; //CALIBRATION indicator RED  
int RDY=3; //Ready indicator GREEN
int SHT=4; //Shot/Calibrating Indicator Blue
int RECV_PIN = 12; //IR Receiver pin
int BTN=5; // Button pin
unsigned int CALP[]={0,0,0,0,0}; // Calibration points
int buttonState;
int CALIBRATE=0; //Calibration not done setting
IRrecv irrecv(RECV_PIN);
decode_results results;




void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(OUTPUT, CAL);
  pinMode(OUTPUT, RDY);
  pinMode(INPUT, BTN); 
  pinMode(OUTPUT, SHT);
}

void loop()
{
  buttonState = digitalRead(BTN);
  if (buttonState == HIGH) {
  if (irrecv.decode(&results)){
  Serial.println("CALIBRATION INITALIZED");
  digitalWrite(CAL, HIGH);
  delay(5000);
  Calibration(1);
  delay(5000);
  Calibration(2);
  delay(5000);
  Calibration(3);
  delay(5000);
  Calibration(4);
  delay(5000);
  Calibration(5);
  digitalWrite(CAL, LOW);
    }
  irrecv.resume(); // Receive the next value
  CALIBRATE=1;
  }
  while(CALIBRATE==1){
  digitalWrite(RDY, HIGH);
  if(irrecv.decode(&results)==CALP[1]){
    Serial.println("SHOT1");
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  if(irrecv.decode(&results)==CALP[2]){
    Serial.println("SHOT2");
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  if(irrecv.decode(&results)==CALP[3]){
    Serial.println("SHOT3");
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  if(irrecv.decode(&results)==CALP[4]){
    Serial.println("SHOT4");
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  //if(irrecv.decode(&results)==CALP[5]){
    //Serial.println("Pašove5");
   // Serial.println(results.value, HEX);
    //irrecv.resume(); // Receive the next value
 // }
  buttonState = digitalRead(BTN);
  if (buttonState == HIGH) {
    CALIBRATE=0;
    }
  }
}

  /*
  switch (CALP[]){
    case CALP[1]:
      Serial.println("PAMUŠO1");
      break;
    case CALP[2]:
      Serial.println("PAMUŠO2");
      break;
    case CALP[3]:
      Serial.println("PAMUŠO3");
      break;
    case CALP[4]:
      Serial.println("PAMUŠO4");
      break;
    case CALP[5]:
      Serial.println("PAMUŠO5");
      break;
  }
  */



  void Calibration(int nr){
    if (irrecv.decode(&results))
    {
     digitalWrite(CAL, HIGH);
     Serial.println(nr);
     delay(1000);
     irrecv.resume();
     irrecv.decode(&results);
     CALP[nr]=results.value;
     Serial.println(results.value);
     digitalWrite(SHT, HIGH);
     delay(500);
     Serial.println(CALP[nr]);
     digitalWrite(SHT, LOW);
     delay(500);
     irrecv.resume(); // Receive the next value
    }
    else Calibration(nr);
  }
