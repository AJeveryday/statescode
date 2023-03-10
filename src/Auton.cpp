
#include "main.h"


void shootdisks(int disks){
    for(int i; i< disks+1 ; i++){
        intake.moveVoltage(-12000);
        pros::delay(150);
        intake.moveVoltage(0);
    }
    //delay for 10 mills for shooting---
    pros::delay(10);
}

void fwd(double distance){
    robotchassis.set_drive_pid(distance, 110, false, true);
    robotchassis.wait_drive();
    
}
void slowfwd(double distance){
    robotchassis.set_drive_pid(distance, 80, false, true);
    robotchassis.wait_drive();
}

void turn(double angle){
    robotchassis.set_turn_pid(angle, 90);
    robotchassis.wait_drive();
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
    intake.moveVoltage(-12000);
    pros::delay(150);
    intake.moveVoltage(0);
}
void AWP(){
    rollers();
    flywheel::setTargetSpeed(1);
    fwd(10);
    shootdisks(3);
    fwd(-3);
    turn(45);
    move_intake(true);
    //first part
    fwd(24);
    pros::delay(10);
    fwd(10);
    turn(-80);
    shootdisks(3);
    turn(80);
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
    
}

void rightauton(){
    flywheel::setTargetSpeed(1); //starts flywheel
    move_intake(true);//starts intake

    fwd(25); //go forward
    pros::delay(10); //pick up disk
    turn(30);//turn right
    stop_intake();//stop the intake
    shootdisks(3);//shoot disks
    turn(10); //turn more to face disk at auton line
    //----
    move_intake(true);
    fwd(5);
    //delay for half a second to grab disk
    pros::delay(100);
    //---
    fwd(-5); // go back 
    turn(-130); //turn left to intake disks
    slowfwd(60); //slowly go forward
    turn(80); //turn towards goal
    shootdisks(3); //shoot disks
    turn(-180); //turn facing rollers
    fwd(-80); // go backwards 
    rollers();

    //exit
    leftDrive.moveVoltage(0); rightDrive.moveVoltage(0);







}

void leftauton(){
    
    rollers();
    flywheel::setTargetSpeed(1);
    fwd(10);
    shootdisks(3);
    fwd(-3);
    turn(45);
    move_intake(true);
    //first part
    fwd(24);
    pros::delay(10);
    fwd(10);
    turn(-80);
    shootdisks(3);
    turn(80);
}