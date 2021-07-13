#include <IRremote.h>

//ir
int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;
//motor
const int pin1=4;
const int pin2=2;
//ultra sonar
const int pingPin = 12;
const int ledPin = 11;

int sensorState = 0;
long unsigned int choice = 0;

void setup()
{
  irrecv.enableIRIn();
  Serial.begin(9600);
  pinMode(pin1, OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() 
{
 if (irrecv.decode(&results)) {
    Serial.println(results.value,DEC);
  	choice=results.value;
    // Receive thxt value
  irrecv.resume();
  }
  delay(10);
 if(choice==16584943) Offmotor();
 if(choice==16601263) Onmotor();
    ultraSonar();
}


void Onmotor(){
	analogWrite(pin1, 255);analogWrite(pin2, 255);
}
void Offmotor(){
	analogWrite(pin1, 0);analogWrite(pin2, 0);
}
void ultraSonar(){
  long duration, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.println(cm);
  if(cm < 100) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
}
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
