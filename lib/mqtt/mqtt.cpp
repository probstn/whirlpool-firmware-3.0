#include <Arduino.h>
#include <PubSubClient.h>

#include "./heat/heat_listener.h"
#include <vector>

class Mqtt : HeatListener
{

public:
    std::vector<String> topics;
    PubSubClient client;

    Mqtt()
    {
        // Constructor
        // subscribe to topics
    }

    void addTopic(String topic);
    void removeTopic(String topic);
    void Mqtt::connect(String user, String pass, String server, int port);
    static void onMessage(char *topic, byte *payload, unsigned int length);
    void onHeatEvent(bool isTurnedOn);
};

void Mqtt::addTopic(String topic)
{
    topics.push_back(topic);
}

void Mqtt::removeTopic(String topic)
{
    topics.erase(std::remove(topics.begin(), topics.end(), topic), topics.end());
}

void Mqtt::connect(String user, String pass, String server, int port)
{
    client.setServer(server.c_str(), port);
    client.setCallback(Mqtt::onMessage); // callback function
    
    String clientId = "ESP32Client-"; // Create a random client ID
    clientId += String(random(0xffff), HEX);
    // Attempt to connect

    if (client.connect(clientId.c_str(), user.c_str(), pass.c_str()))
    {
        Serial.println("[MQTT] connected!");
        Serial.println("[MQTT] Subscribing to topic: " + String(ISHEATING_TOPIC) + " " + String(ISFILTERING_TOPIC) + "\n");
        client.subscribe(ISHEATING_TOPIC);
        client.subscribe(ISFILTERING_TOPIC);
    }
    else
    {
        Serial.print("[MQTT] failed, rc=");
        Serial.print(client.state() + "\n");
    }

    while (true)
    {

        if (!client.connected())
            break;
        client.loop();
    }
}

void Mqtt::onMessage(char *topic, byte *payload, unsigned int length)
{
    String incommingMessage = "";
    for (int i = 0; i < length; i++)
        incommingMessage += (char)payload[i];
    //--- check the incomming message
    Serial.println("[MQTT] Message arrived [" + String(topic) + "]: " + incommingMessage);
    if (strcmp(topic, ISHEATING_TOPIC) == 0)
    {
        if (incommingMessage == "true" || incommingMessage == "1")
            setisHeating(true);
        else
            setisHeating(false);
    }
    if (strcmp(topic, ISFILTERING_TOPIC) == 0)
    {
        if (incommingMessage == "true" || incommingMessage == "1")
            setisFiltering(true);
        else
            setisFiltering(false);
    }
}

void Mqtt::onHeatEvent(bool isTurnedOn)
{
    // Turn on/off heating
    // publish to topics
}