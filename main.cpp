#include "main.h"

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

std::shared_ptr<ChassisController> chassis =
   ChassisControllerBuilder()
   .withMotors ({-18, -19}, //left motors
               {20, 17})  //right motors
.withDimensions(AbstractMotor::gearset::blue, {{1.85_in, 10.5_in}, imev5BlueTPR})
.build();

std::shared_ptr<AsyncMotionProfileController> profileController =
    AsyncMotionProfileControllerBuilder()
      .withLimits({
        2.0, //Maximum linear velocity in m/s
        2.0, //Maximum linear acceleration in m/s/s
        10.0 //Maximum linear jerk in m/s/s/s
      })
      .withOutput(chassis)
      .buildMotionProfileController();

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
	inertialSensor.reset();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	brake('h');
	turnOver(50, 'r', 180);
	// turn(300, 'r', 180);
	
	// brake('h');

	//  intakeLeft.moveVelocity(300);
	//  intakeRight.moveVelocity(300);
	//  pros::delay(500);
	//  intakeLeft.moveVelocity(0);
	//  intakeRight.moveVelocity(0);

	//  profileController->generatePath(
    // 	{{0_ft, 0_ft, 0_deg}, {3_ft, 0_ft, 0_deg}}, "moveOne");
    //  profileController->setTarget("moveOne");
    //  profileController->waitUntilSettled();

	//  turn(300, 'r', 67);

	//  intakeLeft.moveVelocity(600);
	//  intakeRight.moveVelocity(600);
	//  indexBottom.moveVelocity(600);
	//  indexTopTwo.moveVelocity(600);

	//  profileController->generatePath(
    // 	{{0_ft, 0_ft, 0_deg}, {1.4_ft, 0_ft, 0_deg}}, "moveTwo");
    //  profileController->setTarget("moveTwo");
	// 	pros::delay(900);
	// 	intakeLeft.moveVelocity(0);
	// 	intakeRight.moveVelocity(0);
    //  profileController->waitUntilSettled();

	//  pros::delay(750);

	//  brake('b');

	//  indexBottom.moveVelocity(0);
	//  indexTopTwo.moveVelocity(0);
	//  intakeLeft.moveVelocity(-600);
	//  intakeRight.moveVelocity(-600);

	//  profileController->generatePath(
	// 	{{0_ft, 0_ft, 0_deg}, {2_ft, 0_ft, 0_deg}}, "backOne");
	//  profileController->setTarget("backOne", true);
	//  profileController->waitUntilSettled();

	//  intakeLeft.moveVelocity(0);
	//  intakeRight.moveVelocity(0);

	//  brake('h');
	
	//  turn(300, 'r', 188);
	// //  turnOver(300, 'r', 190);

	//  brake('b');

	//  profileController->generatePath(
   	// 	 {{0_ft, 0_ft, 0_deg}, {8_ft, 0_ft, 0_deg}}, "moveThree");
	//  profileController->setTarget("moveThree");
	//  profileController->waitUntilSettled();
	
	//  turn(300, 'l', 135);

	//  profileController->generatePath(
    // 	{{0_ft, 0_ft, 0_deg}, {2.5_ft, 0_ft, 0_deg}}, "movefour");
    //  profileController->setTarget("movefour");
	//  	pros::delay(1100);
	//  	intakeLeft.moveVelocity(600);
	//  	intakeRight.moveVelocity(600);
    //  profileController->waitUntilSettled();
	 
	//  pros::delay(750);
	 
	//  indexBottom.moveVelocity(0);
	//  indexTopTwo.moveVelocity(0);
	//  intakeLeft.moveVelocity(-600);
	//  intakeRight.moveVelocity(-600);
	 
	//  profileController->generatePath(
    // 	{{0_ft, 0_ft, 0_deg}, {2_ft, 0_ft, 0_deg}}, "movefour");
    //  profileController->setTarget("movefour", true);
    //  profileController->waitUntilSettled();

	//  intakeLeft.moveVelocity(0);
	//  intakeRight.moveVelocity(0);
}

void opcontrol() {

	while (true) {
	 pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		             (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		             (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

	 frontRight.setBrakeMode(AbstractMotor::brakeMode::coast);
	 frontLeft.setBrakeMode(AbstractMotor::brakeMode::coast);
	 backRight.setBrakeMode(AbstractMotor::brakeMode::coast);
	 backLeft.setBrakeMode(AbstractMotor::brakeMode::coast);

	 chassis->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
								 controller.getAnalog(ControllerAnalog::rightX));

	 intake();
	 index();
	 autontest();

	 pros::delay(20);
	}
}
