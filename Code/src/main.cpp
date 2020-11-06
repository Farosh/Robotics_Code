#include "main.h"

// fill in the pins: for example, #DEFINE PIN 0
#DEFINE LEFT_FRONT_MOTOR
#DEFINE RIGHT_FRONT_MOTOR
#DEFINE LEFT_BACK_MOTOR
#DEFINE RIGHT_BACK_MOTOR
#DEFINE MOTOR_MOD 1 // if needed, multiplier on motor inputs

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor leftFront(LEFT_FRONT_MOTOR);
pros::Motor rightFront(RIGHT_FRONT_MOTOR);
pros::Motor leftBack(LEFT_BACK_MOTOR);
pros::Motor rightBack(RIGHT_BACK_MOTOR);

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
void opcontrol() {
	while (true) {
		updateDriveBase();
		pros::delay(20);
	}
}

// updates drive base motors based on controller input
updateDriveBase()
{
	leftFront.move(MOTOR_MOD * master.get_analog(E_CONTROLLER_MASTER_LEFT_Y));
	leftBack.move(MOTOR_MOD * master.get_analog(E_CONTROLLER_MASTER_LEFT_Y));
	rightFront.move(MOTOR_MOD * master.get_analog(E_CONTROLLER_MASTER_RIGHT_Y));
	rightBack.move(MOTOR_MOD * master.get_analog(E_CONTROLLER_MASTER_RIGHT_Y));
}
