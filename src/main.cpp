#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "ciphertext.h"
#include "keygenerator.h"

// Device-specific connection credentials based on MAC address
String generateDeviceSSID() {
  uint8_t mac[6];
  WiFi.macAddress(mac);
  char ssid[13];
  sprintf(ssid, "ESP_%02X%02X%02X", mac[3], mac[4], mac[5]);
  return String(ssid);
}

String generateDevicePassword() {
  uint8_t mac[6];
  WiFi.macAddress(mac);
  char password[17];
  sprintf(password, "PW_%02X%02X%02X%02X%02X%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(password);
}

const char* ap_ssid = generateDeviceSSID().c_str();
const char* ap_password = generateDevicePassword().c_str();

// MQTT broker details
const char* mqttServer = "broker.emqx.io";
const int mqttPort = 1883;

const char* clientId = "VieGehtEsDirMeinFreund"; // Must be unique on the broker

// Topics
const char* publishTopic = "/DIP/esp8266";
const char* subscribeTopic = "/DIP/#";

WiFiClient espClient;
PubSubClient client(espClient);

void setupAccessPoint() {
    Serial.print("Setting up Access Point...");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ap_ssid, ap_password);

    Serial.println("\nAccess Point created");
    Serial.print("SSID: ");
    Serial.println(ap_ssid);
    Serial.print("Password: ");
    Serial.println(ap_password);
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
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
  Serial.begin(115200);
  setupAccessPoint();
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
