// main.cpp
#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "heat/heat.h"
#include "test/test.h"
#include "mqtt/mqtt.h"

#define MQTT_TOPIC "probst/outdoor/whirlpool/isHeating"

PubSubClient client;
WiFiClientSecure secureClient;

Heat heat(2, MQTT_TOPIC);
Mqtt mqtt(&client);


void setup() {
    Serial.begin(115200);
    heat.addListener(&mqtt);
}

void loop() {
    heat.turnOn();
    delay(1000);
    heat.turnOff();
    delay(1000);
}