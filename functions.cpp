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

void turnOver(int speed, char direction, double deg){
    do{
      // if(overCount > 0){
      //   speed = 50;
      // }
        double degrees = deg - inertialSensor.get_heading();
        if(degrees >= 0){
            frontRight.moveVelocity(-speed);
            backRight.moveVelocity(-speed);
            frontLeft.moveVelocity(speed);
            backLeft.moveVelocity(speed);
        }
        else if (degrees < 0){
            frontRight.moveVelocity(speed);
            backRight.moveVelocity(speed);
            frontLeft.moveVelocity(-speed);
            backLeft.moveVelocity(-speed);
        }
        printf("%d\n", degrees);
        // if(inertialSensor.get_heading() < deg - 5){
        //   overCount++;
        // }
    }while(inertialSensor.get_heading() > (deg + 5) || inertialSensor.get_heading() < (deg - 5));

}

void turn(int speed, char direction, double deg){

  if(direction == 'r'){
    while(inertialSensor.get_heading() > (deg + 30) || (inertialSensor.get_heading() < (deg - 30))){
      frontRight.moveVelocity(-speed);
      backRight.moveVelocity(-speed);
      frontLeft.moveVelocity(speed);
      backLeft.moveVelocity(speed);
    }
    frontRight.moveVelocity(0);
    backRight.moveVelocity(0);
    frontLeft.moveVelocity(0);
    backLeft.moveVelocity(0);
  }
  else if(direction == 'l'){
    while(inertialSensor.get_heading() > (deg + 30) || (inertialSensor.get_heading() < (deg - 30))){
      frontRight.moveVelocity(speed);
      backRight.moveVelocity(speed);
      frontLeft.moveVelocity(-speed);
      backLeft.moveVelocity(-speed);
    }
    frontRight.moveVelocity(0);
    backRight.moveVelocity(0);
    frontLeft.moveVelocity(0);
    backLeft.moveVelocity(0);
  }
}

void brake(char braketype){
  if(braketype = 'b'){
    frontRight.setBrakeMode(AbstractMotor::brakeMode::brake);
    frontLeft.setBrakeMode(AbstractMotor::brakeMode::brake);
    backRight.setBrakeMode(AbstractMotor::brakeMode::brake);
    backLeft.setBrakeMode(AbstractMotor::brakeMode::brake);
  }
  else if(braketype = 'h'){
    frontRight.setBrakeMode(AbstractMotor::brakeMode::hold);
    frontLeft.setBrakeMode(AbstractMotor::brakeMode::hold);
    backRight.setBrakeMode(AbstractMotor::brakeMode::hold);
    backLeft.setBrakeMode(AbstractMotor::brakeMode::hold);
  }
  else if(braketype = 'c'){
    frontRight.setBrakeMode(AbstractMotor::brakeMode::coast);
	  frontLeft.setBrakeMode(AbstractMotor::brakeMode::coast);
	  backRight.setBrakeMode(AbstractMotor::brakeMode::coast);
	  backLeft.setBrakeMode(AbstractMotor::brakeMode::coast);
}
}

void autontest(){
  if(autontester.isPressed()){
    autonomous();
  }
}
