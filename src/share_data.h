#pragma once
#include <Arduino.h>
#include <XboxControllerNotificationParser.h>

typedef struct
{
    bool btnA, btnB, btnX, btnY;
    bool btnShare, btnStart, btnSelect, btnXbox;
    bool btnLB, btnRB;
    bool btnLS, btnRS;
    bool btnDirUp, btnDirLeft, btnDirRight, btnDirDown;
    uint16_t joyLHori;
    uint16_t joyLVert;
    uint16_t joyRHori;
    uint16_t joyRVert;
    uint16_t trigLT, trigRT;
} JoystickData_t;

extern JoystickData_t joystickData;
extern SemaphoreHandle_t joystickDataMutex;
extern void updateJoystickData(const XboxControllerNotificationParser &xboxNotif);
extern JoystickData_t getJoystickData();
