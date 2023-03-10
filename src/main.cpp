#include "main.h"


using namespace ryan;




/******************************************************************************/
/**                              Welcome to 5327X                            **/
/**                                                                          **/
/**                                    Wauw   								 **/
/******************************************************************************/




void disabled() {}

void competition_initialize() {}









void initialize() {

    /**
         * @brief Chassis Initialization
         *        
         */

    ez::as::initialize();
	ez::as::auton_selector.add_autons(
    {
      Auton("left autonomous", leftauton),
	  Auton("right autonomous", rightauton),
	  Auton("solo_awp", AWP),
    });
    robotchassis.imu_calibrate();
    default_constants(); 
    exit_condition_defaults(); 
    robotchassis.set_active_brake(0.2); // Sets the active brake kP. We recommend 0.1.

    //flywheel task 
    pros::Task flywheelread(flywheel::voltageUpdate);
}














void autonomous() {

    // Execute auton
    ez::as::auton_selector.call_selected_auton();
}














void endgametask(){
    pros::delay(12000000000000);
    
}





void opcontrol(){
	// Sets brake mode
	leftDrive.setBrakeMode(AbstractMotor::brakeMode::coast);
	rightDrive.setBrakeMode(AbstractMotor::brakeMode::coast);

	// Initializes subsystems
	auto model = std::static_pointer_cast<ExpandedSkidSteerModel>(chassis->getModel());

	// Initializes constants

    int intake01_mode = 0;
	flywheel::setTargetSpeed(0);
	int intake02_mode = 0;



    
    pros::delay(20);


	while(true){
        

        model->tank(mastershi.getAnalog(ControllerAnalog::leftY), 
						mastershi.getAnalog(ControllerAnalog::rightX), 
						 0.05);
    
        /**
         * @brief Controls Flywheel speeds
         *        
         */
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
            flywheel::setTargetSpeed(1);
        }
        if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
            flywheel::setTargetSpeed(0.6);
        }
        
        /**
         * @brief Controls Intake
         *        
         */

        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
		{ // When R1 pressed,
			if (intake01_mode != 1)
			{								 			// If intake not running,
				intake.moveVoltage(12000); 			// Run intake
				intake01_mode = 1;
			}
			else {										// If intake already running,
				intake.moveVoltage(0); 				// Turn off intake motor
				intake01_mode = 0;
			}
		}

		// Outtake
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
		{ // When R1 pressed,
			if (intake02_mode != 1)
			{								 			// If intake not running,
				intake.moveVoltage(-12000); 			// Run intake
				intake02_mode = 1;
			}
			else {										// If intake already running,
				intake.moveVoltage(0); 				// Turn off intake motor
				intake02_mode = 0;
			}
		}

        /**
         * @brief Endgame
         *        
         */
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)){
            expansion1.toggle();
        }

        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
            expansion2.toggle();
        }
		pros::delay(10);

        
	}
}
