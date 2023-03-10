#include "globals.hpp"
#include "main.h"
#include "EZ-Template/api.hpp"
using namespace ryan;

// CONTROLLERS
Controller mastershi(ControllerId::master);
pros::Controller master(pros::E_CONTROLLER_MASTER);

// MOTORS
Motor leftFront(18, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees); 
Motor leftMiddle(9, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees); 
Motor leftBack(11, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees); 
Motor rightFront(16, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees); 
Motor rightMiddle(13, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor rightBack(3, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees); 

Motor intake(12, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

MotorGroup leftDrive({leftFront, leftMiddle,leftBack});
MotorGroup rightDrive({rightFront, rightMiddle, rightBack});


// SENSORS
IMU imu(21);

// PNEUMATICS
Pneumatics expansion1('A'); 
Pneumatics expansion2('B'); 


// MOTION PROFILE CONSTANTS
ProfileConstraint moveLimit({3_ftps, 5_ftps2, 5_ftps2, 25_ftps3});
ProfileConstraint turnLimit({4.8_ftps, 17.5_ftps2, 17.5_ftps2, 25_ftps3});
FFVelocityController leftController(0.187, 0.04, 0.025, 4.35, 0.1); // TODO Tune for new chassis
FFVelocityController rightController(0.1915, 0.043, 0.02, 4, 0.1); // TODO Tune for new chassis

// SUBSYSTEM CONTROLLERS
std::shared_ptr<ChassisController> chassis = ChassisControllerBuilder()
    .withMotors(leftDrive, rightDrive)
    .withDimensions({AbstractMotor::gearset::green, 5.0/7.0}, {{3.25_in, 1.294_ft}, imev5BlueTPR})
    .build();

std::shared_ptr<AsyncMotionProfiler> profiler = AsyncMotionProfilerBuilder()
    .withOutput(chassis)
    .withProfiler(std::make_unique<SCurveMotionProfile>(moveLimit))
    .build();




std::shared_ptr<IterativePosPIDController> turnPID = std::make_shared<IterativePosPIDController>(0.037, 0.0, 0.00065, 0, TimeUtilFactory::withSettledUtilParams(2, 2, 100_ms));



extern Drive robotchassis{
    // Left Chassis Ports (negative port will reverse it!)
  {-11,-9,-18},

  // Right Chassis Ports (negative port will reverse it!)
  {1, 13, 16}

  // IMU Port
  ,21

  // Tracking Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  ,4.125

  // Ticks per Rotation of Encoder
  ,600

  // External Gear Ratio of Tracking Wheel (MUST BE DECIMAL)
  // eg. if your drive is 84:36 where the 36t is sensored, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is sensored, your RATIO would be 0.6.
  ,2.333
};



void default_constants()
{
  robotchassis.set_slew_min_power(80, 80);
  robotchassis.set_slew_distance(7, 7);
  robotchassis.set_pid_constants(&robotchassis.headingPID, 11, 0, 20, 0);
  robotchassis.set_pid_constants(&robotchassis.forward_drivePID, 0.45, 0, 5, 0);
  robotchassis.set_pid_constants(&robotchassis.backward_drivePID, 0.45, 0, 5, 0);
  robotchassis.set_pid_constants(&robotchassis.turnPID, 5, 0.003, 35, 15);
  robotchassis.set_pid_constants(&robotchassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults()
{
  robotchassis.set_exit_condition(robotchassis.turn_exit, 100, 3, 500, 7, 500, 500);
  robotchassis.set_exit_condition(robotchassis.swing_exit, 100, 3, 500, 7, 500, 500);
  robotchassis.set_exit_condition(robotchassis.drive_exit, 80, 50, 300, 150, 500, 200);
}

void modified_exit_condition()
{
  robotchassis.set_exit_condition(robotchassis.turn_exit, 100, 3, 500, 7, 500, 500);
  robotchassis.set_exit_condition(robotchassis.swing_exit, 100, 3, 500, 7, 500, 500);
  robotchassis.set_exit_condition(robotchassis.drive_exit, 80, 50, 300, 150, 500, 500);
}