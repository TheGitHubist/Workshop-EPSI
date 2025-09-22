#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Never gonna give you up";
const char* password = "n€verG0nnAl€tyoUd0wn";

// MQTT broker details
const char* mqttServer = "broker.emqx.io";
const int mqttPort = 1883;

const char* clientId = "VieGehtEsDirMeinFreund"; // Must be unique on the broker

// Topics
const char* publishTopic = "/DIP/esp8266";
const char* subscribeTopic = "/DIP/#";

WiFiClient espClient;
PubSubClient client(espClient);

void connectToWiFi() {
    Serial.print("Connecting to Wi-Fi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

// Function to connect to MQTT broker
void connectToMQTT() {
  client.setServer(mqttServer, mqttPort);
  Serial.print("Connecting to MQTT broker");
  while (!client.connected()) {
    if (client.connect(clientId)) {
      Serial.println("\nConnected to MQTT broker");
    } else {
      Serial.print(".");
    }
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");

  if (length == 0) {
    Serial.println("Empty message received. Ignoring.");
    return;
  }

  // Check for "Device is alive" message and ignore it
  if (strncmp((const char*)payload, "01111111110111111101110001110011011101", length) == 0) {
    Serial.println("Heartbeat message received. Ignoring.");
    return;
  }
}

void setup() {
  // put your setup code here, to run once:
  //int result = myFunction(2, 3);
}

void loop() {
  if (!client.connected()) {
    connectToMQTT();
  }
  client.loop();

  // Send heartbeat message every 30 seconds
  static unsigned long lastHeartbeat = 0;
  if (millis() - lastHeartbeat > 3600000) {
    client.publish(publishTopic, "01111111110111111101110001110011011101");
    lastHeartbeat = millis();
  }
}
