#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <Hash.h>

String WebPage = "<!DOCTYPE html><html><style>input[type=\"text\"]{width: 90%; height: 3vh;}input[type=\"button\"]{width: 9%; height: 3.6vh;}.rxd{height: 90vh;}textarea{width: 99%; height: 100%; resize: none;}</style><script>var Socket;function start(){Socket=new WebSocket('ws://' + window.location.hostname + ':81/'); Socket.onmessage=function(evt){document.getElementById(\"rxConsole\").value +=evt.data;}}function enterpressed(){Socket.send(document.getElementById(\"txbuff\").value); document.getElementById(\"txbuff\").value=\"\";}</script><body onload=\"javascript:start();\"> <div><input class=\"txd\" type=\"text\" id=\"txbuff\" onkeydown=\"if(event.keyCode==13) enterpressed();\"><input class=\"txd\" type=\"button\" onclick=\"enterpressed();\" value=\"Send\" > </div><br><div class=\"rxd\"> <textarea id=\"rxConsole\" readonly></textarea> </div></body></html>";
ESP8266WiFiMulti wifiMulti;
ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

unsigned long previousMillis = 0;
unsigned long currentMillis;
unsigned long interval=200; //interval for sending data to the websocket server in ms

void handleRoot();
void handleNotFound();

float sensorRead();
void sensorCheck();
void webSendData(String data);
void webChat();

void setup() {

  Serial.begin(115200); // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP("IITH-Guest-PWD-IITH@2019", "IITH@2019"); // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("buhaha", "1234509876");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(1000);
    Serial.print(++i);
    Serial.print(' ');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID()); // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.on("/sensorcheck", sensorCheck);
  server.on("/webchat", webChat);
  //server.on("/sendData", webSendData);
  server.begin();
  Serial.println("HTTP server started");

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  currentMillis = millis();
  webSocket.loop();
  server.handleClient();
  if (abs(currentMillis - previousMillis) >= interval) {
    previousMillis = currentMillis;
    String sensorData = {(String) sensorRead()};
    webSendData(sensorData+"\n");
  }
}

void handleRoot() {
  server.send(200, "text/html", "<h1>Hai Engineer</h1><button onclick='location.href=\"/buzzeron\"' type='button'>Buzzer On</button><button onclick='location.href=\"/buzzeroff\"' type='button'>Buzzer Off</button><button onclick='location.href=\"/sensorcheck\"' type='button'>Check Sensor Value</button>");
}

void handleNotFound() {
  server.send(404, "text/html", "<h1 style='color=yellow'>404: Not found</h1>"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

float sensorRead() {
  int sensorValue = analogRead(A0);
  float voltage= sensorValue * (3.3 / 1023.0);
  return voltage;
}

void sensorCheck() {
  int sensorData = sensorRead();
  server.send(200, "text/html", "<h1>Hai Engineer</h1><h2>See the sensor value</h2> " + String(sensorData, 0) + "<br><button onclick='location.href=\"/buzzeron\"' type='button'>Buzzer On</button><button onclick='location.href=\"/buzzeroff\"' type='button'>Buzzer Off</button><button onclick='location.href=\"/sensorcheck\"' type='button'>Check Sensor Value</button>");
}

void webChat(){
    server.send(200, "text/html", WebPage);
}

void webSendData(String data){
    webSocket.broadcastTXT(data);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
   if (type == WStype_TEXT){
    for(int i = 0; i < length; i++) Serial.print((char) payload[i]);
    Serial.println();
   }
}
