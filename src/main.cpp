#include "main.h"


using namespace ryan;




/******************************************************************************/
/**                              Welcome to 5327X                            **/
/**                                                                          **/
/**                                    Wauw   								 **/
/******************************************************************************/




void disabled() {
    ez::as::auton_selector.add_autons(
    {
      Auton("left autonomous", leftauton),
	  Auton("right autonomous", rightauton),
	  Auton("solo_awp", AWP),
    });
}

void competition_initialize() {
    //ez::as::auton_selector.call_selected_auton();
}









void initialize() {

    /**
         * @brief Chassis Initialization
         *        
         */
    chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
	chassis.set_active_brake(0.2);					   // Sets the active brake kP. We recommend 0.1.
	chassis.set_curve_default(0, 0);	
    ez::as::initialize();
	ez::as::auton_selector.add_autons(
    {
      Auton("left autonomous", leftauton),
	  Auton("right autonomous", rightauton),
	  Auton("solo_awp", AWP),
    });
    chassis.imu_calibrate();
    default_constants(); 
    exit_condition_defaults(); 
    chassis.set_active_brake(0.2); // Sets the active brake kP. We recommend 0.1.
    

}














void autonomous() {
    chassis.reset_gyro();
  	chassis.reset_drive_sensor();
  	leftDrive.setBrakeMode(MotorGroup::brakeMode::hold);
    rightDrive.setBrakeMode(MotorGroup::brakeMode::hold);
    // Execute auton
    //ez::as::auton_selector.call_selected_auton();
    set_pid();
}

















void driverflywheel(){
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
            flywheel::setTargetSpeed(1);
        }
        if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
            flywheel::setTargetSpeed(0.6);
        }
}


void endgame(){
    pros::delay(60*1000);
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)){
            expansion1.toggle();
        }

        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
            expansion2.toggle();
        }
}


void opcontrol(){
	// Sets brake mode

	// Initializes subsystems


	// Initializes constants

    int intake01_mode = 0;
	flywheel::setTargetSpeed(0);
	int intake02_mode = 0;

    

    leftDrive.setBrakeMode(MotorGroup::brakeMode::hold);
    rightDrive.setBrakeMode(MotorGroup::brakeMode::hold);
    pros::delay(20);
    

	while(true){
        

        chassis.tank();
    
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
			//if (intake02_mode != 1)
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
            //runs endgame task(wait for 60 seconds before activating buttons for expansion)


		pros::delay(10);

        
	}
}