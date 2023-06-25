// main.cpp
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "heat/heat.h"
#include "test/test.h"
#include "heat/heat_listener.h"

Test test;
Heat heat(2);

void setup() {
    Serial.begin(115200);
    heat.addListener(&test);
}

void loop() {
    // Your main loop code here
    heat.turnOn();
    delay(1000);
    heat.turnOff();
    delay(1000);
}