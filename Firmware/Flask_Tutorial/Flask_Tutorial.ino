/****************************************************************************
Flask_Tutorial.ino
Arduino code for Flask Tutorial
Mike Hord @ SparkFun Electronics
24 Oct 2017
https://github.com/sparkfun/Flask_Tutorial

This simple example (derived from the BasicHttpClient example that comes
with the ESP8266 Arduino support package) connects to WiFi then waits for a
button press on either of two buttons to send an HTTP request to a Flask
app running on a server.

Resources:
None

Development environment specifics:
Arduino 1.8.1
ESP8266 Arduino Support v2.3.0

This code is beerware; if you see me (or any other SparkFun employee) at the 
local, and you've found our code helpful, please buy us a round!
****************************************************************************/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup() 
{
  Serial.begin(115200);

  // ESP8266 takes a few moments to boot, so we give it a few seconds
  for(uint8_t t = 4; t > 0; t--) 
  {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  // Add the WiFi access point information
  WiFiMulti.addAP("sparkfun-guest", "sparkfun6333");

  // Set our buttons pins to inputs with pullup resistors enabled
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);

}

void loop() 
{
  // wait for WiFi connection
  if((WiFiMulti.run() == WL_CONNECTED)) 
  {
    // Check if button 12 is pressed...
    if (digitalRead(12) == LOW)
    {
      //...and if so, issue a GET request of the format
      //  gpio/x/y, where x is the desired pin and y is the
      //  desired level to set the pin to. Currently the
      //  Flask app only supports pin 2.
      HTTPClient http;
      http.begin("http://10.8.253.193:5000/gpio/2/0");
      int httpCode = http.GET();
      http.end();
    }
    // Repeat the process for pin 13.
    if (digitalRead(13) == LOW)
    {
      HTTPClient http;
      http.begin("http://10.8.253.193:5000/gpio/2/1");
      int httpCode = http.GET();
      http.end();
    }
  }
  else
  {
    Serial.println("No WiFi");
  }
}

