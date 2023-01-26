#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h> // must be installed
#include <ArduinoOTA.h>
#include <SPI.h>
#include <ESP8266mDNS.h>

int Led = 0;
int ledPin = 2;
int buttonpin = 4; // define D0 SensorInterface
int LED = 15;
int buzzer = 5; // 0 close - 1 open switch

int sensorPin = A0;
int sensorValue = 0;
int val;
unsigned long myTime;

const char *ssid = "DESKTOP-Suki";    // The SSID (name) of the Wi-Fi network you want to connect to
const char *password = "ssu-suki123"; // The password of the Wi-Fi network

// Exampe: https://timeapi.io/api/Time/current/zone?timeZone=America/Los_Angeles
String url = "https://timeapi.io/api/Time/current/zone?timeZone=America/Los_Angeles";
// https://faridfarahmand.000webhostapp.com/PHPCRUD/firstphp_db_insert.php?nodeId=node_3&nodeTemp=39&timeReceived=2022-10-25T20:44:11.4055468
String url1 = "https://sokiyna.000webhostapp.com/IoTmidTerm/insertion_db.php?";
DynamicJsonDocument doc(1024);

void setup()
{
    Serial.begin(9600);

    WiFi.begin(ssid, password); // Connect to the network
    Serial.print("Connecting to ");
    Serial.print(ssid);

    while (WiFi.status() != WL_CONNECTED)
    { // Wait for the Wi-Fi to connect
        delay(500);
        digitalWrite(LED, LOW); // turn the LED off
        Serial.print('.');
        // wait for a second
        noTone(buzzer);
    }

    // if you are connected, print out info about the connection:

    Serial.println('\n');
    Serial.println("Connection established!");
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer

    // print the received signal strength:

    pinMode(LED, OUTPUT);
    pinMode(buzzer, OUTPUT);

    delay(10);
    Serial.println('\n');
    pinMode(Led, OUTPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(buttonpin, INPUT);
}

void loop()
{
    

    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue, DEC);
    digitalWrite(ledPin, HIGH);
    delay(500);
    // delay(sensorValue);
    digitalWrite(ledPin, LOW);
    delay(500);
    // delay(sensorValue);
    // Serial.println(sensorValue);
    delay(500);
    val = digitalRead(buttonpin);
    // Serial.println(val, DEC);
    // if (val == HIGH)
    // {
    //     digitalWrite(Led, HIGH);
    // }
    // else
    // {
    //     digitalWrite(Led, LOW);
    // }

    if (sensorValue > 30 && sensorValue < 33)
    {

        myTime = millis() / 1000;
        delay(2000);
    }

    
    Serial.print("duration is:");
    Serial.println(myTime);

    long rssi = WiFi.RSSI();
    long rssiValue = -50;

    Serial.print("RSSI:");
    Serial.println(rssi);
    // if the rssi is less than -75 turn the buzzer on
    if (rssi < rssiValue)
    {
        tone(buzzer, 1000);
        delay(3000);

        Serial.println("Buzzer working");
        noTone(buzzer);
    }

    String timeST;
    if (myTime > 2)
    {
        if (WiFi.status() == WL_CONNECTED)
        {                            // Wait for the Wi-Fi to connect
            digitalWrite(LED, HIGH); // turn the LED on
            delay(1000);
            WiFiClientSecure client;
            client.setInsecure();
            HTTPClient https;
            String fullUrl = url; // preparing the full URL

            Serial.println("Requesting: --> " + fullUrl);
            if (https.begin(client, fullUrl))
            {                               // start the connection 1=started / 0=failed
                int httpCode = https.GET(); // choose GET or POST method
                // int httpCode = https.POST(fullUrl); // need to include URL

                Serial.println("Response code <--: " + String(httpCode)); // print response code: e.g.,:200
                if (httpCode > 0)
                {
                    Serial.println(https.getString());       // this is the content of the get request received
                    deserializeJson(doc, https.getString()); // deserialize the JSON file
                                                             /*--- Sample Response ----
                                                             {"year":2022,"month":10,"day":25,"hour":20,"minute":44,"seconds":11,"milliSeconds":405,
                                                             "dateTime":"2022-10-25T20:44:11.4055468","date":"10/25/2022","time":"20:44",
                                                             "timeZone":"America/Los_Angeles","dayOfWeek":"Tuesday","dstActive":true}
                                                             ------------------------ */
                    deserializeJson(doc, https.getString()); // deserialize the JSON format into keys and values
                    String mytime = doc["dateTime"];
                    timeST = mytime; // get the value associated with the dataTime key
                    // Serial.println(mytime);
                }

                delay(5000); // delay between each REQUEST to the server
            }
            https.end(); // end of request
        }

        else
        {
            Serial.printf("[HTTPS] Unable to connect\n");
        }
        if (WiFi.status() == WL_CONNECTED)
        {
            WiFiClientSecure client;
            client.setInsecure();
            HTTPClient https;
            long rssi = WiFi.RSSI();
            String fullUrl_insert = url1 + "node=node-1" + "&duration=" + myTime + "&RSSI=" + rssi + "&time_sent=" + timeST; // preparing the full URL                                                                                                                       // polyacid-bars.000webhostapp.com/firstphp_db_insert.php?node_name=node-3&temperature=18.10&time_received=2022-11-01T20:03:06.8062296&humidity=64.00
            Serial.println(fullUrl_insert);

            Serial.println("Requesting: --> " + fullUrl_insert);
            if (https.begin(client, fullUrl_insert))
            { // start the connection 1=started / 0=failed

                int httpCode = https.GET(); // choose GET or POST method
                // int httpCode = https.POST(fullUrl_insert); // need to include URL

                Serial.println("Response code <--: " + String(httpCode)); // print response code: e.g.,:200
                if (httpCode > 0)
                {
                    Serial.println(https.getString()); // this is the content of the get request received
                }
                https.end(); // end of request
            }
            else
            {
                Serial.printf("[HTTPS] Unable to connect\n");
            }
        }
        delay(5000); // delay between each REQUEST to the server
    }
}