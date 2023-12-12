#include <Adafruit_MotorShield.h>
// #include <Servo.h>

const int D_FORWARD = 0;
const int D_BACKWARD = 1;
const int D_LEFT = 2;
const int D_RIGHT = 3;
const int D_STOP = 4;

const int D_MANUAL = 0;
const int D_AUTOMATIC = 1;

int speed = 70;
int leftMotorDir = BACKWARD;
int rightMotorDir = FORWARD;

Adafruit_MotorShield shield = Adafruit_MotorShield();
Adafruit_DCMotor *rightMotor = shield.getMotor(1);
Adafruit_DCMotor *leftMotor = shield.getMotor(2);

int driveDirection = D_FORWARD;
int driveMode = D_MANUAL;

void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  if (!shield.begin(1000)) {
    digitalWrite(LED_BUILTIN, HIGH);
    while (1);
  }

  rightMotor->setSpeed(speed);
  rightMotor->run(rightMotorDir = RELEASE);

  leftMotor->setSpeed(speed);
  leftMotor->run(leftMotorDir = RELEASE);
}

void loop() {
  switch (driveDirection) {
    case D_FORWARD:
      driveForward();
      break;
    case D_BACKWARD:
      driveBackward();
      break;
    case D_LEFT:
      turnLeft();
      break;
    case D_RIGHT:
      turnRight();
      break;
    case D_STOP:
      stop();
      break;
  }

  String receivedData = "";

  while (Serial.available() > 0) {
    char incomingChar = Serial.read();
    receivedData += incomingChar;
  }

  if (receivedData.length() > 0) {
    processSerialCommand(receivedData);
    receivedData = "";
  }
}

void driveForward() {
  rightMotor->run(rightMotorDir = FORWARD);
  rightMotor->setSpeed(speed);

  leftMotor->run(leftMotorDir = BACKWARD);
  leftMotor->setSpeed(speed);
}

void driveBackward() {
  rightMotor->run(rightMotorDir = BACKWARD);
  rightMotor->setSpeed(speed);

  leftMotor->run(leftMotorDir = FORWARD);
  leftMotor->setSpeed(speed);
}

void turnLeft() {
  if (rightMotorDir == RELEASE) {
    rightMotor->run(rightMotorDir = FORWARD);
  }
  rightMotor->setSpeed(speed);

  if (leftMotorDir == RELEASE) {
    leftMotor->run(leftMotorDir = BACKWARD);
  }
  leftMotor->setSpeed((int)(speed / 2));
}

void turnRight() {
  if (rightMotorDir == RELEASE) {
    rightMotor->run(rightMotorDir = FORWARD);
  }
  rightMotor->setSpeed((int)(speed / 2));

  if (leftMotorDir == RELEASE) {
    leftMotor->run(leftMotorDir = BACKWARD);
  }
  leftMotor->setSpeed(speed);
}

void stop() {
  rightMotor->run(rightMotorDir = RELEASE);
  leftMotor->run(leftMotorDir = RELEASE);
}

void processSerialCommand(String command) {
  delay(100);

  if (command.indexOf("forward") >= 0) {
    driveDirection = D_FORWARD;
    driveMode = D_MANUAL;
  } else if (command.indexOf("backward") >= 0) {
    driveDirection = D_BACKWARD;
    driveMode = D_MANUAL;
  } else if (command.indexOf("left") >= 0) {
    driveDirection = D_LEFT;
    driveMode = D_MANUAL;
  } else if (command.indexOf("right") >= 0) {
    driveDirection = D_RIGHT;
    driveMode = D_MANUAL;
  } else if (command.indexOf("stop") >= 0) {
    driveDirection = D_STOP;
    driveMode = D_MANUAL;
  } else if (command.indexOf("increase") >= 0) {
    speed += 10;
    if (speed > 255) speed = 255; 
  } else if (command.indexOf("decrease") >= 0) {
    speed -= 10;
    if (speed < 0) speed = 0;
  } else if (command.indexOf("manual") >= 0) {
    driveMode = D_MANUAL;
  } else if (command.indexOf("automatic") >= 0) {
    driveMode = D_AUTOMATIC;
  }
}
