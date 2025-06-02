#include "arm_task.h"

armTask_t armTaskInstance;

armTask_t::armTask_t()
{
    joint1 = StepperJoint_t(JOINT1_INIT_ANGLE, JOINT1_DIRECTION, JOINT1_MIN_ANGLE, JOINT1_MAX_ANGLE);
    joint2 = DoubleServoJoint_t(JOINT2_INIT_ANGLE, JOINT2_DIRECTION, JOINT2_MIN_ANGLE, JOINT2_MAX_ANGLE,
                                JOINT2_POSITIVE_ZERO_ANGLE, JOINT2_NEGATIVE_ZERO_ANGLE);
    joint3 = SingleServoJoint_t(JOINT3_INIT_ANGLE, JOINT3_DIRECTION, JOINT3_MIN_ANGLE, JOINT3_MAX_ANGLE, JOINT3_ZERO_ANGLE);
    joint4 = SingleServoJoint_t(JOINT4_INIT_ANGLE, JOINT4_DIRECTION, JOINT4_MIN_ANGLE, JOINT4_MAX_ANGLE, JOINT4_ZERO_ANGLE);
    joint5 = SingleServoJoint_t(JOINT5_INIT_ANGLE, JOINT5_DIRECTION, JOINT5_MIN_ANGLE, JOINT5_MAX_ANGLE, JOINT5_ZERO_ANGLE);
    tool = ServoTool_t(TOOL_INIT_ANGLE, TOOL_DIRECTION, TOOL_MIN_ANGLE, TOOL_MAX_ANGLE, TOOL_ZERO_ANGLE);
}

void armTask_t::initPeripheral()
{
    joint1.engine.init(0);
    joint1.stepper = joint1.engine.stepperConnectToPin(JOINT1_STEPPER_STEP_PIN);
    joint1.stepper->setDirectionPin(JOINT1_STEPPER_DIR_PIN);
    joint1.stepper->setEnablePin(JOINT1_STEPPER_ENABLE_PIN);
    joint1.stepper->setAutoEnable(false);
    joint1.stepper->setSpeedInHz(JOINT1_STEPPER_MAX_SPEED);
    joint1.stepper->setAcceleration(JOINT1_STEPPER_ACCELERATION);

    joint2.positiveServo.setPeriodHertz(50);
    joint2.positiveServo.attach(JOINT2_POSITIVE_SERVO_PIN, 500, 2500);
    joint2.negativeServo.setPeriodHertz(50);
    joint2.negativeServo.attach(JOINT2_NEGATIVE_SERVO_PIN, 500, 2500);
    joint3.servo.setPeriodHertz(50);
    joint3.servo.attach(JOINT3_SERVO_PIN, 500, 2500);
    joint4.servo.setPeriodHertz(50);
    joint4.servo.attach(JOINT4_SERVO_PIN, 500, 2500);
    joint5.servo.setPeriodHertz(50);
    joint5.servo.attach(JOINT5_SERVO_PIN, 500, 2500);
    tool.servo.setPeriodHertz(50);
    tool.servo.attach(TOOL_SERVO_PIN, 500, 2500);

    Serial.println("ARM Task peripherals initialized");
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
