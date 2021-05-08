#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <stdint.h>
#include <ArduinoJson.h>
#include "time.h"
#include <DHT.h>

#define PROTOCOL_PAYLOAD_SIZE   1024
#define DEVICE_NAME             16

#define DHTPIN D1
#define DHTTYPE DHT11 // DHT 11

typedef enum 
{
    Temperature,
    Humidity,
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

const char *sensors_str[] =
{
   "Temperature",
   "Humidity",
   "Barometer",
   "Air_Quality",
   "Rain_Detector",
   "Luminosity"
};

  
// Set WiFi credentials
#define WIFI_SSID "SSID"
#define WIFI_PASS "password"
#define UDP_PORT 1234

DHT dht(DHTPIN, DHTTYPE);
 
// UDP
WiFiUDP UDP;
char packet[255];

NTPClient timeClient(UDP, "pool.ntp.org");

static char buffer[PROTOCOL_PAYLOAD_SIZE + sizeof(Header) + 1];
static char toString[120];
static Protocol protocol;

StaticJsonDocument<200> doc;

 
void setup() {
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
  
  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  dht.begin();
  
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

    float temperatura_lida = 0.0;
    float umidade_lida = 0.0;

    temperatura_lida = dht.readTemperature();
    umidade_lida = dht.readHumidity();

    memset(toString, 0, sizeof(toString));
    snprintf(toString, 120, "%f", temperatura_lida);
 
    doc["id"] = 1;
    doc["sensor"] = Temperature;
    doc["device"] = sensors_str[Temperature];
    doc["time"] = timeClient.getEpochTime();
    doc["size"] = strlen(toString);
    doc["payload"] = toString;

    serializeJson(doc, buffer);    
    
    UDP.beginPacket("192.168.0.140", 1234);
    UDP.write(buffer);
    UDP.endPacket();


    memset(toString, 0, sizeof(toString));    
    snprintf(toString, 120, "%f", umidade_lida);
 
    doc["id"] = 2;
    doc["sensor"] = Humidity;
    doc["device"] = sensors_str[Humidity];
    doc["time"] = timeClient.getEpochTime();
    doc["size"] = strlen(toString);
    doc["payload"] = toString;

    serializeJson(doc, buffer);    
    
    UDP.beginPacket("192.168.0.140", 1234);
    UDP.write(buffer);
    UDP.endPacket();
    delay(1000); 
}