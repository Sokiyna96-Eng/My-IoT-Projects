// #include <Arduino.h>
// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>
// #include <ArduinoJson.h> // must be installed
// #include <ArduinoOTA.h>


// int LED = 4;
// const char *ssid = "DESKTOP-Suki";
// const char *password = "ssu-suki123";
// // Exampe: https://timeapi.io/api/Time/current/zone?timeZone=America/Los_Angeles
// String url = "https://timeapi.io/api/Time/current/zone?timeZone=America/Los_Angeles";
// // https://faridfarahmand.000webhostapp.com/PHPCRUD/firstphp_db_insert.php?nodeId=node_3&nodeTemp=39&timeReceived=2022-10-25T20:44:11.4055468
// String url1 = "https://sokiyna.000webhostapp.com/firstphp_insert.php?";
// DynamicJsonDocument doc(1024);
// void setup()
// {
//   pinMode(LED, OUTPUT);
//   Serial.begin(9600);
//   dht.begin();                       // initialize the sensor 
//   pinMode(BUTTON_PIN, INPUT_PULLUP); // start with led OFF
//   // join WiFi network
//   Serial.println();
//   Serial.println("Joining WiFI...");
//   WiFi.mode(WIFI_STA);
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("");
//   Serial.println("WiFi connected.");
//   Serial.print("IP address: ");
//   Serial.println(WiFi.localIP());
//   Serial.println(WiFi.macAddress());
//   digitalWrite(LED, HIGH); // turn the LED on
//   delay(1000); // wait for a second
// }
// void loop()
// {

//   ArduinoOTA.handle();
//   delay(100);

//   // read humidity
//   float humi = dht.readHumidity();
//   delay(10);
//   // read temperature as Celsius
//   float tempC = dht.readTemperature();

//   byte buttonState = digitalRead(BUTTON_PIN);
//   if (buttonState == LOW)
//   {

//     Serial.println("Button is pressed");
//     // check if any reads failed
//     if (isnan(humi) || isnan(tempC))
//     {
//       Serial.println("Failed to read from DHT sensor!");
//     }
//     else if (humi || tempC)
//     {
//       Serial.print("Humidity: ");
//       Serial.print(humi);
//       Serial.print("%");

//       Serial.print("  |  ");

//       Serial.print("Temperature: ");
//       Serial.print(tempC);
//       Serial.print(" C ");
//       Serial.println();
//     }
//     else
//     {
//       Serial.println("Button is not pressed");
//     }
//     delay(100);
//     ///
//     String timeST;
//     if (WiFi.status() == WL_CONNECTED)
//     {
//       digitalWrite(LED, HIGH); // turn the LED on
//       delay(1000); // wait for a second
//       WiFiClientSecure client;
//       client.setInsecure();
//       HTTPClient https;

//       String fullUrl = url; // preparing the full URL

//       Serial.println("Requesting: --> " + fullUrl);
//       if (https.begin(client, fullUrl))
//       {                             // start the connection 1=started / 0=failed
//         int httpCode = https.GET(); // choose GET or POST method
//         // int httpCode = https.POST(fullUrl); // need to include URL

//         Serial.println("Response code <--: " + String(httpCode)); // print response code: e.g.,:200
//         if (httpCode > 0)
//         {
//           Serial.println(https.getString());       // this is the content of the get request received
//           deserializeJson(doc, https.getString()); // deserialize the JSON file
//                                                    /*--- Sample Response ----
//                                                    {"year":2022,"month":10,"day":25,"hour":20,"minute":44,"seconds":11,"milliSeconds":405,
//                                                    "dateTime":"2022-10-25T20:44:11.4055468","date":"10/25/2022","time":"20:44",
//                                                    "timeZone":"America/Los_Angeles","dayOfWeek":"Tuesday","dstActive":true}
//                                                    ------------------------ */
//           deserializeJson(doc, https.getString()); // deserialize the JSON format into keys and values       
//           String mytime = doc["dateTime"];
//           timeST = mytime; // get the value associated with the dataTime key       
//           Serial.println(mytime);
//         }

//         delay(5000); // delay between each REQUEST to the server                                                                                               // soomething like 2022-10-25T21:03:44.1790514
//       }
//       https.end(); // end of request
//     }
//     else
//     {
//       Serial.printf("[HTTPS] Unable to connect\n");
//     }
//     if (WiFi.status() == WL_CONNECTED)
//     {
//       WiFiClientSecure client;
//       client.setInsecure();
//       HTTPClient https;

//       String fullUrl_insert = url1 + "node_name=node-1" + "&time_received=" + timeST + "&temperature=" + tempC + "&humidity=" + humi; // preparing the full URL                                                                                                                       // polyacid-bars.000webhostapp.com/firstphp_db_insert.php?node_name=node-3&temperature=18.10&time_received=2022-11-01T20:03:06.8062296&humidity=64.00
//       Serial.println(fullUrl_insert);

//       Serial.println("Requesting: --> " + fullUrl_insert);
//       if (https.begin(client, fullUrl_insert))
//       { // start the connection 1=started / 0=failed

//         int httpCode = https.GET(); // choose GET or POST method
//         // int httpCode = https.POST(fullUrl_insert); // need to include URL

//         Serial.println("Response code <--: " + String(httpCode)); // print response code: e.g.,:200
//         if (httpCode > 0)
//         {
//           Serial.println(https.getString()); // this is the content of the get request received
//         }
//         https.end(); // end of request
//       }
//       else
//       {
//         Serial.printf("[HTTPS] Unable to connect\n");
//       }
//     }
//     delay(5000); // delay between each REQUEST to the server
//   }
// }

