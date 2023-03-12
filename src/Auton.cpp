
#include "main.h"
//pros::Motor flyw(5);
int None = 0;

int DRIVE_SPEED = 110;
int TURN_SPEED = 90;
void shootdisks(int disks){
    
    intake.moveVoltage(-12000);
        pros::delay(200);
    //intake.moveVoltage(12000);
        //pros::delay(200);
        intake.moveVoltage(0);
    pros::delay(1000);

    intake.moveVoltage(-12000);
        pros::delay(200);
        intake.moveVoltage(0);
    //intake.moveVoltage(12000);
    pros::delay(1000);
    intake.moveVoltage(-12000);
        pros::delay(300);
        intake.moveVoltage(0);
    
}

void fwd(double distance){
    chassis.set_drive_pid(distance, 110, false, true);
    chassis.wait_drive();
    
}
void slowfwd(double distance){
    chassis.set_drive_pid(distance, 25, false, true);
    chassis.wait_drive();
}

void turn(double angle){
    chassis.set_turn_pid(angle, 90);
    chassis.wait_drive();
}

void move_intake(bool mode){
    if(mode == false){
        intake.moveVoltage(-12000);
    } 
    if(mode == true){
        intake.moveVoltage(12000);
    }
}

void stop_intake(){
    intake.moveVoltage(0);
}

void rollers(){
    intake.moveVoltage(12000);
    
}

void delay(int time){
    pros::delay(time * 1000);
}

void run_flywheel(){
    while(true){
        flywheel::motor.moveVoltage(-12000);
        if(flywheel::motor.getActualVelocity() < 3600){
            flywheel::motor.moveVoltage(-12000);
        if(flywheel::motor.getActualVelocity() >= 3500){
            
        }
        }
        pros::delay(10);
    }
    pros::delay(10);
}
void swingleft(int turndis){
    chassis.set_swing_pid(ez::LEFT_SWING, turndis, 90);
    chassis.wait_drive();
}
void swingright(int turndis){
    chassis.set_swing_pid(ez::RIGHT_SWING, turndis, 90);
    chassis.wait_drive();
}

void shootdiskauton(){
    intake.moveVoltage(-12000);
    pros::delay(1000);
    intake.moveVoltage(0);
}
void AWP(){
    pros::Task flywheeltask(run_flywheel);
    
    



    fwd(-2);
    rollers();

    fwd(10);
    turn(45);
    //swingleft(45);
    
    stop_intake();
    fwd(28);
    intake.moveVelocity(12000);   //intake
    slowfwd(38);
    intake.moveVelocity(0);
    turn(-30);
    fwd(10);
    shootdisks(3);
    fwd(-10);



    turn(60);
    move_intake(true);
    



    //fwd(70);
    //turn(-133)
    //shoot(3)
    //fwd()
    /*
    //second part
    slowfwd(60);
    turn(-80);
    shootdisks(3);
    turn(-100);

    //turn to rollers and hit rollers
    fwd(-19);
    turn(45);
    fwd(-5);
    rollers();
    */
    
}

void rightauton(){
    flywheel::setTargetSpeed(1); //starts flywheel
    move_intake(true);//starts intake

    fwd(25); //go forward
    delay(0.01); //pick up disk
    turn(30);//turn right
    stop_intake();//stop the intake
    shootdisks(3);//shoot disks
    turn(10); //turn more to face disk at auton line
    //----
    move_intake(true);
    fwd(5);
    //delay for half a second to grab disk
    delay(0.1);
    //---
    fwd(-5); // go back 
    turn(-130); //turn left to intake disks
    slowfwd(60); //slowly go forward
    turn(80); //turn towards goal
    shootdisks(3); //shoot disks
    turn(-180); //turn facing rollers
    fwd(-80); // go backwards 
    rollers(); //hit rollers

    //exit
    leftDrive.moveVoltage(0); rightDrive.moveVoltage(0);







}

void leftauton(){
    
    profiler->setTarget(2_ft, true);
    
    //fwd(70);
    //turn(-133)
    //shoot(3)
    //fwd
}

void progskills(){
    /*
    fwd(-2);
    rollers();
    fwd(5);
    swingright(45); //edit
    //move_intake(true);
    fwd(20);//edit
    turn(200);
    fwd(-2);
    rollers();
    */
   //flywheel::motor.moveVoltage(-12000);
//chassis.set_angle(0);


chassis.set_drive_pid(-2, DRIVE_SPEED, false, true);
chassis.wait_drive();
flywheel::motor.moveVoltage(-12000);
intake.moveVoltage(12000);
pros::delay(300);

/*
chassis.set_drive_pid(33, 127, false, true);
chassis.wait_drive();
intake.moveVoltage(12000);

chassis.set_turn_pid(90, TURN_SPEED);
chassis.wait_drive();

chassis.set_drive_pid(-40, 127, false, true);
chassis.wait_drive();

pros::delay(200);
*/
chassis.set_drive_pid(5, DRIVE_SPEED, false, true);
chassis.wait_drive();
chassis.set_turn_pid(-45, TURN_SPEED);
chassis.wait_drive();
intake.moveVoltage(12000);
chassis.set_drive_pid(35, DRIVE_SPEED, false, true);
chassis.wait_drive();
chassis.set_turn_pid(90, TURN_SPEED);
chassis.wait_drive();
chassis.set_drive_pid(-15, DRIVE_SPEED);
chassis.wait_drive();
intake.moveVoltage(12000);
pros::delay(200);
intake.moveVoltage(0);
//chassis.set_swing_pid(ez::RIGHT_SWING, 0, 90);
chassis.set_drive_pid(10, TURN_SPEED);
chassis.wait_drive();

chassis.set_turn_pid(0, TURN_SPEED);
chassis.wait_drive();

intake.moveVoltage(0);
chassis.set_drive_pid(50, DRIVE_SPEED, false, true);
chassis.wait_drive();
chassis.set_turn_pid(8, 90);
chassis.wait_drive();
intake.moveVoltage(-12000);
pros::delay(800);
intake.moveVoltage(0);

chassis.set_drive_pid(-45, 127, false, true);
chassis.wait_drive();

intake.moveVoltage(12000);
chassis.set_turn_pid(45, 110);
chassis.wait_drive();

chassis.set_drive_pid(80, 90);
chassis.wait_drive();

pros::delay(1000);

intake.moveVoltage(0);

chassis.set_turn_pid(-45, 127);
chassis.wait_drive();

chassis.set_drive_pid(10, 127);
chassis.wait_drive();

intake.moveVoltage(-12000);
pros::delay(800);
intake.moveVoltage(0);

chassis.set_turn_pid(45, 127);
chassis.wait_drive();

chassis.set_drive_pid(34, 127);
chassis.wait_drive();
intake.moveVoltage(12000);

chassis.set_drive_pid(20, 40);
chassis.wait_drive();

chassis.set_turn_pid(-90, 90);
chassis.wait_drive();

chassis.set_drive_pid(30, 127);
chassis.wait_drive();











}

void set_pid(){
    chassis.set_drive_pid(18, 110);
}