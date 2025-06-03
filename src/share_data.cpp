#include "share_data.h"

JoystickData_t joystickData;
SemaphoreHandle_t joystickDataMutex = xSemaphoreCreateMutex();

void updateJoystickData(const XboxControllerNotificationParser &xboxNotif)
{
    if (xSemaphoreTake(joystickDataMutex, portMAX_DELAY) == pdTRUE)
    {
        joystickData.btnA = xboxNotif.btnA;
        joystickData.btnB = xboxNotif.btnB;
        joystickData.btnX = xboxNotif.btnX;
        joystickData.btnY = xboxNotif.btnY;
        joystickData.btnShare = xboxNotif.btnShare;
        joystickData.btnStart = xboxNotif.btnStart;
        joystickData.btnSelect = xboxNotif.btnSelect;
        joystickData.btnXbox = xboxNotif.btnXbox;
        joystickData.btnLB = xboxNotif.btnLB;
        joystickData.btnRB = xboxNotif.btnRB;
        joystickData.btnLS = xboxNotif.btnLS;
        joystickData.btnRS = xboxNotif.btnRS;
        joystickData.btnDirUp = xboxNotif.btnDirUp;
        joystickData.btnDirLeft = xboxNotif.btnDirLeft;
        joystickData.btnDirRight = xboxNotif.btnDirRight;
        joystickData.btnDirDown = xboxNotif.btnDirDown;

        joystickData.joyLHori = xboxNotif.joyLHori;
        joystickData.joyLVert = xboxNotif.joyLVert;
        joystickData.joyRHori = xboxNotif.joyRHori;
        joystickData.joyRVert = xboxNotif.joyRVert;

        joystickData.trigLT = xboxNotif.trigLT;
        joystickData.trigRT = xboxNotif.trigRT;

        xSemaphoreGive(joystickDataMutex);
    }
}

JoystickData_t getJoystickData()
{
    JoystickData_t data;
    if (xSemaphoreTake(joystickDataMutex, portMAX_DELAY) == pdTRUE)
    {
        data = joystickData;
        xSemaphoreGive(joystickDataMutex);
    }
    return data;
}
