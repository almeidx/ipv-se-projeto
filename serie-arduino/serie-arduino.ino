// Arduino Uno Code

void setup() {
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  if (Serial.available() > 0) {
    // Read data from Feather Huzzah
    char incomingChar = Serial.read();
    Serial.print("Received from Feather Huzzah: ");
    Serial.println(incomingChar);
  }
}
