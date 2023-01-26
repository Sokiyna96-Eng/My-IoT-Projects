// #include <Arduino.h>
// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>
// #include <ArduinoJson.h> // must be installed
// #include <ArduinoOTA.h>
// #include <SPI.h>
// #include <Encoder.h>
// #include <ESP8266mDNS.h>

// int LED = 4;
// int buzzer = 5; // 0 close - 1 open switch
// long rssi = WiFi.RSSI();
// long rssiValue = 50;

// // String url = "https://timeapi.io/api/Time/current/zone?timeZone=America/Los_Angeles";
// // String url1 = "https://sokiyna.000webhostapp.com/IoTmidTerm/insertion_db.php?";
// // DynamicJsonDocument doc(1024);

// const char *ssid = "DESKTOP-Suki";    // The SSID (name) of the Wi-Fi network you want to connect to
// const char *password = "ssu-suki123"; // The password of the Wi-Fi network

// void setup()
// {
//     Serial.begin(9600); // Start the Serial communication to send messages to the computer

//     WiFi.begin(ssid, password); // Connect to the network
//     Serial.print("Connecting to ");
//     Serial.print(ssid);

//     while (WiFi.status() != WL_CONNECTED)
//     { // Wait for the Wi-Fi to connect
//         delay(500);
//         digitalWrite(LED, LOW); // turn the LED off
//         Serial.print('.');
//     }

//     // if you are connected, print out info about the connection:

//     Serial.println('\n');
//     Serial.println("Connection established!");
//     Serial.print("IP address:\t");
//     Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer

//     // print the received signal strength:
//     Serial.print("RSSI:");
//     Serial.println(rssi);

//     pinMode(LED, OUTPUT);
//     pinMode(buzzer, OUTPUT);

//     delay(10);
//     Serial.println('\n');
// }

// // void userConnected()
// // {
// // }

// void loop()
// {

//     // ArduinoOTA.handle();
//     // delay(100);
//     // wifi is on turn the green led on
//     while (WiFi.status() == WL_CONNECTED)
//     {                            // Wait for the Wi-Fi to connect
//         digitalWrite(LED, HIGH); // turn the LED on
//         delay(1000);
//         // digitalWrite(LED, LOW); // turn the LED off
//         // delay(1000);
//     }

//     // if the rssi is less than -75 turn the buzzer on
//     if (rssi < rssiValue)
//     {
//         tone(buzzer, 1000);
//         delay(3000);

//         Serial.print("Buzzer working");
//         noTone(buzzer);
//     }
//     else
//     {
//         // wait for a second
//         noTone(buzzer);
//         Serial.print("buzzer is off");
//     }
// }
