#include "arm_task.h"

armTask_t armTaskInstance;

armTask_t::armTask_t()
{
    joint1 = StepperJoint_t(JOINT1_INIT_ANGLE, JOINT1_MIN_ANGLE, JOINT1_MAX_ANGLE);
    joint2 = DoubleServoJoint_t(JOINT2_INIT_ANGLE, JOINT2_MIN_ANGLE, JOINT2_MAX_ANGLE, JOINT2_POSITIVE_ZERO_ANGLE, JOINT2_NEGATIVE_ZERO_ANGLE);
    joint3 = SingleServoJoint_t(JOINT3_INIT_ANGLE, JOINT3_MIN_ANGLE, JOINT3_MAX_ANGLE, JOINT3_ZERO_ANGLE);
    joint4 = SingleServoJoint_t(JOINT4_INIT_ANGLE, JOINT4_MIN_ANGLE, JOINT4_MAX_ANGLE, JOINT4_ZERO_ANGLE);
    joint5 = SingleServoJoint_t(JOINT5_INIT_ANGLE, JOINT5_MIN_ANGLE, JOINT5_MAX_ANGLE, JOINT5_ZERO_ANGLE);
    tool = ServoTool_t(TOOL_INIT_ANGLE, TOOL_MIN_ANGLE, TOOL_MAX_ANGLE, TOOL_ZERO_ANGLE);

    // 初始化机械臂状态为无力模式
    armState = ARM_STATE_ZERO_FORCE;
}

/**
 * @brief 初始化机械臂任务的外设
 */
void armTask_t::initPeripheral()
{
    // 在0核上初始化步进电机
    joint1.engine.init(0);
    joint1.stepper = joint1.engine.stepperConnectToPin(JOINT1_STEPPER_STEP_PIN);
    joint1.stepper->setDirectionPin(JOINT1_STEPPER_DIR_PIN);
    joint1.stepper->setEnablePin(JOINT1_STEPPER_ENABLE_PIN);
    joint1.stepper->setAutoEnable(false);
    joint1.stepper->setSpeedInHz(JOINT1_STEPPER_MAX_SPEED / 60.0f * STEPPER_STEPS_PER_REVOLUTION * STEPPER_MICROSTEPS * STEPPER_GEAR_RATIO);
    joint1.stepper->setAcceleration(JOINT1_STEPPER_ACCELERATION / 60.0f * STEPPER_STEPS_PER_REVOLUTION * STEPPER_MICROSTEPS * STEPPER_GEAR_RATIO);

    joint2.positiveServo.setPeriodHertz(50);
    joint2.positiveServo.attach(JOINT2_POSITIVE_SERVO_PIN, SERVO_MIN_PULSE_WIDTH, SERVO_MAX_PULSE_WIDTH);
    joint2.negativeServo.setPeriodHertz(50);
    joint2.negativeServo.attach(JOINT2_NEGATIVE_SERVO_PIN, SERVO_MIN_PULSE_WIDTH, SERVO_MAX_PULSE_WIDTH);
    joint3.servo.setPeriodHertz(50);
    joint3.servo.attach(JOINT3_SERVO_PIN, SERVO_MIN_PULSE_WIDTH, SERVO_MAX_PULSE_WIDTH);
    joint4.servo.setPeriodHertz(50);
    joint4.servo.attach(JOINT4_SERVO_PIN, SERVO_MIN_PULSE_WIDTH, SERVO_MAX_PULSE_WIDTH);
    joint5.servo.setPeriodHertz(50);
    joint5.servo.attach(JOINT5_SERVO_PIN, SERVO_MIN_PULSE_WIDTH, SERVO_MAX_PULSE_WIDTH);
    tool.servo.setPeriodHertz(50);
    tool.servo.attach(TOOL_SERVO_PIN, SERVO_MIN_PULSE_WIDTH, SERVO_MAX_PULSE_WIDTH);

    Serial.println("ARM Task peripherals initialized");
}

void armTask_t::run(void *pvParameters)
{
    initPeripheral();

    while (true)
    {
        Serial.println("ARM Task is running");
        updateData();
        control();
        vTaskDelay(ARM_TASK_DELAY);
    }
}

void armTask_t::runTask(void *pvParameters)
{
    armTaskInstance.run(pvParameters);
}

/**
 * @brief 更新机械臂任务的数据
 */
void armTask_t::updateData()
{
    JoystickData_t joystickData = getJoystickData();

    // X键无力模式，Y键初始化
    if (joystickData.btnX)
    {
        armState = ARM_STATE_ZERO_FORCE;
    }
    else if (joystickData.btnY)
    {
        if (armState == ARM_STATE_ZERO_FORCE)
        {
            armState = ARM_STATE_INITIALIZE;
        }
    }
}

/**
 * @brief 控制机械臂
 */
void armTask_t::control()
{
    switch (armState)
    {
    case ARM_STATE_ZERO_FORCE:
        zeroForceControl();
        break;
    case ARM_STATE_INITIALIZE:
        initializeControl();
        break;
    case ARM_STATE_RUN:
        runControl();
        break;
    default:
        break;
    }
}

/**
 * @brief 无力模式控制
 *        在此模式下，机械臂的所有关节都停止输出
 */
void armTask_t::zeroForceControl()
{
    Serial.println("Zero Force Control");

    joint1.stepper->disableOutputs();
    joint2.positiveServo.detach();
    joint2.negativeServo.detach();
    joint3.servo.detach();
    joint4.servo.detach();
    joint5.servo.detach();
    tool.servo.detach();
}

