#include <Servo.h>
#include <IRremote.h>

Servo Servo1;
IRrecv IR(3);

int servoPin = 9;
int potPin= A0;
bool turn = true;

void setup() {
  Servo1.attach(servoPin);
  IR.enableIRIn();
  Serial.begin(9600);
  Servo1.write(0);
}

void loop() {
  if(IR.decode()){
    if (IR.decodedIRData.decodedRawData != 0){
      Serial.println(IR.decodedIRData.decodedRawData, HEX);
    }
    
    if(IR.decodedIRData.decodedRawData == 0xBF40FF00){
      lockPin();
    }
    
    delay(100);
    IR.resume();
  }
}

void lockPin(){
  if (turn == true){
    forward();
    turn = !turn;
  }else if (turn == false) {
    backward();
    turn = !turn;
  }
}

void forward(){
  for (int pos = 0; pos <= 160; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    Servo1.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.println(String(pos));
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void backward(){
  for (int pos = 160; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    Servo1.write(pos);              // tell servo to go to position in variable 'pos'
    Serial.println(String(pos));
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
