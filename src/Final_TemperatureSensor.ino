#include <OneWire.h>
#include <Wire.h>
#include <DallasTemperature.h> // both libraries needed for the sensor

#include <LiquidCrystal_I2C.h> 

// wifi libraries
#include <WiFi.h>
#include <HTTPClient.h>

// left blank for github
const char* ssid = "";
const char* password = "";
String apiKey = "";

unsigned long previousMillisLogging = 0;
const unsigned long intervalLogging = 15000;// time interval to send to thingspeak

unsigned long previousMillisSensor = 0 ;
const unsigned long intervalSensor = 1000;// time interval to update sensor information

float tempC=0.0;//temperature from sensor

#define OneWireBus 4 // The pin connecting to the data output of the sensor
OneWire oneWire(OneWireBus);
DallasTemperature sensors(&oneWire);

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// pins for output devices
const int led = 18;
const int piezo = 19;


// Temperature threshold needed to activate output devices
float ledThreshold = 30.0;
float piezoThreshold = 37.5;
const int piezoFrequency = 1000; // frequency  which piezo will emit

void setup() {
  Serial.begin(115200);
  delay(1000);

  connectWifi();


  // input and output devices

  sensors.begin();

  pinMode(led,OUTPUT);
  pinMode(piezo,OUTPUT);

  Wire.begin(5,22); // setting SDA and SCL
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Temperature");
  delay(1500);
  lcd.clear();
}

void connectWifi(){//connects to wifi

  Serial.println("Attempting to connect to: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
}
void wifiCheck(){// checks if wifi is connected, reconnects if it isnt
  if (WiFi.status()==WL_CONNECTED){
    Serial.print("WiFi connected - ESP32 IP address: ");
    Serial.println(WiFi.localIP());
    return;
    }
  else{
    connectWifi();
  }
}
void sendTemp(float temperature) { // sends temperature to thingspeak

  if (WiFi.status()!=WL_CONNECTED){
    return;
  }

  HTTPClient http;

  String url = "http://api.thingspeak.com/update?api_key=" + String(apiKey) + "&field1=" + String(temperature);

  http.begin(url);

  int response = http.GET();
  Serial.print("ThingSpeak response:");
  Serial.println(response);

  http.end();
}

void updateOutputs(float temperature){
    if (temperature > ledThreshold) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }

  if (temperature > piezoThreshold) {
    tone(piezo, piezoFrequency);
  } else {
    noTone(piezo);       
  }
}

bool sensorConnectionCheck(float temperature) {
    if (temperature == DEVICE_DISCONNECTED_C) {
        Serial.println("Sensor disconnected");

        // turns LED nad piezo off
        digitalWrite(led, LOW);
        noTone(piezo);

        return false;
    }

    return true;
} 
void outputScreen(float temperature) {
    Serial.println("printing to screen");
    lcd.clear();

    lcd.setCursor(0,0);

    lcd.print("Temperature");
    lcd.setCursor(0,1);
    lcd.print(temperature);
    lcd.print((char)223);
    lcd.print("C");
}

void loop() {
  unsigned long currentMillis=millis();

  //every second
  if ((currentMillis-previousMillisSensor)>=intervalSensor){
      previousMillisSensor=currentMillis;

      sensors.requestTemperatures();
      tempC=sensors.getTempCByIndex(0);// Temperature from sensor
  
      if (!sensorConnectionCheck(tempC)) { // Checks if sensor is not connected
          return;
      }

      // Displays temp to LCD  
      outputScreen(tempC);

      // Output devices logic
      updateOutputs(tempC);
  }

  // every 15 seconds
  if ((currentMillis-previousMillisLogging)>=intervalLogging){
      previousMillisLogging=currentMillis;


      wifiCheck(); //checks if disconnected
      // Sends temperature to thingspeak
      sendTemp(tempC);
  }
}
