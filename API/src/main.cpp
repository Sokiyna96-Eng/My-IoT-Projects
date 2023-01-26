/*;----------------------
; Title: ESP8266 Wifi Database Insert
;----------------------
;Program Detail:
;----------------------
; Purpose: Send two sensor values from a microcontroller to create an insert query to a remote database
; Inputs: Press on or off button 
; Outputs: An updated database table with the new data on a website accessed via the internet
; Date: November 27, 2022 at 8:00 pm pst
; Compiler: Visual Studio Code version 1.71.2, Platform IO 2.5.4
; Author: Sokiyna Naser
; Versions:
;         V1- The ESP8266 connects to wifi to send queries to find the local timestamp, receives two sensor measurements
;             and creates an insert query to the remote database.
;----------------------
; File Dependencies:
;
;----------------------
;  Arduino.h
;  ESP8266WiFi.h
;  ESP8266HTTPClient.h
;  ArduinoJson.h
;  ArduinoOTA.h
;  DHT.h
;----------------------
; Main Program
;----------------------
*/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h> // must be installed
#include <ArduinoOTA.h>

#define BUTTON_PIN 16
int ledPin = 4;

const char *ssid = "DESKTOP-Suki";
const char *password = "ssu-suki123";
// Exampe: https://timeapi.io/api/Time/current/zone?timeZone=America/Los_Angeles
// String url = "https://timeapi.io/api/Time/current/zone?timeZone=America/Los_Angeles";
// String url = "https://timeapi.io/api/Time/current/zone?timeZone=America/Los_Angeles";
String url = "https://sokiyna.000webhostapp.com/API/result.txt";

DynamicJsonDocument doc(1024);
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  // join WiFi network
  Serial.println();
  Serial.println("Joining WiFI...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
}
void loop()
{
  ArduinoOTA.handle();
  delay(100);

  // read humidity

  byte buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW)
  {

    Serial.println("Button is pressed");
    ///
    String timeST;
    if (WiFi.status() == WL_CONNECTED)
    {
      WiFiClientSecure client;
      client.setInsecure();
      HTTPClient https;

      String fullUrl = url; // preparing the full URL

      Serial.println("Requesting: --> " + fullUrl);
      if (https.begin(client, fullUrl))
      {                             // start the connection 1=started / 0=failed
        int httpCode = https.GET(); // choose GET or POST method
        // int httpCode = https.POST(fullUrl); // need to include URL

        Serial.println("Response code <--: " + String(httpCode)); // print response code: e.g.,:200
        if (httpCode > 0)
        {
          // Serial.println(https.getString());       // this is the content of the get request received
          deserializeJson(doc, https.getString()); // deserialize the JSON file
                                                   /*--- Sample Response ----
                                                   {"year":2022,"month":10,"day":25,"hour":20,"minute":44,"seconds":11,"milliSeconds":405,
                                                   "dateTime":"2022-10-25T20:44:11.4055468","date":"10/25/2022","time":"20:44",
                                                   "timeZone":"America/Los_Angeles","dayOfWeek":"Tuesday","dstActive":true}
                                                   ------------------------ */
          deserializeJson(doc, https.getString()); // deserialize the JSON format into keys and values   
          Serial.println(https.getString());       // this is the content of the get request received
          String val1 = doc["Node1"]["LED1"];
          Serial.println(val1);
          if (val1 == "on")
          {
            Serial.println("LED1 is on");
            digitalWrite(ledPin, HIGH);
          }
          else
          {
            Serial.println("LED1 is off");
            digitalWrite(ledPin, LOW);
          }
          // get the value associated with the dataTime key       
          // Serial.println(mytime);
        }

        delay(5000); // delay between each REQUEST to the server                                                                                               // soomething like 2022-10-25T21:03:44.1790514
      }
      https.end(); // end of request
    }
    else
    {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }
}