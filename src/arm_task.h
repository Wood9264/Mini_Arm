#pragma once
#include <Arduino.h>

const uint16_t ARM_TASK_DELAY = 1000;

class armTask_t
{
private:
    void initPeripheral();

public:
    armTask_t();

    void run(void *pvParameters);

    static void runTask(void *pvParameters);
};

extern armTask_t armTaskInstance;
