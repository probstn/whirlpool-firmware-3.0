// heat.cpp
#include "heat.h"

Heat::Heat(int PIN, String mqtt_topic) {
    this->pin = PIN;
    this->mqtt_topic = mqtt_topic;
    pinMode(this->pin, OUTPUT);
}

void Heat::turnOn() {
    isOn = true;
    digitalWrite(pin, HIGH);
    fireChangeEvent(true);
}

void Heat::turnOff() {
    isOn = false;
    digitalWrite(pin, LOW);
    fireChangeEvent(false);
}

bool Heat::getIsOn() {
    return isOn;
}

void Heat::addListener(HeatListener* listener) {
    // Add the listener to the vector
    listeners.push_back(listener);
}

void Heat::removeListener(HeatListener* listener) {
    // Find and remove the listener from the vector
    auto it = std::find(listeners.begin(), listeners.end(), listener);
    if (it != listeners.end()) {
        listeners.erase(it);
    }
}

void Heat::fireChangeEvent(bool isOn) {
    // Notify all listeners
    for (auto listener : listeners) {
        listener->onHeatEvent(isOn);
    }
}

void Heat::onMqttEvent(String topic, String message) {
    if (topic == mqtt_topic) {
        if (message == "true") {
            turnOn();
        } else if (message == "false") {
            turnOff();
        }
    }
}