#include <Arduino.h>


// heat_listener.h
#ifndef MQTT_LISTENER_H
#define MQTT_LISTENER_H

class MqttListener {
public:
  virtual void onMqttEvent(String topic, String message) = 0;
};

#endif  // HEAT_LISTENER_H
