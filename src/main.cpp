#include "main.h"
#include "api.h"
#include "okapi/api.hpp"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous() {
	//homerow auton??
	using namespace okapi;
//#17 is upper uptakes and #16 is lower uptakes
	MotorGroup uptakesOut({-17, -16});
	MotorGroup uptakesSpit({17, -16});

	MotorGroup forwardIntake({8, -7, 12, -1, -2, 11});
	MotorGroup specialBoi({8, -7, 12, -1, -2, 11, -16});

	MotorGroup xDriveStrafe({1, -11, -2, 12});
	MotorGroup turnRight({1, 11, 2, 12});
	MotorGroup turnLeft({-1, -11, -2, -12});

//#8 is right intake and #7 is left intake
	MotorGroup intakeIn({8, -7});
	MotorGroup intakeOut({-8, 7});

	//represents chassis for moving forward and backward for the meantime
	std::shared_ptr<ChassisController> chassisFB = ChassisControllerBuilder()
	.withMotors(12, -1, -2, 11)
	// Green gearset, 3 in wheel diam, 11.5 in wheel track
	.withDimensions(AbstractMotor::gearset::green, {{3_in, 11.5_in}, imev5GreenTPR})
	.build();

	//represents chassis for moving left and right for the meantime (strafing)
	std::shared_ptr<ChassisController> chassisLR = ChassisControllerBuilder()
	.withMotors(12, 1, -2, -11)
	// Green gearset, 3 in wheel diam, 11.5 in wheel track
	.withDimensions(AbstractMotor::gearset::green, {{3_in, 11.5_in}, imev5GreenTPR})
	.build();

	//flips out intakes

	//launches ball.. finally figured out motor group :')

	//uptakesOut.moveRelative(3000, 127);

	/*
	chassisLR->setMaxVelocity(70);
	chassisFB->setMaxVelocity(70);
	pros::delay(2000);
	chassisLR->moveDistance(-5_in);
	intakes.moveRelative(3000, 127);
	pros::delay(100);
	chassisFB->turnAngle(45_deg);
	pros::delay(100);
	chassisFB->moveDistance(12_in);
	intakes.moveRelative(3000, -127);
	uptakesOut.moveRelative(3000, 127);*/

	//
	/*
	chassisLR->setMaxVelocity(100);
	chassisFB->setMaxVelocity(100);
	chassisLR->moveDistance(-6_in); */

	/*
	intakeOut.moveRelative(2000, 127);
	pros::delay(1750);
	turnRight.moveRelative(500, 100);
	pros::delay(300);
	//chassisFB->moveDistance(12_in);
	forwardIntake.moveRelative(1500, 120);
	pros::delay(1250);
	uptakesOut.moveRelative(2750, 127);
	pros::delay(1000);
	chassisFB->moveDistance(-10_in);

	//second part: corner and middle edge goal
	turnLeft.moveRelative(3450, 90); pros::delay(2000);
	chassisFB->moveDistance(30_in);
	turnLeft.moveRelative(2500, 90); pros::delay(1250);
	specialBoi.moveRelative(3000,120); pros::delay(2500);
	uptakesOut.moveRelative(3000, 127);*/

	/*
	turnLeft.moveRelative(500, 100); pros::delay(250);

	chassisFB->setMaxVelocity(127);
	chassisFB->moveDistance(-50_in);
	turnRight.moveRelative(1250, 100); pros::delay(1250);
	specialBoi.moveRelative(600, 127); pros::delay(750);
	chassisFB->moveDistance(9_in);
	uptakesOut.moveRelative(3000, 127); pros::delay(2000);
	chassisFB->moveDistance(-10_in);*/

	//third part.. finish row hopefully
	chassisFB->setMaxVelocity(110);

	uptakesOut.moveAbsolute(2000, 127); pros::delay(1250);

	chassisFB->moveDistance(-5_in);
	turnLeft.moveAbsolute(1250, 100); pros::delay(1250);
	intakeOut.moveAbsolute(2000, 127); pros::delay(1000);
	turnLeft.moveRelative(1700, 100); pros::delay(1250);
	intakeIn.moveRelative(3000, 127);
	chassisFB->moveDistance(45_in);
	turnLeft.moveRelative(2000, 100); pros::delay(1000);
	chassisFB->moveDistance(15_in);
	uptakesOut.moveRelative(2500, 127); pros::delay(1000);
	chassisFB->moveDistance(-10_in);

	turnRight.moveRelative(1100, 127); pros::delay(1000);
	intakeIn.moveRelative(4500, 127);
	chassisFB->moveDistance(33_in);
	turnLeft.moveRelative(750, 100); pros::delay(500);

	chassisFB->moveDistance(12_in);
	uptakesOut.moveRelative(2500, 127); pros::delay(1000);
	chassisFB->moveDistance(-12_in);

	turnRight.moveRelative(2500, 127); pros::delay(1000);
	intakeIn.moveRelative(4500, 127);
	chassisFB->moveDistance(40_in);
	turnLeft.moveRelative(1250, 127); pros::delay(1000);
	chassisFB->moveDistance(15_in);
	uptakesOut.moveRelative(2500, 127); pros::delay(100);

/*
	chassisFB->setMaxVelocity(100);
	chassisFB->moveDisdtance(2_m);
	chassisLR->moveDistance(2_m);
	chassisLR->moveDistance(-1_m);
	chassisFB->turnAngle(90_deg);*/
	/*
	chassisFB->moveDistance(2_ft);
	//chassisLR->moveDistance(2_ft);
	chassisLR->moveDistance(2_ft);*/

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	using namespace pros;

	Motor driveFrontLeft(12);
	Motor driveFrontRight(1);
	Motor driveBackLeft(11);
	Motor driveBackRight(2);

	Motor uptakeLow(16, true);
	Motor uptakeHigh(17, true);

	Motor intakeRight(8);
	Motor intakeLeft(7, true);

	Controller joystick(CONTROLLER_MASTER);

	int leftX, rightY, rightX;
	bool out, spit;
	bool iForward, iReverse;

	while (true) {
		leftX = joystick.get_analog(ANALOG_LEFT_X);
		rightY = joystick.get_analog(ANALOG_RIGHT_Y);
		rightX = joystick.get_analog(ANALOG_RIGHT_X);

		out = joystick.get_digital(DIGITAL_L1);
		spit = joystick.get_digital(DIGITAL_L2);

		iForward = joystick.get_digital(DIGITAL_R1);
		iReverse = joystick.get_digital(DIGITAL_R2);

		driveFrontLeft = leftX+rightY+rightX;
		driveBackLeft = leftX+rightY-rightX;
		driveFrontRight = leftX-rightY+rightX;
		driveBackRight = leftX-rightY-rightX;

		if (out) {
			uptakeHigh = 127;
			uptakeLow = 90;
		}
		else if (spit) {
			uptakeHigh = -127;
			uptakeLow = 90;
		}
		else {
			uptakeHigh = 0;
			uptakeLow = 0;
		}

		if (iForward) {
			intakeLeft = 127;
			intakeRight = 127;
		}
		else if (iReverse) {
			intakeLeft = -127;
			intakeRight = -127;
		}
		else {
			intakeLeft = 0;
			intakeRight = 0;
		}

		delay(20); //20 milliseconds.. helps cool CPU
	}
}
