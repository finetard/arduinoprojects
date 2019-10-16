#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h> 
#include <ESP8266WebServer.h>


const char *ssid = "IITH-Guest-PWD-IITH@2019";  //ENTER YOUR WIFI SETTINGS
const char *password = "IITH@2019";


/*
const char *ssid = "buhaha";  //ENTER YOUR WIFI SETTINGS
const char *password = "1234509876";
*/
ESP8266WebServer server(80);

void handleRoot();

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());  
    if (!MDNS.begin("esp8266",WiFi.localIP())) {             // Start the mDNS responder for esp8266.local
    Serial.println("Error setting up MDNS responder!");
    }
    else {
    Serial.println("mDNS responder started");
    }
  server.on("/", handleRoot);  //Associate handler function to path

server.begin();                           //Start server
Serial.println("HTTP server started");
 }

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/plain", "Hello world!");   // Send HTTP status 200 (Ok) and send some text to the browser/client
}
