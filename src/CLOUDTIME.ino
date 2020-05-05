/*
 * Project CLOUDTIME
 * Description:
 * Author:
 * Date:
 */



#include "Particle.h"

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1); 

#define SSD1306_128_64 
   
int currentDateTime;


// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
 Serial.begin(9600);
   Wire.begin();
   while(!Serial);
   Serial.println("BeginlinSync");
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  sync_my_time();
  delay(random(10000,60000));   // just a random delay so that we can see this work (edited) 
 printcurrentDateTime();
}
void sync_my_time() {
  String DateTime;
  String TimeOnly;
  char currentDateTime[25];
  char currentTime[9];
  Time.zone(-6); // Set Time Zone to MDT (UTC - 7)
  unsigned long cur=millis();
  // Request time synch from Particle Device Cloud and wait for data to come back
  Particle.syncTime();
  waitUntil(Particle.syncTimeDone);
}
  // Check if synchronized successfully
  if (Particle.timeSyncedLast() >= cur) {
    DateTime = Time.timeStr();
    TimeOnly = DateTime.substring(11,19);       // pull out only Time from DateTime String
    Serial.println(DateTime);
    Serial.println(TimeOnly);
    // Using Time with Formatted Print Statements
    DateTime.toCharArray(currentDateTime,25);   // convert DateTime in to an array of char for printf()
    TimeOnly.toCharArray(currentTime,9);        // convert TImeOnly to an array of char for printf()
    Serial.printf("The current date and time is %s \n",currentDateTime);
    Serial.printf("The current time is %s \n",currentTime);
    Particle.syncTime();
    //Wait to receive time from Particle Device Cloud
    waitUntil(Particle.syncTimeDone);
    // Check if synchronized successfully
    if(Particle.timeSyncedLast() >= cur){
      // Print current time
      Serial.printlnf("Current time is %s",currentTime);//Time.timeStr().c_str());
    }  
  }

}
void printcurrentDateTime () {
  display.clearDisplay( );
  display.display();
  // display a pixel in each corner of the screen
  display.drawPixel(0, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(0, 63, WHITE);
  display.drawPixel(127, 63, WHITE);
 display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(27,30);
  display.print("currentDateTime");
   delay(1000);
   display.display();
   delay(1000);
   display.display();
}

}
 }