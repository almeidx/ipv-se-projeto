#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "labmicro";
const char *password = "microwifi";

// 0 - Manual
// 1 - Automático
int drive_state = 0;

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

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
  server.on("/drive_state", HTTP_GET, handleDriveState);

  server.begin();

  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String response = "Hello from ESP8266!";
  server.send(200, "text/plain", response);
}

void handleForward() {
  String response = "Moving forward!";
  server.send(200, "text/plain", response);
}

void handleBackward() {
  String response = "Moving backward!";
  server.send(200, "text/plain", response);
}

void handleLeft() {
  String response = "Moving left!";
  server.send(200, "text/plain", response);
}

void handleRight() {
  String response = "Moving right!";
  server.send(200, "text/plain", response);
}

void handleDriveState() {
  String response = String(drive_state);
  server.send(200, "text/plain", response);
}
