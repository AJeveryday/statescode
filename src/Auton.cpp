#include "Auton.hpp"
#include "main.h"


void AWP(){
    
}

void rightauton(){
    
    profiler->setTarget(-2.5_ft, true);
    flywheel::setTargetSpeed(1);
    turnToAngle(90_deg);
    
    leftDrive.moveVoltage(0); rightDrive.moveVoltage(0);
}

void leftauton(){
    
    profiler->setTarget(-2.5_ft, true);
    
    
    leftDrive.moveVoltage(0); rightDrive.moveVoltage(0);
}