#include <Arduino.h>
#include "joystick_task.h"

void joystickTask(void *pvParameters)
{
    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(100)); // Delay for 100 milliseconds
    }
}
