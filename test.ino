#include <IRremote.h>

int CAL=2;
int RDY=3;
int SHT=4;
int RECV_PIN = 12;
int BTN=5;
unsigned int CALP[]={0,0,0,0,0};
int buttonState;
int CALIBRATE=0;
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
    Serial.println("Pašove1");
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  if(irrecv.decode(&results)==CALP[2]){
    Serial.println("Pašove2");
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  if(irrecv.decode(&results)==CALP[3]){
    Serial.println("Pašove3");
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  if(irrecv.decode(&results)==CALP[4]){
    Serial.println("Pašove4");
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
     Serial.println(nr);
     digitalWrite(CAL, HIGH);
     Serial.println(results.value, HEX);
     digitalWrite(SHT, HIGH);
     delay(500);
     CALP[nr]=results.value;
     digitalWrite(SHT, LOW);
     delay(500);
     irrecv.resume(); // Receive the next value
    }
    else Calibration(nr);
  }













    
