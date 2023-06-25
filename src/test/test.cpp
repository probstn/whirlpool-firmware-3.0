#include "test.h"

Test::Test() {
    Serial.println("Test");
    eventQueue = xQueueCreate(10, sizeof(bool)); // Create a queue to hold event data
    xTaskCreatePinnedToCore(eventTask, "EventTask", 4096, this, 1, &taskHandle, 1); // Create the event handling task on core 1
}

void Test::onHeatEvent(bool isTurnedOn) {
    xQueueSend(eventQueue, &isTurnedOn, portMAX_DELAY); // Send the event data to the queue
}

void Test::eventTask(void* param) {
    Test* test = static_cast<Test*>(param); // Get the Test object from the task parameter

    while (true) {
        test->run(); // Run the event handling task function
        vTaskDelay(pdMS_TO_TICKS(100)); // Delay of 100 milliseconds
    }
}

void Test::run() {
    bool isTurnedOn;
    if (xQueueReceive(eventQueue, &isTurnedOn, 0) == pdTRUE) {
        // Event data received from the queue
        // Perform event handling logic here
        // You can access the value of `isTurnedOn`
        // and perform actions accordingly
        Serial.println("Event: " + String(isTurnedOn));
    }
}