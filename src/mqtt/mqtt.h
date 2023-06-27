#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <vector>
#include <WiFiClientSecure.h>
#include "./heat/heat_listener.h"
#include "mqtt_listener.h"

class Mqtt : public HeatListener
{
public:
    PubSubClient *client;
    WiFiClientSecure *wifiClient;

    Mqtt(PubSubClient *client);
    void onHeatEvent(bool isTurnedOn);
    void connect(String user, String pass, String server, int port);
    void addListener(MqttListener *listener);
    void removeListener(MqttListener *listener);

private:

    WiFiClientSecure *espClient;

    String user;
    String pass;

    String server;
    int port;

    struct topics
    {
        String isHeating;
        String isFiltering;
    } topics;

    std::vector<MqttListener *> listeners;
    void fireMessageEvent(String topic, String message);

    TaskHandle_t taskHandle;            // Handle for the event handling task
    QueueHandle_t eventQueue;           // Queue to pass event data
    static void eventTask(void *param); // Static task function for event handling
    void run();                         // Event handling task function
};

void callback(char *topic, byte *payload, unsigned int length);

#endif