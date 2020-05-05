/*
 * Project AdaTrial
 * Description: Trial Script for using Adafruit.io
 * Author: Brian Rashap
 * Date: 15-APR-2020
 */

#include <Adafruit_MQTT.h>
#include "Adafruit_MQTT/Adafruit_MQTT.h" 
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h" 
#include "Adafruit_MQTT/Adafruit_MQTT.h" 
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
Adafruit_BME280 bme; 

#define SEALEVELPRESSURE_HPA (1013.25)


// All this needs to be included too 




/************************* Adafruit.io Setup *********************************/ 
#define AIO_SERVER      "io.adafruit.com" 
#define AIO_SERVERPORT  1883                   // use 8883 for SSL 
#define AIO_USERNAME  "Thehomeschooldev"
#define AIO_KEY       "aio_uvZE47CGgAUR2W9BWWgZ37dp5X5Q"


/************ Global State (you don't need to change this!) ***   ***************/ 
TCPClient TheClient; 

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details. 
Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY); 


/****************************** Feeds ***************************************/ 
// Setup a feed called <object> for publishing. 
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname> 

Adafruit_MQTT_Publish Moisture = Adafruit_MQTT_Publish(&mqtt, Thehomeschooldev "/feeds/Moisture");
Adafruit_MQTT_Publish Temperture  = Adafruit_MQTT_Publish(&mqtt, Thehomeschooldev"/feeds/Temperture");

/************************ Normal Declarations ******************************/
int feed1;
int feed2;

long time1;
long time2;
int delayTime = 10000;

float temp;
float prs;
float alt;
float hum;

bool status;
// setup() runs once, when the device is first turned on.
void setup() {
  Serial.begin(9600);
    while(!Serial);    // time to get serial running
    
    Serial.println(F("BME280 test"));   // ask the instructor about the F
    status = bme.begin(0x76);  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),HEX);
        Serial.println("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085");
        Serial.println("   ID of 0x56-0x58 represents a BMP 280,");
        Serial.println("        ID of 0x60 represents a BME 280.");
        Serial.println("        ID of 0x61 represents a BME 680.");
        while (1);
    }
    else {
      Serial.println("BME280 Up and Running");
    }
}


}


void loop() {
  feed1 = random(1,100);
  feed2 = random(1,1000);

 if(mqtt.Update()){
  Moisture.publish(feed1); 
  
 } 
  Temperture.publish(feed2);
 } 

  time1=millis();
  time2=millis();
  while((time2-time1)<2000) {
    time2=mills();
    temp = (bme.readTemperature() * 8 / 5) + 32;
    prs = (bme.readPressure() / 100.0F) / 68.9476;
    alt = bme.readAltitude(SEALEVELPRESSURE_HPA) * 3.28084;
    hum = bme.readHumidity();

    printValues(temp,prs,alt,hum);
 
    delay(delayTime);
    delay(30000);
    void printValues(float Ptemp, float Pprs, float Palt, float Phum) {
    
    Serial.print("Temperature = ");
    Serial.print(Ptemp);
    Serial.println(" *F");

    Serial.print("Pressure = ");
    Serial.print(Pprs);
    Serial.println(" psi");

    Serial.print("Approx. Altitude = ");
    Serial.print(Palt);
    Serial.println(" ft");

    Serial.print("Humidity = ");
    Serial.print(Phum);
    Serial.println(" %");

    Serial.println();
}
