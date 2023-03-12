#include "main.h"
#include "subsystems/flywheel.hpp"

/**
         * @brief Controls Flywheel
         *        
         */

namespace flywheel{
    okapi::Motor motor(FLYWHEELPORT);

    auto flywheelread = okapi::DemaFilter(0.5,0.5);
    
    int targetSpeed;
    double actualSpeed = 0;
    int nextspeed;
    void voltageUpdate() {
        
        
            if (targetSpeed == 0)  {motor.moveVoltage(0); }
            actualSpeed = flywheelread.filter(motor.getActualVelocity());
            int currentVoltage = actualSpeed * (MAXIMUM_VOLTAGE/TECHNICAL_FLYWHEEL_RPM);
            int convertedTarget = targetSpeed * (MAXIMUM_VOLTAGE/TECHNICAL_FLYWHEEL_RPM);
            int error = (convertedTarget - currentVoltage) * 0.5;
            int finalVoltage = convertedTarget + error;
            motor.moveVoltage(-(finalVoltage));
            pros::delay(10);
        
        
    };

    void setTargetSpeed(double pwr) {
        targetSpeed = TECHNICAL_FLYWHEEL_RPM * pwr;
        voltageUpdate();
        if (targetSpeed > 0) brake(false);
        
    };
    void brake(bool mode) {
        if (mode == true && abs(actualSpeed) < 30) motor.setBrakeMode(okapi::Motor::brakeMode::brake);
        else motor.setBrakeMode(okapi::Motor::brakeMode::coast);
    };
}
