#include "main.h"

Motor frontRight(17);
Motor frontLeft(-18);
Motor backRight(20);
Motor backLeft(-19);

Motor indexBottom(14);
Motor indexTopTwo(13);
Motor intakeLeft(11);
Motor intakeRight(-12);

pros::Imu inertialSensor(16);

Controller controller;

ControllerButton indexOut(ControllerDigital::L2);
ControllerButton indexIn(ControllerDigital::L1);
ControllerButton intakeIn(ControllerDigital::R1);
ControllerButton intakeOut(ControllerDigital::R2);

ControllerButton autontester(ControllerDigital::A);
