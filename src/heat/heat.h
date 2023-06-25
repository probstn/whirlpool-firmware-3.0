// heat.h
#ifndef HEAT_H
#define HEAT_H

#include <Arduino.h>
#include <vector>
#include "heat_listener.h"
#include "./mqtt/mqtt_listener.h"

class Heat {
private:
    int pin;
    String mqtt_topic;
    std::vector<HeatListener*> listeners;
    bool isOn = false;
    void fireChangeEvent(bool isOn);

public:

    Heat(int PIN, String mqtt_topic);

    void addListener(HeatListener* listener);
    void removeListener(HeatListener* listener);
    void turnOn();
    void turnOff();
    bool getIsOn();
    void onMqttEvent(String topic, String message);
};

#endif // HEAT_H
