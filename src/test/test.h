#ifndef TEST_H
#define TEST_H

#include <Arduino.h>
#include "./heat/heat_listener.h"

class Test : public HeatListener {
public:
    Test();
    void onHeatEvent(bool isTurnedOn);

private:
    TaskHandle_t taskHandle; // Handle for the event handling task
    QueueHandle_t eventQueue; // Queue to pass event data
    static void eventTask(void* param); // Static task function for event handling
    void run(); // Event handling task function
};

#endif