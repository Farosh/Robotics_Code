#include "main.h"



// fill in the information
#define LEFT_FRONT_MOTOR 0
#define RIGHT_FRONT_MOTOR 0
#define LEFT_BACK_MOTOR 0
#define RIGHT_BACK_MOTOR 0
#define MOTOR_MOD 1 // if needed, multiplier on all motor inputs
// assuming all drive base motors have the same gearset
// fill in E_MOTOR_GEARSET_36 for red, 18 for green, 06 for blue
#define DRIVE_BASE_GEARSET pros::E_MOTOR_GEARSET_18
// also, if any of the drive base motors individually run in reverse, go to the
// all drive base motors defined section and change each reversed motor's
// parameter of 0 to 1; I'd have you just change the modifier, but then I'd
// need a modifier for each one, instead of just manually reversing the motors.

// intake pins; intakes are set to the left and right top triggers
#define LEFT_INTAKE 0
#define RIGHT_INTAKE 0
#define INTAKE_MOD 1 // multiplier on intakes
#define INTAKES_GEARSET pros::E_MOTOR_GEARSET_18 // same drill as above

// flywheel pin; I'm assuming you only want the flywheel in one direction; tell
// me if that's incorrect. If it spins the wrong way, make FLYWHEEL_MOD negative
// flywheel currently set to the left, bottom trigger
#define FLYWHEEL 0
#define FLYWHEEL_MOD 1 // multiplier on flywheel
#define FLYWHEEL_GEARSET pros::E_MOTOR_GEARSET_18 // same drill as above



// main controller defined
pros::Controller master (pros::E_CONTROLLER_MASTER);

// all drive base motors defined
pros::Motor leftFront(LEFT_FRONT_MOTOR, DRIVE_BASE_GEARSET, 0,
	pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightFront (RIGHT_FRONT_MOTOR, DRIVE_BASE_GEARSET, 0,
	pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftBack (RIGHT_FRONT_MOTOR, DRIVE_BASE_GEARSET, 0,
	pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightBack (RIGHT_BACK_MOTOR, DRIVE_BASE_GEARSET, 0,
	pros::E_MOTOR_ENCODER_DEGREES);

// intake motors defined
pros::Motor leftIntake (LEFT_INTAKE, INTAKES_GEARSET, 0,
	pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightIntake (RIGHT_INTAKE, INTAKES_GEARSET, 0,
	pros::E_MOTOR_ENCODER_DEGREES);

// flywheel motor defined
pros::Motor flywheel (FLYWHEEL, FLYWHEEL_GEARSET, 0,
	pros::E_MOTOR_ENCODER_DEGREES);



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {}

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
void autonomous() {}

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

// FUNCTIONS FOR OP CONTROL

// updates drive base motors based on controller input
void updateDriveBase()
{
	leftFront.move(MOTOR_MOD *
		master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
	leftBack.move(MOTOR_MOD *
		master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
	rightFront.move(MOTOR_MOD *
		master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
	rightBack.move(MOTOR_MOD *
		master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
}

// updates intakes
void updateIntakes()
{
	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
	{
		leftIntake.move(INTAKE_MOD * 127);
		rightIntake.move(-INTAKE_MOD * 127);
	}
	else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
	{
		leftIntake.move(-INTAKE_MOD * 127);
		rightIntake.move(INTAKE_MOD * 127);
	}
}

// updates flywheel
void updateFlywheel()
{
	if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
	{
		flywheel.move(FLYWHEEL_MOD * 127);
	}
}

// opcontrol itself
void opcontrol() {
	while (true) {
		updateDriveBase();
		updateIntakes();
		pros::delay(20);
	}
}
