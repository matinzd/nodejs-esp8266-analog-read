#include <WebSocketsClient.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <string>

const char* SSID = "WIFI_NAME";
const char* PASSWORD = "WIFI_PASSWORD";
const char* WEBSOCKET_HOST = "ws.example.com";
const int WEBSOCKET_PORT = 3000;

WebSocketsClient webSocket;

void connectToWiFi() {
  Serial.println();

  WiFi.begin(SSID, PASSWORD);
  Serial.printf("Connecting to WiFi %s ", SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

// Handler for websocket events
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED: {
      Serial.printf("[WSc] Connected to url: %s\n", payload);
        webSocket.sendTXT("Websocket Connection From Arduino");
      }
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] get text: %s\n", payload);
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);

      // send data to server
      // webSocket.sendBIN(payload, length);
      break;
        case WStype_PING:
            Serial.printf("[WSc] get ping\n");
            break;
        case WStype_PONG:
            Serial.printf("[WSc] get pong\n");
            break;
    }

}


void connectToWebsocketServer() {
  // server address, port and URL
  webSocket.begin(WEBSOCKET_HOST, WEBSOCKET_PORT, "/");

  // event handler
  webSocket.onEvent(webSocketEvent);

  // try ever 5000 again if connection has failed
  webSocket.setReconnectInterval(5000);
  webSocket.enableHeartbeat(15000, 3000, 2);
}

float getVoltage(int sensorValue) {
  return sensorValue * (5.0 / 1023.0);
}

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  connectToWiFi();
  connectToWebsocketServer();
}

void loop() {
  webSocket.loop();
  String voltageStr = String(getVoltage(analogRead(A0)));
  String log = "Voltage from arduino " + voltageStr;
  Serial.println(log);
  webSocket.sendTXT(voltageStr);
  delay(500);
}
