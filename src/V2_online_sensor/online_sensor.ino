#include <OneWire.h>
#include <DallasTemperature.h> // both libraries needed for the sensor

// wifi libraries
#include <WiFi.h>
#include <HTTPClient.h>

// left blank for github
const char* ssid = "";
const char* password = "";
String apiKey = "";

#define OneWireBus 4
// The pin connecting to the data output of the sensor
OneWire oneWire(OneWireBus);
DallasTemperature sensors(&oneWire);

// pins for output devices
const int led = 18;
const int piezo = 19;


// Temperature threshold needed to activate output devices
float ledThreshold = 30.0;
float piezoThreshold = 37.5;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Attempting to connect to: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());

  sensors.begin();

  pinMode(led,OUTPUT);
  pinMode(piezo,OUTPUT);
}

void sendTemp(float temperature) { // sends temperature to thingspeak

  HTTPClient http;

  String url = "http://api.thingspeak.com/update?api_key=" + String(apiKey) + "&field1=" + String(temperature);

  http.begin(url);

  int response = http.GET();
  Serial.print("ThingSpeak response:");
  Serial.println(response);

  http.end();
}


void loop() {

   sensors.requestTemperatures();

  float tempC=sensors.getTempCByIndex(0);// Temperature from sensor
  
  if (tempC == DEVICE_DISCONNECTED_C){ // if sensor not connected
    Serial.println("Sensor disconnected");

    digitalWrite(led, LOW);
    noTone(piezo);

    delay(1000);
    return;
    }

  
  // Output devices logic
  if (tempC > ledThreshold) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }

  if (tempC > piezoThreshold) {
    tone(piezo, 1000);
  } else {
    noTone(piezo);       
  }

  sendTemp(tempC);
  millis(20000);

}
