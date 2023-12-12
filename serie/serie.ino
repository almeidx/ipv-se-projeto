#include <Adafruit_MotorShield.h>

const int DEFAULT_SPEED = 70;

const int sensorEcho = 4;
const int sensorTrig = 5;

const int D_FORWARD = 0;
const int D_BACKWARD = 1;
const int D_LEFT = 2;
const int D_RIGHT = 3;
const int D_STOP = 4;

const int D_MANUAL = 0;
const int D_AUTOMATIC = 1;

int speed = DEFAULT_SPEED, oldSpeed = 0;
int leftMotorDir = BACKWARD;
int rightMotorDir = FORWARD;
long duration, cm;
unsigned long currentTime, lastTimeRead = 0;

bool emManobra = false;
bool frontSensorStop = false;

Adafruit_MotorShield shield = Adafruit_MotorShield();
Adafruit_DCMotor *rightMotor = shield.getMotor(1);
Adafruit_DCMotor *leftMotor = shield.getMotor(2);

int driveDirection = D_STOP;
int driveMode = D_MANUAL;

void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
	pinMode(sensorEcho, INPUT);
	pinMode(sensorTrig, OUTPUT);

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
  readUltrassons();

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

  if (emManobra) {
    currentTime = millis();

    if (lastTimeRead != 0 && currentTime - lastTimeRead > 2000) {
      emManobra = false;
      driveDirection = D_FORWARD;
      lastTimeRead = 0;
      speed = oldSpeed;
      return;
    }

    if (oldSpeed == 0) {
      oldSpeed = speed;
    }

    speed = 60;
    driveDirection = D_LEFT;

    if (lastTimeRead == 0) {
      lastTimeRead = currentTime;
    }

    return;
  }

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
  if (frontSensorStop) {
    return;
  }

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
    driveDirection = D_STOP;
    speed = DEFAULT_SPEED;
  } else if (command.indexOf("automatic") >= 0) {
    driveMode = D_AUTOMATIC;
    driveDirection = D_FORWARD;
    speed = DEFAULT_SPEED;
  }
}

long microsecondsToCm(long microseconds) {
	return microseconds / 29 / 2;
}

void readUltrassons() {
  if (emManobra) {
    return;
  }

  digitalWrite(sensorTrig, LOW);
	delayMicroseconds(2);

	digitalWrite(sensorTrig, HIGH);
	delayMicroseconds(10);

	digitalWrite(sensorTrig, LOW);

	duration = pulseIn(sensorEcho, HIGH);
	cm = microsecondsToCm(duration);

  if (cm <= 40) {
    if (!frontSensorStop) {
      frontSensorStop = true;
      driveDirection = D_STOP;
      emManobra = driveMode == D_AUTOMATIC;
    }
  } else {
    frontSensorStop = false;
    emManobra = false;
  }
}




