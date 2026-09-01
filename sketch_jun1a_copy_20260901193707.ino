#include <WiFi.h>

const int ENA = 4;
const int IN1 = 12;
const int IN2 = 14;

const int ENB = 5;
const int IN3 = 26;
const int IN4 = 25;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  
  stopRobot();

  Serial.print("Setting up Wi-Fi Network...");
  WiFi.softAP("Hager_Robot", "12345678");

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin();
  Serial.println("Server Started! Ready for control.");
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client Connected.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            
            client.print("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"></head>");
            client.print("<body style=\"text-align:center; font-family:Arial; background-color:#f0f0f0;\">");
            client.print("<h1 style=\"color:#333;\">Hager Robot Control</h1><br>");
            
            client.print("<a href=\"/F\"><button style=\"width:140px; height:60px; font-size:20px; margin:10px; border-radius:10px; background-color:#4CAF50; color:white;\">&#x25B2; FORWARD</button></a><br>");
            client.print("<a href=\"/L\"><button style=\"width:110px; height:60px; font-size:20px; margin:10px; border-radius:10px; background-color:#2196F3; color:white;\">&#x25C0; LEFT</button></a>");
            client.print("<a href=\"/S\"><button style=\"width:110px; height:60px; font-size:20px; margin:10px; border-radius:10px; background-color:#f44336; color:white; font-weight:bold;\">STOP</button></a>");
            client.print("<a href=\"/R\"><button style=\"width:110px; height:60px; font-size:20px; margin:10px; border-radius:10px; background-color:#2196F3; color:white;\">RIGHT &#x25B6;</button></a><br>");
            client.print("<a href=\"/B\"><button style=\"width:140px; height:60px; font-size:20px; margin:10px; border-radius:10px; background-color:#4CAF50; color:white;\">&#x25BC; BACKWARD</button></a>");
            
            client.print("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        if (currentLine.endsWith("GET /F")) { moveForward(); }
        if (currentLine.endsWith("GET /B")) { moveBackward(); }
        if (currentLine.endsWith("GET /L")) { turnLeft(); }
        if (currentLine.endsWith("GET /R")) { turnRight(); }
        if (currentLine.endsWith("GET /S")) { stopRobot(); }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, 220);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); analogWrite(ENB, 220);
}

void moveBackward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); analogWrite(ENA, 220);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); analogWrite(ENB, 220);
}

void turnLeft() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, 200);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); analogWrite(ENB, 200);
}

void turnRight() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); analogWrite(ENA, 200);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); analogWrite(ENB, 200);
}

void stopRobot() {
  analogWrite(ENA, 0); analogWrite(ENB, 0);
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}