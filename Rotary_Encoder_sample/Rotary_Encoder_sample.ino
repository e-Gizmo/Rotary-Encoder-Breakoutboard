/*
  e-Gizmo Rotary Encoder Breakoutboard
 
 This sample code gives you an incremental or
 decrements numerical value using Rotary Encoder
 Breakoutboard and it has center button that acts
 as confirmation button.
 
 Modified code by
 e-Gizmo Mechatronix Central
 February 13, 2017
 
 Reference:
 http://bildr.org/2012/08/rotary-encoder-arduino/
 
 
 */
//these pins can not be changed 2/3 are special pins
int ENCODER_A = 2;
int ENCODER_B = 3;
int ENCODER_BUTTON = 4; //push button switch

volatile int LASTENCODED =  0;
volatile long ENCODERVALUE = 0;

long LASTENCODERVALUE = 0;

int LASTMSB = 0;
int LASTLSB = 0;

void setup() {
  Serial.begin (9600);

  pinMode(ENCODER_A, INPUT); 
  pinMode(ENCODER_B, INPUT);

  pinMode(ENCODER_BUTTON, INPUT);


  digitalWrite(ENCODER_A, HIGH); //turn pullup resistor on
  digitalWrite(ENCODER_B, HIGH); //turn pullup resistor on

  digitalWrite(ENCODER_BUTTON, HIGH); //turn pullup resistor on


  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, UPDATEENCODER, CHANGE); 
  attachInterrupt(1, UPDATEENCODER, CHANGE);

}

void loop(){ 
  //Do stuff here
  if(digitalRead(ENCODER_BUTTON)){
    //button is not being pushed
    digitalWrite(13, LOW);
  }
  else{
    //button is being pushed
    digitalWrite(13,HIGH);
  }

  Serial.println(ENCODERVALUE);
  delay(1000); //just here to slow down the output, and show it will work  even during a delay
}


void UPDATEENCODER(){
  int MSB = digitalRead(ENCODER_A); //MSB = most significant bit
  int LSB = digitalRead(ENCODER_B); //LSB = least significant bit

  int ENCODED = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int SUM  = (LASTENCODED << 2) | ENCODED; //adding it to the previous encoded value

  if(SUM == 0b1101 || SUM == 0b0100 || SUM == 0b0010 || SUM == 0b1011) ENCODERVALUE ++;
  if(SUM == 0b1110 || SUM == 0b0111 || SUM == 0b0001 || SUM == 0b1000) ENCODERVALUE --;

  LASTENCODED = ENCODED; //store this value for next time
}