/**
 * @brief 初始化模式控制
 *        在此模式下，机械臂的所有关节都移动到初始位置，随后进入运行模式
 */
void armTask_t::initializeControl()
{
    Serial.println("Initialize Control");

    joint1.stepper->enableOutputs();

    joint2.positiveServo.setPeriodHertz(50);
    joint2.positiveServo.attach(JOINT2_POSITIVE_SERVO_PIN, SERVO_MIN_PULSE_WIDTH, SERVO_MAX_PULSE_WIDTH);
    joint2.negativeServo.setPeriodHertz(50);
    joint2.negativeServo.attach(JOINT2_NEGATIVE_SERVO_PIN, SERVO_MIN_PULSE_WIDTH, SERVO_MAX_PULSE_WIDTH);
    joint3.servo.setPeriodHertz(50);
    joint3.servo.attach(JOINT3_SERVO_PIN, SERVO_MIN_PULSE_WIDTH, SERVO_MAX_PULSE_WIDTH);
    joint4.servo.setPeriodHertz(50);
    joint4.servo.attach(JOINT4_SERVO_PIN, SERVO_MIN_PULSE_WIDTH, SERVO_MAX_PULSE_WIDTH);
    joint5.servo.setPeriodHertz(50);
    joint5.servo.attach(JOINT5_SERVO_PIN, SERVO_MIN_PULSE_WIDTH, SERVO_MAX_PULSE_WIDTH);
    tool.servo.setPeriodHertz(50);
    tool.servo.attach(TOOL_SERVO_PIN, SERVO_MIN_PULSE_WIDTH, SERVO_MAX_PULSE_WIDTH);

    joint1.targetAngle = JOINT1_INIT_ANGLE;
    joint2.targetAngle = JOINT2_INIT_ANGLE;
    joint3.targetAngle = JOINT3_INIT_ANGLE;
    joint4.targetAngle = JOINT4_INIT_ANGLE;
    joint5.targetAngle = JOINT5_INIT_ANGLE;
    tool.targetAngle = TOOL_INIT_ANGLE;

    // 限制关节角度
    joint1.targetAngle = constrain(joint1.targetAngle, joint1.minAngle, joint1.maxAngle);
    joint2.targetAngle = constrain(joint2.targetAngle, joint2.minAngle, joint2.maxAngle);
    joint3.targetAngle = constrain(joint3.targetAngle, joint3.minAngle, joint3.maxAngle);
    joint4.targetAngle = constrain(joint4.targetAngle, joint4.minAngle, joint4.maxAngle);
    joint5.targetAngle = constrain(joint5.targetAngle, joint5.minAngle, joint5.maxAngle);
    tool.targetAngle = constrain(tool.targetAngle, tool.minAngle, tool.maxAngle);

    // 依次移动到目标角度
    joint2.moveToTarget();
    delay(1000);
    joint3.moveToTarget();
    delay(1000);
    joint4.moveToTarget();
    delay(1000);
    joint5.moveToTarget();
    tool.moveToTarget();
    armState = ARM_STATE_RUN;
}

/**
 * @brief 运行模式控制
 *        在此模式下，机械臂的所有关节根据摇杆输入进行控制
 */
void armTask_t::runControl()
{
    Serial.println("Run Control");

    JoystickData_t joystickData = getJoystickData();

    joint1.targetAngle += (APPLY_DEADZONE(joystickData.joyLHori) - JOYSTICK_MIDDLE_VALUE) * JOINT1_DIRECTION * JOINT1_JOYSTICK_ANGLE_STEP;
    joint2.targetAngle += (APPLY_DEADZONE(joystickData.joyLVert) - JOYSTICK_MIDDLE_VALUE) * JOINT2_DIRECTION * JOINT2_JOYSTICK_ANGLE_STEP;
    joint3.targetAngle += (APPLY_DEADZONE(joystickData.joyRHori) - JOYSTICK_MIDDLE_VALUE) * JOINT3_DIRECTION * JOINT3_JOYSTICK_ANGLE_STEP;
    joint4.targetAngle += (APPLY_DEADZONE(joystickData.joyRVert) - JOYSTICK_MIDDLE_VALUE) * JOINT4_DIRECTION * JOINT4_JOYSTICK_ANGLE_STEP;
    joint5.targetAngle += (joystickData.btnDirLeft - joystickData.btnDirRight) * JOINT5_DIRECTION * JOINT5_JOYSTICK_ANGLE_STEP;
    tool.targetAngle += (joystickData.trigLT - joystickData.trigRT) * TOOL_DIRECTION * TOOL_JOYSTICK_ANGLE_STEP;

    // 限制关节角度
    joint1.targetAngle = constrain(joint1.targetAngle, joint1.minAngle, joint1.maxAngle);
    joint2.targetAngle = constrain(joint2.targetAngle, joint2.minAngle, joint2.maxAngle);
    joint3.targetAngle = constrain(joint3.targetAngle, joint3.minAngle, joint3.maxAngle);
    joint4.targetAngle = constrain(joint4.targetAngle, joint4.minAngle, joint4.maxAngle);
    joint5.targetAngle = constrain(joint5.targetAngle, joint5.minAngle, joint5.maxAngle);
    tool.targetAngle = constrain(tool.targetAngle, tool.minAngle, tool.maxAngle);

    joint1.moveToTarget();
    joint2.moveToTarget();
    joint3.moveToTarget();
    joint4.moveToTarget();
    joint5.moveToTarget();
    tool.moveToTarget();
}
