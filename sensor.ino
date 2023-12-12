#include <Servo.h>

const int servoPin = 9;
const int SERVO_TURN_DELAY = 500;

const int sensorEcho = 4;
const int sensorTrig = 5;

const int sensorEchoBack = 2;
const int sensorTrigBack = 3;

int servoAngle = 0;

long duration, cmFront, durationBack, cmBack;
volatile int state = HIGH;

Servo servo;

long microsecondsToCm(long microseconds)
{
	return microseconds / 29 / 2;
}

void setDriveMode(int x, int cm)
{

	Serial.println("--------------------------------------------------");
	Serial.println(cm);

	if (x < 65)
	{
		if (cm <= 40)
		{
			Serial.println("Vira a direita");
		}
	}

	if (x >= 65 && x <= 85)
	{
		if (cm <= 40)
		{
			Serial.println("Andar para tras");
		}
	}

	if (x > 85)
	{
		if (cm <= 40)
		{
			Serial.println("Vira a esquerda");
		}
	}
}

void pararCarroBack(int cmBack)
{

	Serial.println("--------------------------------------------------");
	Serial.println(cmBack);

	if (cmBack <= 40)
	{
		Serial.println("PARAR QUE VAI BATER");
	}
}

void readUltrassons(int x)
{
	digitalWrite(sensorTrig, LOW);
	delayMicroseconds(2);

	digitalWrite(sensorTrig, HIGH);
	delayMicroseconds(10);

	digitalWrite(sensorTrig, LOW);

	duration = pulseIn(sensorEcho, HIGH);

	cmFront = microsecondsToCm(duration);

	setDriveMode(x, cmFront);
}

void lerBack()
{
	digitalWrite(sensorTrigBack, LOW);
	delayMicroseconds(2);

	digitalWrite(sensorTrigBack, HIGH);
	delayMicroseconds(10);

	digitalWrite(sensorTrigBack, LOW);

	durationBack = pulseIn(sensorEchoBack, HIGH);

	cmBack = microsecondsToCm(durationBack);

	pararCarroBack(cmBack);
}

void setup()
{
	servo.attach(servoPin);
	Serial.begin(9600);

	pinMode(sensorEcho, INPUT);
	pinMode(sensorTrig, OUTPUT);

	pinMode(sensorEchoBack, INPUT);
	pinMode(sensorTrigBack, OUTPUT);
}

void loop()
{

	while (servoAngle < 150)
	{

		if (servoAngle == 0)
		{
			servoAngle = 50;
		}

		servo.write(servoAngle);
		delay(SERVO_TURN_DELAY);
		servoAngle = servoAngle + 10;
		readUltrassons(servoAngle);
		lerBack();

		servo.write(servoAngle);
		delay(SERVO_TURN_DELAY);
		servoAngle = servoAngle + 10;
		readUltrassons(servoAngle);
		lerBack();
	}
	// IP: 192.168.1.6
	while (servoAngle > 25)
	{
		if (servoAngle == 175)
		{
			servoAngle = 175;
		}

		servo.write(servoAngle);
		delay(SERVO_TURN_DELAY);
		servoAngle = servoAngle - 10;
		readUltrassons(servoAngle);
		lerBack();

		servo.write(servoAngle);
		delay(SERVO_TURN_DELAY);
		servoAngle = servoAngle - 10;
		readUltrassons(servoAngle);
		lerBack();
	}
}
