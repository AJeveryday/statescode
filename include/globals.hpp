#pragma once
#include "main.h"

#define LVGL_SCREEN_WIDTH 480
#define LVGL_SCREEN_HEIGHT 240

// CONSTANTS
const double DEADBAND = 0.0500;



// CONTROLLER
extern Controller master;


// MOTORS
extern MotorGroup leftDrive;
extern MotorGroup rightDrive;
extern Motor intake;

// SENSORS
extern IMU imu; 


// PNEUMATICS
extern Pneumatics expansion;
extern Pneumatics expansion_blocker;

// MOTION PROFILE CONSTANTS
extern ProfileConstraint moveLimit;
extern ProfileConstraint turnLimit;
extern FFVelocityController leftController;
extern FFVelocityController rightController;

// SUBSYSTEM CONTROLLERS
extern std::shared_ptr<ChassisController> chassis;
extern std::shared_ptr<AsyncMotionProfiler> profiler;

extern std::shared_ptr<IterativePosPIDController> turnPID;

/**
 * @brief Create a Blank Background using LVGL
 * 
 */
void createBlankBackground();