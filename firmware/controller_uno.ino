#include <SoftwareSerial.h>
#include <ezButton.h>

// left joystick (vertical)
#define VRX_PINV  A0 // Arduino pin connected to VRX pin
#define VRY_PINV  A1 // Arduino pin connected to VRY pin
#define SW_PINV   2  // Arduino pin connected to SW  pin
ezButton buttonV(SW_PINV);

//right joystick (horizontal)
#define VRX_PINH  A2 // Arduino pin connected to VRX pin
#define VRY_PINH  A3 // Arduino pin connected to VRY pin
#define SW_PINH   7  // Arduino pin connected to SW  pin
ezButton buttonH(SW_PINH);

#define LEFT_THRESHOLD  400
#define RIGHT_THRESHOLD 800
#define UP_THRESHOLD    400
#define DOWN_THRESHOLD  800

#define COMMAND_NO     0x00
#define COMMAND_LEFT   0x01
#define COMMAND_RIGHT  0x02
#define COMMAND_UP     0x04
#define COMMAND_DOWN   0x08

int yValueV = 0 ; // To store value of the Y axis
int xValueH = 0 ; // To store value of the X axis
int command = COMMAND_NO;

int upPin = 11; // up button pin
int downPin = 10; // down button pin
int motorSpeed = 0; // stages of motor speed

SoftwareSerial mySerial(8,9); // HC-05 RX and TX pins

void setup() {
mySerial.begin(9600); // begins bluetooth communication
Serial.begin(9600); // begins serial monitor
buttonV.setDebounceTime(50); // set debounce time to 50 milliseconds
buttonH.setDebounceTime(50); // set debounce time to 50 milliseconds

pinMode(downPin, INPUT); // initializes the down button
pinMode(upPin, INPUT); // initializes the up button
}

void loop() {
 buttonV.loop(); // MUST call the loop() function first
 buttonH.loop(); // MUST call the loop() function first

 // decreases and increases the motor speed stage when the corresponding button is pressed (max of 2 and -2)
 if ((digitalRead(upPin) == HIGH) && (motorSpeed < 2)) {
   motorSpeed += 1;
 }
 if ((digitalRead(downPin) == HIGH) && (motorSpeed > -2)) {
   motorSpeed -= 1;
 }

 delay(250); // delay for the button

 // sends the car what stage of speed it's at
 if (motorSpeed == -2) {
   mySerial.write('2');
 } else if (motorSpeed == -1) {
   mySerial.write('3');
 } else if (motorSpeed == 0) {
   mySerial.write('4');
 } else if (motorSpeed == 1) {
   mySerial.write('5');
 } else if (motorSpeed == 2) {
   mySerial.write('6');
 }

 // read analog X and Y analog values
 yValueV = analogRead(VRY_PINV);
 xValueH = analogRead(VRX_PINH);

 // sends a signal to the car if the joystick button is pressed or released
 if (buttonV.isPressed() || buttonH.isPressed()) {
   mySerial.write('1');
 }
 if (buttonV.isReleased() || buttonH.isReleased()) {
   mySerial.write('0');
 }

 // converts the analog value to commands
 // reset commands
 command = COMMAND_NO;

 // check left/right commands
 if (xValueH < LEFT_THRESHOLD)
   command = command | COMMAND_LEFT;
 else if (xValueH > RIGHT_THRESHOLD)
   command = command | COMMAND_RIGHT;

 // check up/down commands
 if (yValueV < UP_THRESHOLD)
   command = command | COMMAND_UP;
 else if (yValueV > DOWN_THRESHOLD)
   command = command | COMMAND_DOWN;

 // sends a signal to the car where the joysticks want it to go
 if (command & COMMAND_LEFT) {
   mySerial.write('l');
 ] else if (command & COMMAND_RIGHT) {
   mySerial.write('r');
 }
 if (command & COMMAND_UP) {
   mySerial.write('u');
 } else if (command & COMMAND_DOWN) {
   mySerial.write('d');
 }
}