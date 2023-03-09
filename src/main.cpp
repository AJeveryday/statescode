#include "main.h"

void disabled() {}

void competition_initialize() {}

void initialize() {
	// LCD initialization
	pros::lcd::initialize();



	// IMU Initialization
	pros::lcd::set_text(2, "imu calibrating..............");
    std::cout << "imu calibrating.............." << std::endl;
	imu.calibrate();
    pros::delay(2000);
	pros::lcd::set_text(2, "imu calibrated");
    std::cout << "imu calibrated, initialization finished!!!\n" << std::endl;


    

    // Auton Initialization
    auto&& selector = AutonSelector::getInstance();
    selector.addRoute(AWP, "AWP");
    selector.addRoute(rightauton, "right auton");
}

void autonomous() {
    // Initialization
    leftDrive.setBrakeMode(AbstractMotor::brakeMode::brake);
    rightDrive.setBrakeMode(AbstractMotor::brakeMode::brake);
    

    // Execute auton
    AutonSelector::getInstance().execute();    
}
void endgametask(){
    pros::delay(12000000000000);
    master.rumble("-");
}

void opcontrol(){
	// Sets brake mode
	leftDrive.setBrakeMode(AbstractMotor::brakeMode::coast);
	rightDrive.setBrakeMode(AbstractMotor::brakeMode::coast);
    //endgame task
    pros::Task endgame();

	// Initializes subsystems
	auto model = std::static_pointer_cast<ExpandedSkidSteerModel>(chassis->getModel());

	// Initializes constants


	// Initializes brasin background
	createBlankBackground();
	//auto gif = std::make_unique<Gif>("/usd/gif/crab-rave.gif", lv_scr_act());
    bool setIntake = false;
    bool setOuttake = false;

    int time = 0;
	while(true){
        
        // Chassis control using curvature drives
		model->curvature(master.getAnalog(ControllerAnalog::leftY), 
						 master.getAnalog(ControllerAnalog::rightX), 
						 0.05);


        time += 1;
        /**
         * @brief Controls Intake and Outtake
         *        When R1 is pressed Intake, When R2 is pressed Outtake
         */
		if(master[ControllerDigital::R1].changedToPressed()){
            if(setIntake == false){
                intake.moveVoltage(12000);
                setIntake = true;
            }
            else{
                intake.moveVoltage(0);
            }
        }

        
        if(master[ControllerDigital::R2].changedToPressed()){
            if(setOuttake == false){
                intake.moveVoltage(-12000);
                setOuttake = true;
            }
            else{
                intake.moveVoltage(0);
            }
        }

        /**
         * @brief Controls Flywheel speeds
         *        When L1 is pressed{flywheel runs at max speed}, When L2 is pressed{flywheel runs at moderate speed}
         */

        if(master[ControllerDigital::L1].changedToPressed()){
            flywheel::setTargetSpeed(LONG_RANGE_POWER);
            flywheel::voltageUpdate();
        }

        
        if(master[ControllerDigital::L2].changedToPressed()){
            flywheel::setTargetSpeed(SHORT_RANGE_POWER);
            flywheel::voltageUpdate();
        }

        if(time >= 12000000000000){
            if(master[ControllerDigital::down].changedToPressed()){
                expansion.toggle();
                expansion_blocker.toggle();
        }
		pros::delay(10);
	}
}
}