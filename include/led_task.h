#pragma once
#include <Arduino.h>

const uint8_t LED_PIN = 2;

class LedTask_t
{
private:
    void initPeripheral();

public:
    LedTask_t();

    void run(void *pvParameters);

    static void runTask(void *pvParameters);
};

extern LedTask_t ledTaskInstance;
