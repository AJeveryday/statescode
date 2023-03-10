#pragma once
#include "main.h"
#include "EZ-Template/api.hpp"


#define LVGL_SCREEN_WIDTH 480
#define LVGL_SCREEN_HEIGHT 240

// CONSTANTS
const double DEADBAND = 0.0500;



// CONTROLLER
extern Controller mastershi;
extern pros::Controller master;

// MOTORS
extern MotorGroup leftDrive;
extern MotorGroup rightDrive;
extern Motor intake;

// SENSORS
extern IMU imu; 


// PNEUMATICS
extern Pneumatics expansion1;
extern Pneumatics expansion2;

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


extern Drive robotchassis;
extern void default_constants();
extern void exit_condition_defaults();