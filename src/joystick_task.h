#pragma once
#include <Arduino.h>
#include <XboxSeriesXControllerESP32_asukiaaa.hpp>
#include "share_data.h"

// 任务延时时间
const uint16_t JOYSTICK_TASK_DELAY = 8;

// 摇杆中间值
const uint16_t JOYSTICK_MIDDLE_VALUE = 32767;
// 摇杆从初始位置开始的最大偏移值
const uint16_t JOYSTICK_MAX_OFFSET = 32767;
// 扳机从初始位置开始的最大偏移值
const uint16_t TRIGGER_MAX_OFFSET = 255;
// 按键最大偏移值
const uint16_t BUTTON_MAX_OFFSET = 1;

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
