#pragma once
#include <Arduino.h>
#include <ESP32Servo.h>
#include <FastAccelStepper.h>
#include "share_data.h"

const uint16_t ARM_TASK_DELAY = 1000;

const int8_t JOINT_DIRECTION_POSITIVE = 1;  // 正向
const int8_t JOINT_DIRECTION_NEGATIVE = -1; // 反向

const uint16_t SERVO_MIN_PULSE_WIDTH = 500;  // 舵机最小脉宽
const uint16_t SERVO_MAX_PULSE_WIDTH = 2500; // 舵机最大脉宽

const uint8_t JOINT1_STEPPER_DIR_PIN = 5;           // 关节1步进电机方向引脚
const uint8_t JOINT1_STEPPER_STEP_PIN = 18;         // 关节1步进电机步进引脚
const uint8_t JOINT1_STEPPER_ENABLE_PIN = 19;       // 关节1步进电机使能引脚
const uint16_t JOINT1_STEPPER_MAX_SPEED = 3200;     // 关节1步进电机最大速度
const uint16_t JOINT1_STEPPER_ACCELERATION = 30000; // 关节1步进电机加速度

const uint8_t JOINT2_POSITIVE_SERVO_PIN = 19; // 关节2正向舵机引脚
const uint8_t JOINT2_NEGATIVE_SERVO_PIN = 18; // 关节2反向舵机引脚
const uint8_t JOINT3_SERVO_PIN = 5;           // 关节3舵机引脚
const uint8_t JOINT4_SERVO_PIN = 17;          // 关节4舵机引脚
const uint8_t JOINT5_SERVO_PIN = 16;          // 关节5舵机引脚
const uint8_t TOOL_SERVO_PIN = 4;             // 工具舵机引脚

const int16_t JOINT1_INIT_ANGLE = 0;                      // 关节1初始角度
const int8_t JOINT1_DIRECTION = JOINT_DIRECTION_POSITIVE; // 关节1方向
const int16_t JOINT1_MIN_ANGLE = -70;                     // 关节1最小角度
const int16_t JOINT1_MAX_ANGLE = 70;                      // 关节1最大角度

const int16_t JOINT2_INIT_ANGLE = 90;                     // 关节2初始角度
const int8_t JOINT2_DIRECTION = JOINT_DIRECTION_POSITIVE; // 关节2方向
const int16_t JOINT2_MIN_ANGLE = -90;                     // 关节2最小角度
const int16_t JOINT2_MAX_ANGLE = 90;                      // 关节2最大角度
const uint8_t JOINT2_POSITIVE_ZERO_ANGLE = 90;            // 关节2正向舵机零点角度
const uint8_t JOINT2_NEGATIVE_ZERO_ANGLE = 97;            // 关节2反向舵机零点角度

const int16_t JOINT3_INIT_ANGLE = 0;                      // 关节3初始角度
const int8_t JOINT3_DIRECTION = JOINT_DIRECTION_POSITIVE; // 关节3方向
const int16_t JOINT3_MIN_ANGLE = -90;                     // 关节3最小角度
const int16_t JOINT3_MAX_ANGLE = 90;                      // 关节3最大角度
const uint8_t JOINT3_ZERO_ANGLE = 90;                     // 关节3舵机零点角度

const int16_t JOINT4_INIT_ANGLE = 0;                      // 关节4初始角度
const int8_t JOINT4_DIRECTION = JOINT_DIRECTION_POSITIVE; // 关节4方向
const int16_t JOINT4_MIN_ANGLE = -90;                     // 关节4最小角度
const int16_t JOINT4_MAX_ANGLE = 90;                      // 关节4最大角度
const uint8_t JOINT4_ZERO_ANGLE = 90;                     // 关节4舵机零点角度

const int16_t JOINT5_INIT_ANGLE = 0;                      // 关节5初始角度
const int8_t JOINT5_DIRECTION = JOINT_DIRECTION_POSITIVE; // 关节5方向
const int16_t JOINT5_MIN_ANGLE = -90;                     // 关节5最小角度
const int16_t JOINT5_MAX_ANGLE = 90;                      // 关节5最大角度
const uint8_t JOINT5_ZERO_ANGLE = 90;                     // 关节5舵机零点角度

const int16_t TOOL_INIT_ANGLE = 0;                      // 工具初始角度
const int8_t TOOL_DIRECTION = JOINT_DIRECTION_POSITIVE; // 工具方向
const int16_t TOOL_MIN_ANGLE = -90;                     // 工具最小角度
const int16_t TOOL_MAX_ANGLE = 90;                      // 工具最大角度
const uint8_t TOOL_ZERO_ANGLE = 90;                     // 工具舵机零点角度

