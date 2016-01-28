
/*
 * ESP8266 REST and AP Config
 *
 * RESTful environment https://github.com/marcoschwartz/aREST#api-documentation
 * with WiFi Connection manager and fallback web configuration portal
 * for the ESP8266 WiFi chip
 * 
 */
 
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for WiFiManager library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include <aREST.h>               //https://github.com/marcoschwartz/aREST


// Create aREST instance
aREST rest = aREST();

// The port to listen for incoming TCP connections
#define LISTEN_PORT 80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

void setup() {

  Serial.begin(115200);

  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("ESP8266_REST");

  //WiFiManager
  WiFiManager wifiManager;

  //fetches ssid and pass from eeprom and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "ESP8266_AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("ESP8266_AutoConnectAP");

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
  
  server.begin();
}

void loop() {

  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  rest.handle(client);

}
