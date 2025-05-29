#include <Arduino.h>

void armTask(void *pvParameters)
{
    // Task code goes here
    while (true)
    {
        Serial.println("ARM Task is running");
        Serial.println(xPortGetCoreID()); // Print the core ID where this task is running
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }
}