// 关节基类
class Joint_t
{
public:
    // 初始化角度
    int16_t initAngle;
    // 运动方向
    int8_t direction;
    // 最小角度
    int16_t minAngle;
    // 最大角度
    int16_t maxAngle;
    // 当前角度
    int16_t currentAngle;
    // 目标角度
    int16_t targetAngle;

    Joint_t() = default;
    virtual ~Joint_t() = default;
};

// 单舵机关节
class SingleServoJoint_t : public Joint_t
{
public:
    Servo servo;
    // 关节零点的舵机角度(0-180)
    uint8_t jointZeroAngle;

    SingleServoJoint_t() = default;
    SingleServoJoint_t(int16_t initAngle, int8_t direction, int16_t minAngle, int16_t maxAngle, uint8_t jointZeroAngle)
    {
        this->initAngle = initAngle;
        this->direction = direction;
        this->minAngle = minAngle;
        this->maxAngle = maxAngle;
        this->jointZeroAngle = jointZeroAngle;
        this->currentAngle = initAngle;
        this->targetAngle = initAngle;
    }
    void moveToTarget()
    {
        // 将目标角度转换为舵机角度
        int16_t servoAngle = jointZeroAngle + targetAngle * direction;
        servo.write(servoAngle);
    }
};

// 双舵机关节
class DoubleServoJoint_t : public Joint_t
{
public:
    // 正向舵机
    Servo positiveServo;
    // 反向舵机
    Servo negativeServo;
    // 正向舵机关节零点的舵机角度(0-180)
    uint8_t positiveJointZeroAngle;
    // 反向舵机关节零点的舵机角度(0-180)
    uint8_t negativeJointZeroAngle;

    DoubleServoJoint_t() = default;
    DoubleServoJoint_t(int16_t initAngle, int8_t direction, int16_t minAngle, int16_t maxAngle,
                       uint8_t positiveJointZeroAngle, uint8_t negativeJointZeroAngle)
    {
        this->initAngle = initAngle;
        this->direction = direction;
        this->minAngle = minAngle;
        this->maxAngle = maxAngle;
        this->positiveJointZeroAngle = positiveJointZeroAngle;
        this->negativeJointZeroAngle = negativeJointZeroAngle;
        this->currentAngle = initAngle;
        this->targetAngle = initAngle;
    }
    void moveToTarget()
    {
        // 将目标角度转换为正向舵机角度
        int16_t positiveServoAngle = positiveJointZeroAngle + targetAngle * direction;
        positiveServo.write(positiveServoAngle);

        // 将目标角度转换为反向舵机角度
        int16_t negativeServoAngle = negativeJointZeroAngle - targetAngle * direction;
        negativeServo.write(negativeServoAngle);
    }
};

// 步进电机关节
class StepperJoint_t : public Joint_t
{
public:
    FastAccelStepperEngine engine = FastAccelStepperEngine();
    FastAccelStepper *stepper = NULL;

    StepperJoint_t() = default;
    StepperJoint_t(int16_t initAngle, int8_t direction, int16_t minAngle, int16_t maxAngle)
    {
        this->initAngle = initAngle;
        this->direction = direction;
        this->minAngle = minAngle;
        this->maxAngle = maxAngle;
        this->currentAngle = initAngle;
        this->targetAngle = initAngle;
    }
};

// 舵机工具
class ServoTool_t : public Joint_t
{
public:
    Servo servo;
    // 工具零点的舵机角度(0-180)
    uint8_t jointZeroAngle;

    ServoTool_t() = default;
    ServoTool_t(int16_t initAngle, int8_t direction, int16_t minAngle, int16_t maxAngle, uint8_t jointZeroAngle)
    {
        this->initAngle = initAngle;
        this->direction = direction;
        this->minAngle = minAngle;
        this->maxAngle = maxAngle;
        this->jointZeroAngle = jointZeroAngle;
        this->currentAngle = initAngle;
        this->targetAngle = initAngle;
    }
    void moveToTarget()
    {
        // 将目标角度转换为舵机角度
        int16_t servoAngle = jointZeroAngle + targetAngle * direction;
        servo.write(servoAngle);
    }
};

class armTask_t
{
private:
    enum armState_t
    {
        ARM_STATE_ZERO_FORCE, // 无力模式
        ARM_STATE_INITIALIZE, // 初始化模式
        ARM_STATE_RUN,        // 运行模式
    };

    StepperJoint_t joint1;
    DoubleServoJoint_t joint2;
    SingleServoJoint_t joint3;
    SingleServoJoint_t joint4;
    SingleServoJoint_t joint5;
    ServoTool_t tool;

    armState_t armState = ARM_STATE_ZERO_FORCE; // 机械臂状态

    void initPeripheral();
    void updateData();
    void control();
    void zeroForceControl();
    void initializeControl();
    void runControl();

public:
    armTask_t();

    void run(void *pvParameters);

    static void runTask(void *pvParameters);
};

extern armTask_t armTaskInstance;
