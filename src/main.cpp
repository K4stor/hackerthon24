#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>

Servo speedServo;
Servo directionServo;

SoftwareSerial BTSerial (2,3);

int speedPin = 9;
int directionPin = 10;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

  speedServo.attach(speedPin);
  directionServo.attach(directionPin);
}

void loop() {

  if(BTSerial.available()) {

    char value = BTSerial.read();

    char speed = 0b00001111 & value;
    char direction = (0b11110000 & value) >> 4;

    unsigned char mappedDirection = map(direction, 0, 127, 135, 35); 
    unsigned char mappedSpeed = map(speed, 0, 127, 20, 160); 
    
    speedServo.write(mappedSpeed);
    directionServo.write(mappedDirection);
    delay(15); 
  }
}