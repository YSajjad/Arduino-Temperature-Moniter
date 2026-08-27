#include <OneWire.h>
#include <DallasTemperature.h> // both libraries needed for tge sensor

#define OneWireBus 7
// The arduino digital pin connecting to the data output of the sensor
OneWire oneWire(OneWireBus);
DallasTemperature sensors(&oneWire);

const int led = 4;
const int piezo = 8;

//Temperature threshold needed to activate output devices
float ledThreshold = 30.0;
float piezoThreshold = 37.5;

void setup() {
  Serial.begin(9600);
  Serial.println("Beginning temperature readings");

  sensors.begin();

  pinMode(led,OUTPUT);
  pinMode(piezo,OUTPUT);

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

  Serial.println(tempC);

  delay(1500);
}
