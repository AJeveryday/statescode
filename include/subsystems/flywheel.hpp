#include "main.h"

namespace flywheel {
    #define FLYWHEELPORT 5
    #define LONG_RANGE_POWER 0.8888888
    #define SHORT_RANGE_POWER 0.6666999
    #define MAXIMUM_VOLTAGE 12000
    #define TECHNICAL_FLYWHEEL_RPM 600

    extern okapi::Motor motor;

    extern int targetSpeed;
    extern double actualSpeed;

    void voltageUpdate();
    void setTargetSpeed(double pwr);
    void brake(bool mode);

}