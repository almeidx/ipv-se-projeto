#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "Gane"; //"labmicro";
const char *password = "naosei123";  // "microwifi";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("*");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/forward", HTTP_GET, handleForward);
  server.on("/backward", HTTP_GET, handleBackward);
  server.on("/left", HTTP_GET, handleLeft);
  server.on("/right", HTTP_GET, handleRight);
  server.on("/stop", HTTP_GET, handleStop);
  server.on("/automatic", HTTP_GET, handleAutomatic);
  server.on("/manual", HTTP_GET, handleManual);
  server.on("/increase", HTTP_GET, handleIncrease);
  server.on("/decrease", HTTP_GET, handleDecrease);

  server.onNotFound(handleNotFound);

  server.begin();

  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String response = "Hello from ESP8266!";
  server.send(200, "text/plain", response);
  Serial.println(response);
}

void handleForward() {
  String response = "Moving forward ...";
  server.send(200, "text/plain", response);
  Serial.println(response);
}

void handleBackward() {
  String response = "Moving backward ...";
  server.send(200, "text/plain", response);
  Serial.println(response);
}

void handleLeft() {
  String response = "Moving left ...";
  server.send(200, "text/plain", response);
  Serial.println(response);
}

void handleRight() {
  String response = "Moving right ...";
  server.send(200, "text/plain", response);
  Serial.println(response);
}

void handleStop() {
  String response = "State stop ...";
  server.send(200, "text/plain", response);
  Serial.println(response);
}

void handleAutomatic() {
  String response = "Mode automatic ...";
  server.send(200, "text/plain", response);
  Serial.println(response);
}

void handleManual() {
  String response = "Mode manual ...";
  server.send(200, "text/plain", response);
  Serial.println(response);
}

void handleIncrease() {
  String response = "State increase ...";
  server.send(200, "text/plain", response);
  Serial.println(response);
}

void handleDecrease() {
  String response = "State decrease ...";
  server.send(200, "text/plain", response);
  Serial.println(response);
}

void handleNotFound() {
  String response = "404 Not Found";
  server.send(404, "text/plain", response);
  Serial.println(response);
}
