#include "mqtt.h"

Mqtt::Mqtt(PubSubClient *client)
{
    this->client = client;
    Serial.println("Mqtt");
    eventQueue = xQueueCreate(10, sizeof(bool));                                        // Create a queue to hold event data
    xTaskCreatePinnedToCore(eventTask, "EventTaskMqtt", 4096, this, 1, &taskHandle, 1); // Create the event handling task on core 1
}

void Mqtt::onHeatEvent(bool isTurnedOn)
{
    xQueueSend(eventQueue, &isTurnedOn, portMAX_DELAY); // Send the event data to the queue
}

void Mqtt::eventTask(void *param)
{
    Mqtt *mqtt = static_cast<Mqtt *>(param); // Get the Test object from the task parameter

    while (true)
    {
        mqtt->run();
        mqtt->client->loop();
        vTaskDelay(pdMS_TO_TICKS(100)); // Delay of 100 milliseconds
    }
}

void Mqtt::run()
{
    bool isTurnedOn;
    if (xQueueReceive(eventQueue, &isTurnedOn, 0) == pdTRUE)
    {
        // Event data received from the queue
        // Perform event handling logic here
        // You can access the value of `isTurnedOn
        // and perform actions accordingly
        Serial.println("Mqtt Event from Heating: " + String(isTurnedOn));
    }
}

void Mqtt::connect(String user, String pass, String server, int port)
{
    client->setServer(server.c_str(), port);
    // client->setCallback(callback);
    client->setCallback([&](char *topic, byte *payload, unsigned int length){
        String incommingMessage = "";
        for (int i = 0; i < length; i++)
            incommingMessage += (char)payload[i];
        //--- check the incomming message
        Serial.println("[MQTT] Message arrived [" + String(topic) + "]: " + incommingMessage);
        // handle message
        fireMessageEvent(String(topic), incommingMessage);
    });

    while (!client->connected()) {

    }
        Serial.print("[MQTT] Attempting to connect...\n");
        String clientId = "ESP32Client-"; // Create a random client ID
        clientId += String(random(0xffff), HEX);
        // Attempt to connect

        if (client->connect(clientId.c_str(), user.c_str(), pass.c_str()))
        {
            Serial.println("[MQTT] connected!");
        }
        else
        {
            Serial.print("[MQTT] failed, rc=");
            Serial.print(client->state() + "\n");
        }

        while (true)
        {

            if (!client->connected())
                break;
            client->loop();
        }
}

void callback(char *topic, byte *payload, unsigned int length)
{
    String incommingMessage = "";
    for (int i = 0; i < length; i++)
        incommingMessage += (char)payload[i];
    //--- check the incomming message
    Serial.println("[MQTT] Message arrived [" + String(topic) + "]: " + incommingMessage);
    // handle message
    
}

void Mqtt::addListener(MqttListener *listener)
{
    // Add the listener to the vector
    listeners.push_back(listener);
}

void Mqtt::removeListener(MqttListener *listener)
{
    // Find and remove the listener from the vector
    auto it = std::find(listeners.begin(), listeners.end(), listener);
    if (it != listeners.end())
    {
        listeners.erase(it);
    }
}

void Mqtt::fireMessageEvent(String topic, String message)
{
    // Notify all listeners
    Serial.println("[MQTT] Fire message event");
    for (auto listener : listeners)
    {
        listener->onMqttEvent(topic, message);
    }
}