#include "main.h"

int overCount = 0;

void index(){
  if(indexIn.isPressed()){
    indexBottom.moveVelocity(600);
    indexTopTwo.moveVelocity(600);
  }
  else if (indexOut.isPressed()){
    indexBottom.moveVelocity(-600);
    indexTopTwo.moveVelocity(-600);
  }
  else if (!intakeIn.isPressed() || !intakeOut.isPressed()){
    indexBottom.moveVelocity(0);
    indexTopTwo.moveVelocity(0);
  }
}

void intake(){
  if(intakeIn.isPressed()){
    intakeLeft.moveVelocity(600);
    intakeRight.moveVelocity(600);
  }
  else if (intakeOut.isPressed()){
    intakeLeft.moveVelocity(-600);
    intakeRight.moveVelocity(-600);
  }
  else if (!indexIn.isPressed() || !indexOut.isPressed()){
    intakeLeft.moveVelocity(0);
    intakeRight.moveVelocity(0);
  }
}

// void turnOver(int speed, char direction, double deg){
//     do{
//         double degrees = deg - inertialSensor.get_heading();
//         if(degrees >= 0){
//             frontRight.moveVelocity(-speed);
//             backRight.moveVelocity(-speed);
//             frontLeft.moveVelocity(speed);
//             backLeft.moveVelocity(speed);
//         }
//         else if (degrees < 0){
//             frontRight.moveVelocity(speed);
//             backRight.moveVelocity(speed);
//             frontLeft.moveVelocity(-speed);
//             backLeft.moveVelocity(-speed);
//         }
//         printf("%d\n", degrees);
//     }while(inertialSensor.get_heading() > (deg + 5) || inertialSensor.get_heading() < (deg - 5));

// }

// void turn(int speed, char direction, double deg){

//   if(direction == 'r'){
//     while(inertialSensor.get_heading() > (deg + 30) || (inertialSensor.get_heading() < (deg - 30))){
//       frontRight.moveVelocity(-speed);
//       backRight.moveVelocity(-speed);
//       frontLeft.moveVelocity(speed);
//       backLeft.moveVelocity(speed);
//     }
//     frontRight.moveVelocity(0);
//     backRight.moveVelocity(0);
//     frontLeft.moveVelocity(0);
//     backLeft.moveVelocity(0);
//   }
//   else if(direction == 'l'){
//     while(inertialSensor.get_heading() > (deg + 30) || (inertialSensor.get_heading() < (deg - 30))){
//       frontRight.moveVelocity(speed);
//       backRight.moveVelocity(speed);
//       frontLeft.moveVelocity(-speed);
//       backLeft.moveVelocity(-speed);
//     }
//     frontRight.moveVelocity(0);
//     backRight.moveVelocity(0);
//     frontLeft.moveVelocity(0);
//     backLeft.moveVelocity(0);
//   }
// }

// void brake(char braketype){
//   if(braketype = 'b'){
//     frontRight.setBrakeMode(AbstractMotor::brakeMode::brake);
//     frontLeft.setBrakeMode(AbstractMotor::brakeMode::brake);
//     backRight.setBrakeMode(AbstractMotor::brakeMode::brake);
//     backLeft.setBrakeMode(AbstractMotor::brakeMode::brake);
//   }
//   else if(braketype = 'h'){
//     frontRight.setBrakeMode(AbstractMotor::brakeMode::hold);
//     frontLeft.setBrakeMode(AbstractMotor::brakeMode::hold);
//     backRight.setBrakeMode(AbstractMotor::brakeMode::hold);
//     backLeft.setBrakeMode(AbstractMotor::brakeMode::hold);
//   }
//   else if(braketype = 'c'){
//     frontRight.setBrakeMode(AbstractMotor::brakeMode::coast);
// 	  frontLeft.setBrakeMode(AbstractMotor::brakeMode::coast);
// 	  backRight.setBrakeMode(AbstractMotor::brakeMode::coast);
// 	  backLeft.setBrakeMode(AbstractMotor::brakeMode::coast);
// }
// }

void setDrive(int left, int right) {
  driveLeftFront = left;
  driveLeftBack = left;
  driveRightFront = right;
  driveRightBack = right;
}

void rotate(double angle, int number) {
  bool direction = fabs(angle - inertialSensor.get_heading()) / (angle - inertialSensor.get_heading()) == 1;

  // bool direction;
  // if(angle > 0){
  //   direction = false;
  // }
  // else{
  //   direction = true;
  // }
  // bool direction;
  double kP = 6;
  double kD = 45;
  double error;
  double prevError;
  double derivative;
  double output;
  double done = 0;

  while (done < 5) {
    prevError = angle - inertialSensor.get_heading();
    pros::delay(10);
    error = angle - inertialSensor.get_heading();
    derivative = error - prevError;
    output = direction ? fmin(85, error * kP + derivative * kD) : fmax(-85, error * kP + derivative * kD);
    if(number == 1 && done == 0){
      output = fabs(output);
    }
    else if (number == 2 && done == 0){
      output = -output;
    }
    setDrive(output, -output);
    if (fabs(error) < 2) {
      done += 1;
    }
  }
  setDrive(0, 0);
}

void autontest(){
  if(autontester.isPressed()){
    autonomous();
  }
}

void calibrate(){
  if(calibrater.isPressed()){
    inertialSensor.reset();
  }
}
