#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <Hash.h>
#include "index.h"


ESP8266WiFiMulti wifiMulti;
WebSocketsServer webSocket = WebSocketsServer(81);
ESP8266WebServer server(80);

void handleRoot();
void sendData();

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP("IITH-Guest-PWD-IITH@2019", "IITH@2019");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("buhaha", "1234509876");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

    Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

  server.on("/", handleRoot);
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
  server.handleClient();
  sendData();
  delay(1000);
}

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
   if (type == WStype_TEXT){
    for(int i = 0; i < length; i++) Serial.print((char) payload[i]);
    Serial.println();
   }
}

void sendData(){
  int c = analogRead(A0);
  String data = String(c, 0);
  webSocket.broadcastTXT(data);
}
