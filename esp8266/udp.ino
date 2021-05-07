#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <stdint.h>
#include <ArduinoJson.h>
#include "time.h"

#define PROTOCOL_PAYLOAD_SIZE   1024
#define DEVICE_NAME             16

typedef enum 
{
    Temperature,
    Barometer,
    Air_Quality,
    Rain_Detector,
    Luminosity
} Sensors;

typedef struct 
{
    uint8_t id;
    Sensors sensor;
    char device[DEVICE_NAME];
    time_t data;
    uint32_t size;
} Header;

typedef struct 
{
    Header header;
    char payload[PROTOCOL_PAYLOAD_SIZE];
} Protocol;

  
// Set WiFi credentials
#define WIFI_SSID "SSID"
#define WIFI_PASS "password"
#define UDP_PORT 1234
 
// UDP
WiFiUDP UDP;
char packet[255];

NTPClient timeClient(UDP, "pool.ntp.org");

static char buffer[PROTOCOL_PAYLOAD_SIZE + sizeof(Header) + 1];
static Protocol protocol;

StaticJsonDocument<200> doc;

 
void setup() {
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
  
  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  
}
 
void loop() {
 
    doc["id"] = 1;
    doc["sensor"] = Temperature;
    doc["device"] = "esp8266";
     doc["time"] = timeClient.getEpochTime();
    doc["size"] = strlen("Hello World");
    doc["payload"] = "Hello World";

    serializeJson(doc, buffer);
    
    UDP.beginPacket("192.168.0.140", 1234);
    UDP.write(buffer);
    UDP.endPacket();
    delay(1000); 
}