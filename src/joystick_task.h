#pragma once
#include <Arduino.h>
#include <XboxSeriesXControllerESP32_asukiaaa.hpp>
#include "share_data.h"

// 任务延时时间
const uint16_t JOYSTICK_TASK_DELAY = 1;

class JoystickTask_t
{
private:
    void initPeripheral();

public:
    XboxSeriesXControllerESP32_asukiaaa::Core xboxController;
    String xbox_string();

    JoystickTask_t();

    void run(void *pvParameters);

    static void runTask(void *pvParameters);
};

extern JoystickTask_t joystickTaskInstance;
