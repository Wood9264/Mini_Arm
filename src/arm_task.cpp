#include "arm_task.h"

armTask_t armTaskInstance;

armTask_t::armTask_t()
{
}

void armTask_t::initPeripheral()
{
}

void armTask_t::run(void *pvParameters)
{
    initPeripheral();

    while (true)
    {
        Serial.println("ARM Task is running");
        Serial.println(xPortGetCoreID());
        vTaskDelay(ARM_TASK_DELAY);
    }
}

void armTask_t::runTask(void *pvParameters)
{
    armTaskInstance.run(pvParameters);
}

void armTask(void *pvParameters)
{
    // Task code goes here
    while (true)
    {
        Serial.println("ARM Task is running");
        Serial.println(xPortGetCoreID()); // Print the core ID where this task is running
        vTaskDelay(pdMS_TO_TICKS(1000));  // Delay for 1 second
    }
}
