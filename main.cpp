#include "main.h"

#define HUE 207
#define DEFAULT -3
#define AUTONS "One Goal", "Two Goal", "242 Special"

namespace selector{

const char *b[] = {AUTONS, ""};
int auton;
int autonCount;
const char *btnmMap[] = {"","","","","","","","","","",""}; // up to 10 autons

lv_obj_t *tabview;
lv_obj_t *redBtnm;
lv_obj_t *blueBtnm;

lv_res_t redBtnmAction(lv_obj_t *btnm, const char *txt){
	//printf("red button: %s released\n", txt);

	for(int i = 0; i < autonCount; i++){
		if(strcmp(txt, btnmMap[i]) == 0){
			auton = i+1;
		}
	}

	return LV_RES_OK; // return OK because the button matrix is not deleted
}

lv_res_t blueBtnmAction(lv_obj_t *btnm, const char *txt)
{
	//printf("blue button: %s released\n", txt);

	for(int i = 0; i < autonCount; i++){
		if(strcmp(txt, btnmMap[i]) == 0){
			auton = -(i+1);
		}
	}

	return LV_RES_OK; // return OK because the button matrix is not deleted
}

lv_res_t skillsBtnAction(lv_obj_t *btn){
  //printf("skills pressed");
	auton = 0;
	return LV_RES_OK;
}

int tabWatcher() {
	int activeTab = lv_tabview_get_tab_act(tabview);
	while(1){
		int currentTab = lv_tabview_get_tab_act(tabview);

		if(currentTab != activeTab){
			activeTab = currentTab;
			if(activeTab == 0){
				if(auton == 0) auton = 1;
				auton = abs(auton);
				lv_btnm_set_toggle(redBtnm, true, abs(auton)-1);
			}else if(activeTab == 1){
				if(auton == 0) auton = -1;
				auton = -abs(auton);
				lv_btnm_set_toggle(blueBtnm, true, abs(auton)-1);
			}else{
				auton = 0;
			}
		}

		pros::delay(20);
	}
}

void init(int hue, int default_auton, const char **autons){

	int i = 0;
	do{
		memcpy(&btnmMap[i], &autons[i], sizeof(&autons));
		i++;
	}while(strcmp(autons[i], "") != 0);

	autonCount = i;
	auton = default_auton;

	// lvgl theme
	lv_theme_t *th = lv_theme_alien_init(hue, NULL); //Set a HUE value and keep font default RED
	lv_theme_set_current(th);

	// create a tab view object
	tabview = lv_tabview_create(lv_scr_act(), NULL);

	// add 3 tabs (the tabs are page (lv_page) and can be scrolled
	lv_obj_t *redTab = lv_tabview_add_tab(tabview, "Left");
	lv_obj_t *blueTab = lv_tabview_add_tab(tabview, "Right");
	lv_obj_t *skillsTab = lv_tabview_add_tab(tabview, "Skills");

	//set default tab
	if(auton < 0){
		lv_tabview_set_tab_act(tabview, 1, LV_ANIM_NONE);
	}else if(auton == 0){
		lv_tabview_set_tab_act(tabview, 2, LV_ANIM_NONE);
	}

	// add content to the tabs
	// button matrix
	redBtnm = lv_btnm_create(redTab, NULL);
	lv_btnm_set_map(redBtnm, btnmMap);
	lv_btnm_set_action(redBtnm, redBtnmAction);
	lv_btnm_set_toggle(redBtnm, true, abs(auton)-1);//3
	lv_obj_set_size(redBtnm, 450, 50);
	lv_obj_set_pos(redBtnm, 0, 100);
	lv_obj_align(redBtnm, NULL, LV_ALIGN_CENTER, 0, 0);

	// blue tab
	blueBtnm = lv_btnm_create(blueTab, NULL);
	lv_btnm_set_map(blueBtnm, btnmMap);
	lv_btnm_set_action(blueBtnm, *blueBtnmAction);
	lv_btnm_set_toggle(blueBtnm, true, abs(auton)-1);
	lv_obj_set_size(blueBtnm, 450, 50);
	lv_obj_set_pos(blueBtnm, 0, 100);
	lv_obj_align(blueBtnm, NULL, LV_ALIGN_CENTER, 0, 0);

	// skills tab
	lv_obj_t *skillsBtn = lv_btn_create(skillsTab, NULL);
	lv_obj_t *label = lv_label_create(skillsBtn, NULL);
	lv_label_set_text(label, "Skills");
	lv_btn_set_action(skillsBtn, LV_BTN_ACTION_CLICK, *skillsBtnAction);
	// lv_btn_set_state(skillsBtn, LV_BTN_STATE_TGL_REL);
	lv_obj_set_size(skillsBtn, 450, 50);
	lv_obj_set_pos(skillsBtn, 0, 100);
	lv_obj_align(skillsBtn, NULL, LV_ALIGN_CENTER, 0, 0);

	// start tab watcher
	pros::Task tabWatcher_task(tabWatcher);

}

} // namespace selector

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
   .withMotors ({18, 19}, //left motors -
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
	selector::init(HUE, DEFAULT, selector::b);

	inertialSensor.reset();
	while (inertialSensor.is_calibrating()){
		pros::delay(10);
	}
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	
	//one goal left side
	if (selector::auton == 1){
	 profileController->generatePath(
    	{{0_ft, 0_ft, 0_deg}, {1_ft, 0_ft, 0_deg}}, "moveOne");
	 intakeLeft.moveVelocity(300);
	 intakeRight.moveVelocity(300);
     profileController->setTarget("moveOne");
     profileController->waitUntilSettled();

	 rotate(315, 0);

	 profileController->generatePath(
    	{{0_ft, 0_ft, 0_deg}, {.5_ft, 0_ft, 0_deg}}, "moveOne");
	 intakeLeft.moveVelocity(600);
	 intakeRight.moveVelocity(600);
     profileController->setTarget("moveOne");
     profileController->waitUntilSettled();

	 indexBottom.moveVelocity(600);
	 indexTopTwo.moveVelocity(600);

	 pros::delay(800);

	 indexBottom.moveVelocity(0);
	 indexTopTwo.moveVelocity(0);
	 intakeLeft.moveVelocity(0);
	 intakeRight.moveVelocity(0); 

	 	 profileController->generatePath(
    	{{0_ft, 0_ft, 0_deg}, {2_ft, 0_ft, 0_deg}}, "moveOne");
     profileController->setTarget("moveOne", true);
     profileController->waitUntilSettled();

	 rotate (90, 0);
	}

    //Two goal left side
	if(selector::auton == 2){

	}

	//242 special, start on mid tile
	if (selector::auton == 3){
	 intakeLeft.moveVelocity(300);
	 intakeRight.moveVelocity(300);
	 pros::delay(500);
	 intakeLeft.moveVelocity(0);
	 intakeRight.moveVelocity(0);

	 profileController->generatePath(
     	{{0_ft, 0_ft, 0_deg}, {3.5_ft, 0_ft, 0_deg}}, "moveOne");
     profileController->setTarget("moveOne");
	 pros::delay(750);
	 intakeLeft.moveVelocity(600);
	 intakeRight.moveVelocity(600);
     profileController->waitUntilSettled();

	 intakeLeft.moveVelocity(0);
	 intakeRight.moveVelocity(0);

	 profileController->generatePath(
     	{{0_ft, 0_ft, 0_deg}, {1.5_ft, 0_ft, 0_deg}}, "moveOne");
     profileController->setTarget("moveOne", true);
     profileController->waitUntilSettled();

	 rotate(58, 1);

	 profileController->generatePath(
     	{{0_ft, 0_ft, 0_deg}, {1.3_ft, 0_ft, 0_deg}}, "moveOne");
     profileController->setTarget("moveOne");
     profileController->waitUntilSettled();

	 rotate(40, 0);

	 profileController->generatePath(
     	{{0_ft, 0_ft, 0_deg}, {.72_ft, 0_ft, 0_deg}}, "moveOne");
     profileController->setTarget("moveOne");
	 intakeLeft.moveVelocity(300);
	 intakeRight.moveVelocity(300);
	 indexBottom.moveVelocity(55);
	 indexTopTwo.moveVelocity(55);
     profileController->waitUntilSettled();

	 intakeLeft.moveVelocity(0);
	 intakeRight.moveVelocity(0);
	 indexBottom.moveVelocity(0);
	 indexTopTwo.moveVelocity(0);

	 profileController->generatePath(
     	{{0_ft, 0_ft, 0_deg}, {1_ft, 0_ft, 0_deg}}, "moveOne");
     profileController->setTarget("moveOne", true);
     profileController->waitUntilSettled();

	 rotate(62, 0);

	 profileController->generatePath(
     	{{0_ft, 0_ft, 0_deg}, {1.5_ft, 0_ft, 0_deg}}, "moveOne");
     profileController->setTarget("moveOne");
     profileController->waitUntilSettled();

	 indexBottom.moveVelocity(600);
	 indexTopTwo.moveVelocity(600);
	 intakeLeft.moveVelocity(300);
	 intakeRight.moveVelocity(300);

	 pros::delay(1500);

	 indexBottom.moveVelocity(0);
	 indexTopTwo.moveVelocity(0);
	 intakeLeft.moveVelocity(0);
	 intakeRight.moveVelocity(0);

	 profileController->generatePath(
     	{{0_ft, 0_ft, 0_deg}, {1.5_ft, 0_ft, 0_deg}}, "moveOne");
     profileController->setTarget("moveOne", true);
     profileController->waitUntilSettled();
	}

	//One goal right side
	if (selector::auton == -1){
	 intakeLeft.moveVelocity(300);
	 intakeRight.moveVelocity(300);
	 pros::delay(500);
	 intakeLeft.moveVelocity(0);
	 intakeRight.moveVelocity(0);

	 profileController->generatePath(
    	{{0_ft, 0_ft, 0_deg}, {2.9_ft, 0_ft, 0_deg}}, "moveOne");
     profileController->setTarget("moveOne");
     profileController->waitUntilSettled();

	 rotate(75, 1);

	 intakeLeft.moveVelocity(600);
	 intakeRight.moveVelocity(600);
	 indexBottom.moveVelocity(600);
	 indexTopTwo.moveVelocity(600);

	 profileController->generatePath(
    	{{0_ft, 0_ft, 0_deg}, {1.3_ft, 0_ft, 0_deg}}, "moveTwo");
     profileController->setTarget("moveTwo");
     profileController->waitUntilSettled();

	 pros::delay(750);

	 indexBottom.moveVelocity(0);
	 indexTopTwo.moveVelocity(0);
	 intakeLeft.moveVelocity(-600);
	 intakeRight.moveVelocity(-600);

	 profileController->generatePath(
		{{0_ft, 0_ft, 0_deg}, {1.9_ft, 0_ft, 0_deg}}, "backOne");
	 profileController->setTarget("backOne", true);
	 pros::delay(500);
	 indexBottom.moveVelocity(-600);
	 indexTopTwo.moveVelocity(-600);
	 profileController->waitUntilSettled();

	 intakeLeft.moveVelocity(0);
	 intakeRight.moveVelocity(0);
	 indexBottom.moveVelocity(0);
	 indexTopTwo.moveVelocity(0);
	}

	//Two goal left side
	if (selector::auton == -2){
	 intakeLeft.moveVelocity(300);
	 intakeRight.moveVelocity(300);
	 pros::delay(500);
	 intakeLeft.moveVelocity(0);
	 intakeRight.moveVelocity(0);

	 profileController->generatePath(
    	{{0_ft, 0_ft, 0_deg}, {2.9_ft, 0_ft, 0_deg}}, "moveOne");
     profileController->setTarget("moveOne");
     profileController->waitUntilSettled();

	 rotate(75, 1);

	 intakeLeft.moveVelocity(600);
	 intakeRight.moveVelocity(600);
	 indexBottom.moveVelocity(600);
	 indexTopTwo.moveVelocity(600);

	 profileController->generatePath(
    	{{0_ft, 0_ft, 0_deg}, {1.3_ft, 0_ft, 0_deg}}, "moveTwo");
     profileController->setTarget("moveTwo");
     profileController->waitUntilSettled();

	 pros::delay(750);

	 indexBottom.moveVelocity(0);
	 indexTopTwo.moveVelocity(0);
	 intakeLeft.moveVelocity(-600);
	 intakeRight.moveVelocity(-600);

	 profileController->generatePath(
		{{0_ft, 0_ft, 0_deg}, {1.9_ft, 0_ft, 0_deg}}, "backOne");
	 profileController->setTarget("backOne", true);
	 pros::delay(500);
	 indexBottom.moveVelocity(-600);
	 indexTopTwo.moveVelocity(-600);
	 profileController->waitUntilSettled();

	 intakeLeft.moveVelocity(0);
	 intakeRight.moveVelocity(0);
	 indexBottom.moveVelocity(0);
	 indexTopTwo.moveVelocity(0);
	}

	//242 special, home row
	if (selector::auton == -3){
	 intakeLeft.moveVelocity(300);
	 intakeRight.moveVelocity(300);
	 pros::delay(500);
	 intakeLeft.moveVelocity(0);
	 intakeRight.moveVelocity(0);

	 profileController->generatePath(
    	{{0_ft, 0_ft, 0_deg}, {2.9_ft, 0_ft, 0_deg}}, "moveOne");
     profileController->setTarget("moveOne");
     profileController->waitUntilSettled();

	 rotate(75, 1);

	 intakeLeft.moveVelocity(600);
	 intakeRight.moveVelocity(600);
	 indexBottom.moveVelocity(600);
	 indexTopTwo.moveVelocity(600);

	 profileController->generatePath(
    	{{0_ft, 0_ft, 0_deg}, {1.45_ft, 0_ft, 0_deg}}, "moveTwo");
     profileController->setTarget("moveTwo");
		// pros::delay(900);
		// intakeLeft.moveVelocity(0);
		// intakeRight.moveVelocity(0);
     profileController->waitUntilSettled();

	 pros::delay(750);

	 indexBottom.moveVelocity(0);
	 indexTopTwo.moveVelocity(0);
	 intakeLeft.moveVelocity(-600);
	 intakeRight.moveVelocity(-600);

	 profileController->generatePath(
		{{0_ft, 0_ft, 0_deg}, {2.05_ft, 0_ft, 0_deg}}, "backOne");
	 profileController->setTarget("backOne", true);
	 pros::delay(500);
	 indexBottom.moveVelocity(-600);
	 indexTopTwo.moveVelocity(-600);
	 profileController->waitUntilSettled();

	 intakeLeft.moveVelocity(0);
	 intakeRight.moveVelocity(0);
	 indexBottom.moveVelocity(0);
	 indexTopTwo.moveVelocity(0);
	
	 rotate(206, 0);

	 profileController->generatePath(
   		 {{0_ft, 0_ft, 0_deg}, {7.3_ft, 0_ft, 0_deg}}, "moveThree");
	 profileController->setTarget("moveThree");
	 profileController->waitUntilSettled();
	
	 rotate(162, 0);

	 intakeLeft.moveVelocity(600);
	 intakeRight.moveVelocity(600);
	 indexBottom.moveVelocity(600);
	 indexTopTwo.moveVelocity(600);

	 profileController->generatePath(
    	{{0_ft, 0_ft, 0_deg}, {2.5_ft, 0_ft, 0_deg}}, "movefour");
     profileController->setTarget("movefour");
     profileController->waitUntilSettled();
	 
	 pros::delay(500);

	 indexBottom.moveVelocity(0);
	 indexTopTwo.moveVelocity(0);
	 intakeLeft.moveVelocity(-600);
	 intakeRight.moveVelocity(-600);
	 
	 profileController->generatePath(
    	{{0_ft, 0_ft, 0_deg}, {2_ft, 0_ft, 0_deg}}, "movefour");
     profileController->setTarget("movefour", true);
	 pros::delay(500);
	 indexBottom.moveVelocity(-600);
	 indexTopTwo.moveVelocity(-600);
     profileController->waitUntilSettled();

	 rotate(310, 0);

	 indexBottom.moveVelocity(0);
	 indexTopTwo.moveVelocity(0);
	 intakeLeft.moveVelocity(0);
	 intakeRight.moveVelocity(0);
	}
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
	 indexBottom.setBrakeMode(AbstractMotor::brakeMode::coast);
	 indexTopTwo.setBrakeMode(AbstractMotor::brakeMode::coast);
	 intakeLeft.setBrakeMode(AbstractMotor::brakeMode::coast);
	 intakeRight.setBrakeMode(AbstractMotor::brakeMode::coast);

	 chassis->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
								 controller.getAnalog(ControllerAnalog::rightX));

	 intake();
	 index();
	 autontest();

	 pros::delay(20);
	}
}
