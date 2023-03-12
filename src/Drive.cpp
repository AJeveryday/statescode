#include "Drive.hpp"


void turnToAngle(QAngle targetAngle){
    turnPID->reset();
    turnPID->setTarget(0);

    do {
        rchassis->getModel()->tank(0, turnPID->step(-Math::rescale180(targetAngle.convert(degree)-imu.get())));
        pros::delay(10);
    } while(!turnPID->isSettled());

    (rchassis->getModel())->stop();
}