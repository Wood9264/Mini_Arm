#include <Arduino.h>
#include "led_task.h"

void ledTask(void *pvParameters)
{
    ledTaskInit();

    while (true)
    {
        digitalWrite(LED_PIN, HIGH);
        delay(500); // Delay for 500 milliseconds
        digitalWrite(LED_PIN, LOW);
        delay(500); // Delay for 500 milliseconds
        Serial.println("LED Task is running");
        Serial.println(xPortGetCoreID()); // Print the core ID where this task is running
    }
}

void ledTaskInit()
{
    pinMode(LED_PIN, OUTPUT);
}
