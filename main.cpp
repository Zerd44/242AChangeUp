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
        1.0, //Maximum linear velocity in m/s
        2.0, //Maximum linear acceleration in m/s/s
        10.0 //Maximum linear jerk in m/s/s/s
      })
      .withOutput(chassis)
      .buildMotionProfileController();

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	frontRight.setBrakeMode(AbstractMotor::brakeMode::brake);
	 frontLeft.setBrakeMode(AbstractMotor::brakeMode::brake);
	 backRight.setBrakeMode(AbstractMotor::brakeMode::brake);
	 backLeft.setBrakeMode(AbstractMotor::brakeMode::brake);
	//  inertialSensor.reset();
	//  pros::delay(3000);
	// turn(300, 'r', 180);
	// pros::delay(1000);
	// overshoot('r', 180);

	profileController->generatePath(
       {{0_ft, 0_ft, 0_deg}, {2_ft, 0_ft, 0_deg}}, "moveOne");
     profileController->setTarget("moveOne");
     profileController->waitUntilSettled();
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
	turnTest();

		pros::delay(20);
	}
}
