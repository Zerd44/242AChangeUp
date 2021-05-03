#include "main.h"

// void master(){
//   if(indexIn.isPressed()){
//     indexBottom.moveVelocity(600);
//     indexTopTwo.moveVelocity(600);
//   }
//   else if (allOut.isPressed()){
//     indexBottom.moveVelocity(-600);
//     indexTopTwo.moveVelocity(-600);
// 		intakeLeft.moveVelocity(-600);
// 		intakeRight.moveVelocity(-600);
//   }
//   else if (intakeIn.isPressed()){
//     intakeLeft.moveVelocity(600);
//     intakeRight.moveVelocity(600);
//   }
//   else if (intakeOut.isPressed()){
//     intakeLeft.moveVelocity(-600);
//     intakeRight.moveVelocity(-600);
//   }
// 	else {
// 		indexBottom.moveVelocity(0);
// 		indexTopTwo.moveVelocity(0);
// 		intakeLeft.moveVelocity(0);
// 		intakeRight.moveVelocity(0);
// 	}
// }

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

void turn(int speed, char direction, int deg){
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
  else{

  }
}

void overshoot(char direction, int deg){
    while(inertialSensor.get_heading() > (deg + 5)){
      frontRight.moveVelocity(50);
      backRight.moveVelocity(50);
      frontLeft.moveVelocity(-50);
      backLeft.moveVelocity(-50);
  }
  frontRight.moveVelocity(0);
  backRight.moveVelocity(0);
  frontLeft.moveVelocity(0);
  backLeft.moveVelocity(0);
}

void turnTest(){
  if(turntester.isPressed()){
    turn(300, 'r', 90);
  }
}
