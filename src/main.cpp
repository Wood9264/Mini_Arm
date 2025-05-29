#include <Arduino.h>
#include "arm_task.h"
#include "led_task.h"

TaskHandle_t armTaskHandle;
TaskHandle_t ledTaskHandle;

void setup()
{
    Serial.begin(115200);

    xTaskCreatePinnedToCore(armTask, "ARM Task", 2048, NULL, 1, &armTaskHandle, 1);
    xTaskCreatePinnedToCore(ledTask, "LED Task", 1024, NULL, 1, &ledTaskHandle, 0);
}

void loop()
{
}
