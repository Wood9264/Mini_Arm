#include "joystick_task.h"

JoystickTask_t joystickTaskInstance;

JoystickTask_t::JoystickTask_t()
{
    xboxController = XboxSeriesXControllerESP32_asukiaaa::Core("7d:c9:60:ff:0b:62");
}

void JoystickTask_t::initPeripheral()
{
    // 初始化 Xbox 控制器
    xboxController.begin();
}

void JoystickTask_t::run(void *pvParameters)
{
    initPeripheral();

    while (true)
    {
        xboxController.onLoop();
        if (xboxController.isConnected())
        {
            if (xboxController.isWaitingForFirstNotification())
            {
                Serial.println("waiting for first notification");
            }
            else
            {
                // Serial.print(xbox_string());
                // 更新共享数据
                updateJoystickData(xboxController.xboxNotif);
            }
        }
        else
        {
            Serial.println("not connected");
            if (xboxController.getCountFailedConnection() > 2)
            {
                ESP.restart();
            }
        }

        delay(JOYSTICK_TASK_DELAY);
    }
}

void JoystickTask_t::runTask(void *pvParameters)
{
    joystickTaskInstance.run(pvParameters);
}

String JoystickTask_t::xbox_string()
{
    String str = String(xboxController.xboxNotif.btnY) + "," +
                 String(xboxController.xboxNotif.btnX) + "," +
                 String(xboxController.xboxNotif.btnB) + "," +
                 String(xboxController.xboxNotif.btnA) + "," +
                 String(xboxController.xboxNotif.btnLB) + "," +
                 String(xboxController.xboxNotif.btnRB) + "," +
                 String(xboxController.xboxNotif.btnSelect) + "," +
                 String(xboxController.xboxNotif.btnStart) + "," +
                 String(xboxController.xboxNotif.btnXbox) + "," +
                 String(xboxController.xboxNotif.btnShare) + "," +
                 String(xboxController.xboxNotif.btnLS) + "," +
                 String(xboxController.xboxNotif.btnRS) + "," +
                 String(xboxController.xboxNotif.btnDirUp) + "," +
                 String(xboxController.xboxNotif.btnDirRight) + "," +
                 String(xboxController.xboxNotif.btnDirDown) + "," +
                 String(xboxController.xboxNotif.btnDirLeft) + "," +
                 String(xboxController.xboxNotif.joyLHori) + "," +
                 String(xboxController.xboxNotif.joyLVert) + "," +
                 String(xboxController.xboxNotif.joyRHori) + "," +
                 String(xboxController.xboxNotif.joyRVert) + "," +
                 String(xboxController.xboxNotif.trigLT) + "," +
                 String(xboxController.xboxNotif.trigRT) + "\n";
    return str;
};
