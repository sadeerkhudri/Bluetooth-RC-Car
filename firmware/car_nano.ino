#include <SoftwareSerial.h>

SoftwareSerial mySerial(8,7); // HC-05 RX and TX pins
char data; // initializes variable for data incoming from the controller

//defines all motor pins
#define forwardR 5
#define backwardR 6
#define backwardL 10
#define forwardL 9

int motorSpeed; // initializes motorSpeed variable

int buzzerPin = 3 ; // buzzer pin

void setup() {
 mySerial.begin(9600); // starts communication with the HC-05 (bluetooth module)
 Serial.begin(9600); // begins serial monitor

 // initalizes all the pins for the motors and buzzer
 pinMode(forwardR, OUTPUT);
 pinMode(backwardR, OUTPUT);
 pinMode(backwardL, OUTPUT);
 pinMode(forwardL, OUTPUT);
 pinMode(buzzerPin, OUTPUT);
 digitalWrite(forwardR, LOW);
 digitalWrite(backwardR, LOW);
 digitalWrite(backwardL, LOW);
 digitalWrite(forwardL, LOW);
}


void loop() {
 // checks if communication is available
 if(mySerial.available()>0) {
   data = mySerial.read(); // stores the data it receives from the controller in the variable
   Serial.println(data); 
 }

 // sets the motor speed corresponding to what the controller tells it
 if (data == '2') {
   motorSpeed = 75;
 } else if (data == '3') {
   motorSpeed = 120;
 } else if (data == '4') {
   motorSpeed = 165;
 } else if (data == '5') {
   motorSpeed = 210;
 } else if (data == '6') {
   motorSpeed = 255;
 }

 // moves the car using the motor controller depending on what the controller tells it
 if (data == 'u') {
   digitalWrite(forwardR, motorSpeed);
   digitalWrite(forwardL, motorSpeed);
 } else if (data == 'd'){
   digitalWrite(backwardR, motorSpeed);
   digitalWrite(backwardL, motorSpeed);
 } else if (data == 'r') {
   digitalWrite(forwardL, motorSpeed);
   digitalWrite(backwardR, motorSpeed);
 } else if (data == 'l') {
   digitalWrite(forwardR, motorSpeed);
   digitalWrite(backwardL, motorSpeed);
 }
 digitalWrite(forwardR, LOW);
 digitalWrite(backwardR, LOW);
 digitalWrite(backwardL, LOW);
 digitalWrite(forwardL, LOW);

 // plays the buzzer as a horn if the button on the joystick is pressed from the controller
 if (data == '1') {
   tone(buzzerPin, 1000);
 } else if (data == '0') { 
   noTone(buzzerPin);
 }

 data = 'Nothing'; // resets the data variable to nothing
}