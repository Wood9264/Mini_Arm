#include "led_task.h"

LedTask_t ledTaskInstance;

LedTask_t::LedTask_t()
{
}

void LedTask_t::initPeripheral()
{
    pinMode(LED_PIN, OUTPUT);
}

void LedTask_t::run(void *pvParameters)
{
    initPeripheral();

    while (true)
    {
        digitalWrite(LED_PIN, HIGH);
        delay(500);
        digitalWrite(LED_PIN, LOW);
        delay(500);
        Serial.println("LED Task is running");
    }
}

void LedTask_t::runTask(void *pvParameters)
{
    ledTaskInstance.run(pvParameters);
}
