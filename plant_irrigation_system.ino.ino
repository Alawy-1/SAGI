#include <WiFi.h>
#include <WebServer.h>

const int ledPin = 2;
const int soilPin = 4;
const int relayPin = 26;
const int DRY_VALUE = 3400; 
const int WET_VALUE = 3100;
const int threshold = 3230;

const char* ssid = "Tuwaiq's Students";
const char* password = "Tuwaiq@001";

WebServer server(80);

String getHTML() {
  int rawValue = analogRead(soilPin);
  
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>Plant Irrigation</title>";
  html += "<meta http-equiv='refresh' content='5'>";
  html += "<style>";
  html += "body { font-family: Arial; text-align: center; background: #e8f5e9; padding: 30px; }";
  html += "h1 { color: #2e7d32; }";
  html += ".card { background: white; padding: 20px; border-radius: 12px; margin: 20px auto; max-width: 400px; box-shadow: 0 2px 8px rgba(0,0,0,0.1); }";
  html += ".value { font-size: 48px; font-weight: bold; color: #2e7d32; }";
  html += "</style></head><body>";
  html += "<h1>🌱 Plant Irrigation System</h1>";
  html += "<div class='card'>";
  html += "<h2>Soil Moisture (Raw)</h2>";
  html += "<p class='value'>" + String(rawValue) + "</p>";
  html += "</div>";
  html += "</body></html>";
  
  return html;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(ledPin, OUTPUT);
  pinMode(soilPin, INPUT);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  Serial.println("Connecting to Wifi");
  WiFi.begin(ssid, password);

  if (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();

  // Wait for the IP to be assigned
  delay(4000);

  Serial.println("Wi-Fi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/html", getHTML());
  });
  
  server.begin();
  Serial.println("Web server started!");
  Serial.print("Open this in your browser: http://");
  Serial.println(WiFi.localIP());
  
  Serial.println();
  Serial.println("Plant Irrigation System");
}

void loop() {
  server.handleClient();
  int soilValue = analogRead(soilPin);

  Serial.print("soil Pin value:");
  Serial.println(soilValue);

  if(soilValue > threshold){
    digitalWrite(ledPin, HIGH);
    //digitalWrite(relayPin, HIGH);
    Serial.println("LED ON | PUMP ON");
  } else {
    digitalWrite(ledPin, LOW);
    //digitalWrite(relayPin, LOW);
    Serial.println("LED OFF | PUMP OFF");
  }
  
  delay(10000);

}
