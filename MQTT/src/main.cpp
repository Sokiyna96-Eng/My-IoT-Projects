//-----------------------------
// Title: MQTT
//-----------------------------
// Program Details:
//-----------------------------
// Purpose: Conenct to broker.mqtt-dashboard.com, Publish and subscribe
// Dependencies: Make sure you have installed PubSubClient.h
// Compiler: PIO Version 1.72.0
// Atuhor: Originally an example called ESP8266-mqtt / slightly modified and cleaned up by Farid Farahmand
// OUTPUT: publishes 1,2,3,.... on outTopic every publishTimeInterval
// INPUT: Received value from the broker on inTopic
// SETUP: To see the published values go to http://www.hivemq.com/demos/websocket-client/
//        subscribe to inTopic and outTopic. You can also create an APP using MQTT Dash
// Versions:
//  v1: Nov-24-2022 - Cleaned up version
//-----------------------------

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>

// WiFi variables
const char *ssid = "DESKTOP-Suki";           // Enter your WiFi name
const char *password = "ssu-suki123"; // Enter WiFi password

// MQTT variables
const char *mqtt_server = "broker.mqttdashboard.com";
const char *publishTopic = "testtopic/temp/MQTT/iot";  // outTopic where ESP publishes
const char *subscribeTopic = "testtopic/temp/MQTT/iotlab"; // inTopic where ESP has subscribed to
#define publishTimeInterval 10000                          // in seconds

// Definitions
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
#define BUILTIN_LED 2 // built-in LED
#define BUTTON_PIN 16
int ledPin = 4;
char msg[MSG_BUFFER_SIZE];
int value = 0;
int ledStatus = 0;
int val;

WiFiClient espClient;
PubSubClient client(espClient); // define MQTTClient

void setup_wifi()
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to WIFI");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
//------------------------------------------

void callback(char *topic, byte *payload, int length)
{
  Serial.print("Message arrived ["); // Received the incoming message
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    val = (char)payload[i];
    Serial.print((char)payload[i]); // the received value is in (char)payload[i]
  }
  Serial.println();
  //  Switch on the LED if an 1 was received as first character
  //  add your code here
  if (val == 49)
  {
    Serial.println("LED IS ON");
    digitalWrite(ledPin, HIGH);
  }
  else if (val == 48)
  {
    Serial.println("LED IS OFF");
    digitalWrite(ledPin, LOW);
  }
}
//------------------------------------------

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      // ... and resubscribe
      client.subscribe(subscribeTopic);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
//------------------------------------------

void setup()
{
  pinMode(ledPin, OUTPUT); // Initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
//------------------------------------------
void loop()
{

  if (!client.connected())
  {
    reconnect(); // check for the latest value in inTopic
  }
  client.loop();

  // print out the value you read:
  // Publish to outTopic
  unsigned long now = millis();
  byte buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW)
  {
    int sensorValue = analogRead(A0);

    if (now - lastMsg > publishTimeInterval)
    {
      Serial.println("Button is pressed");
      lastMsg = now;
      value = sensorValue;
      snprintf(msg, MSG_BUFFER_SIZE, "Potentiometer Value: %d", value); // prints Number # 1, Number # 2, .....
      Serial.print("Publish message: ");
      Serial.println(msg);
      Serial.println(publishTopic);
      client.publish(publishTopic, msg);
    }
   client.setCallback(callback);
  }
}
