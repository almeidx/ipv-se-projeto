#include <Adafruit_MotorShield.h>

Adafruit_MotorShield Shield = Adafruit_MotorShield();

Adafruit_DCMotor *leftMotor = Shield.getMotor(3);
Adafruit_DCMotor *rightMotor = Shield.getMotor(4);

void setup()
{
  Serial.begin(9600);
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!Shield.begin(1000))
  {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1)
      ;
  }

  Serial.println("Motor Shield found.");

  leftMotor->setSpeed(150);
  leftMotor->run(FORWARD);

  rightMotor->setSpeed(150);
  rightMotor->run(FORWARD);

  // turn on motors
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);
}

void loop()
{
  Serial.print("tick");

  leftMotor->run(BACKWARD);
  rightMotor->run(FORWARD);

  leftMotor->setSpeed(150);
  rightMotor->setSpeed(150);
}
