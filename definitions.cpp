#include "main.h"

Motor frontRight(17);
Motor frontLeft(18); //-
Motor backRight(20);
Motor backLeft(19);// -

pros::Motor driveLeftFront(18, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftBack(19, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightFront(17, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightBack(20, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);

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
ControllerButton calibrater(ControllerDigital::B);

ControllerButton autontester(ControllerDigital::A);
