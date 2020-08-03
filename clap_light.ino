/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on NodeMCU.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right NodeMCU module
  in the Tools -> Board menu!

  For advanced settings please follow ESP examples :
   - ESP8266_Standalone_Manual_IP.ino
   - ESP8266_Standalone_SmartConfig.ino
   - ESP8266_Standalone_SSL.ino

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xmw8pOFAKECPzdjhoSEd-Lg01i4RONYO-F";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "WifiSsid";
char pass[] = "WifiPass";

int claps = 0;
long detectionSpanInitial = 0;
long detectionSpan = 0;
boolean lightState = false;

void setup()
{
	// Debug console
	Serial.begin(9600);
	
	// initialize Blynk wifi connection
	Blynk.begin(auth, ssid, pass);

	pinMode(D7, INPUT);
	pinMode(D8, OUTPUT);
}

void loop()
{
  Blynk.run();

  int sensorState = digitalRead(D7);
 
  if (sensorState == 1) {
    if (claps == 0) {
      detectionSpanInitial = detectionSpan = millis();
      claps++;
    } else if (claps > 0 && millis()-detectionSpan >= 50) {
      detectionSpan = millis();
      claps++;
    }
  }
 
  if (millis()-detectionSpanInitial >= 400 && claps == 2) {
	if (lightState) {
		lightState = false;
		digitalWrite(D8, LOW);
	} else {
		lightState = true;
		digitalWrite(D8, HIGH);
	}
    claps = 0;
  }

}

