#include "Drive.hpp"
#include "globals.cpp"

void turnToAngle(QAngle targetAngle){
    turnPID->reset();
    turnPID->setTarget(0);

    do {
        chassis->getModel()->tank(0, turnPID->step(-Math::rescale180(targetAngle.convert(degree)-imu.get())));
        pros::delay(10);
    } while(!turnPID->isSettled());

    (chassis->getModel())->stop();
}