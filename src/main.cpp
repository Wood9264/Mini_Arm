#include <Arduino.h>
#include "arm_task.h"
#include "led_task.h"
#include "joystick_task.h"

TaskHandle_t armTaskHandle;
TaskHandle_t ledTaskHandle;
TaskHandle_t joystickTaskHandle;

void setup()
{
    Serial.begin(115200);

    xTaskCreatePinnedToCore(armTaskInstance.runTask, "ARM Task", 2048, NULL, 1, &armTaskHandle, 1);
    // 因步进电机引脚占用了led引脚，停止led任务的运行
    // xTaskCreatePinnedToCore(ledTaskInstance.runTask, "LED Task", 1024, NULL, 1, &ledTaskHandle, 1);
    xTaskCreatePinnedToCore(joystickTaskInstance.runTask, "Joystick Task", 4096, NULL, 1, &joystickTaskHandle, 1);
}

void loop()
{
}
