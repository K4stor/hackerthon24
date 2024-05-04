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
    unsigned speed = 0b00001111 & value;
    unsigned direction = (0b11110000 & value) >> 4;

    Serial.println("Value: ");
    Serial.println(value);

    Serial.println("Direction: ");
    Serial.println(direction);
    Serial.println("Speed: ");
    Serial.println(speed);

    unsigned char mappedDirection = mapDirection(direction); 
    unsigned char mappedSpeed = mapSpeed(speed);

    Serial.println("Mapped direction: ");
    Serial.println(mappedDirection);
    Serial.println("Mapped speed: ");
    Serial.println(mappedSpeed);
    
    speedServo.write(mappedSpeed);
    directionServo.write(mappedDirection);
    delay(15); 
  }
}

unsigned char mapSpeed(unsigned char speed) {
  unsigned char standStillSpeed = 90;
  unsigned char maxForwardSpeed = 160;
  unsigned char maxBackwardSpeed = 20;

  if (speed == 4) {
    return standStillSpeed;
  } else if (speed > 4) {
    return map(speed, 5, 15, standStillSpeed, maxForwardSpeed);
  } else if (speed < 4) {
    return map(speed, 0, 3, standStillSpeed, maxBackwardSpeed);
  }
}

unsigned char mapDirection(unsigned char direction) {
  unsigned char straightForwardDirection = 85;
  unsigned char maxLeftDirection = 135;
  unsigned char maxRightDirection = 35;

  if (direction == 7 || direction == 8) {
    return straightForwardDirection;
  } else if (direction > 8) {
    return map(direction, 9, 15, straightForwardDirection, maxRightDirection);
  } else if (direction < 7) {
    return map(direction, 0, 6, straightForwardDirection, maxLeftDirection);
  }
}
