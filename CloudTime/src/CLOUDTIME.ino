/*
 * Project CLOUDTIME
 * Description:
 * Author:
 * Date:
 */
#include <Particle.h>
// setup() runs once, when the device is first turned on.
void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println ("BeginlineSync");
  
  // Put initialization like pinMode and begin functions here.
 // wait for Serial monitor 13 Serial.println("-------- Begin Time Sync --------"); 14 }
// wait for Serial monitor 13 Serial.println("-------- Begin Time Sync --------"); 14 }
}
// loop() runs over and over again, as quickly as it can execute.
void loop() {sync_my_time();
delay (random(1000,6000));
}

  // The core of your code will likely live here.
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
  // Check if synchronized successfully
  if(Particle.timeSyncedLast() >= cur) {
    DateTime = Time.timeStr();
    TimeOnly = DateTime.substring(11,19);       // pull out only Time from DateTime String
    Serial.println(DateTime);
    Serial.println(TimeOnly);
    // Using Time with Formatted Print Statements
    DateTime.toCharArray(currentDateTime,25);   // convert DateTime in to an array of char for printf()
    TimeOnly.toCharArray(currentTime,9);        // convert TImeOnly to an array of char for printf()
    Serial.printf("The current date and time is %s \n",currentDateTime);
    Serial.printf("The current time is %s \n",currentTime);
  }
}

