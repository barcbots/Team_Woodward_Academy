#pragma config(Sensor, in1,    knob,           sensorPotentiometer)
#pragma config(Motor,  port1,           LiftRightB,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           LiftRightM,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           LiftRightT,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           DL,            tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           Hang,          tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           Hang,          tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           DR,            tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           LiftLeftT,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           LiftLeftM,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          LiftLeftB,     tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
//Kia got a crush on Mr hre
//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
//#include "LCD Wizard 2.c"
//#include "LCD Selection Wizard.c"

void pre_auton() {
	//startTask(lcdSelection);
}
/* void stopMotors()
{
motor[LiftRight] = 0;
motor[LiftRight] = 0;
motor[LiftRight] = 0;
motor[LiftLeft] = 0;
motor[LiftLeft] = 0;
motor[LiftLeft] = 0;
}

void LiftUp(float rotations)
{
nMotorEncoder[LiftRight] = 0;
while(nMotorEncoder[LiftRight]<rotataions*360)
{
motor[LiftRight] = 127;
motor[LiftRight] = 127;
motor[LiftRight] = 127;
motor[LiftLeft] = 127;
motor[LiftLeft] = 127;
motor[LiftLeft] = 127;
}
stopMotors ();
}
void LiftDown (float rotatitons)
{
nMotorEncoder[LiftLeft] = 0;
while(nMotorEncoder[LiftRight]<rotataions*360)
{
motor[LiftRight] = -127;
motor[LiftRight] = -127;
motor[LiftRight] = -127;
motor[LiftLeft] = -127;
motor[LiftLeft] = -127;
motor[LiftLeft] = -127;
}
stopMotors ();
}
void LiftUp (float rotations)
{
nMotorEncoder[LiftRight] = 0;
while(nMotorEncoder[LiftRight]<rotataions*360)
{
motor[LiftRight] = 127;
motor[LiftRight] = 127;
motor[LiftRight] = 127;
motor[LiftLeft] = 127;
motor[LiftLeft] = 127;
motor[LiftLeft] = 127;
}
}

task main()
{
LiftUp(1)
LiftUp(-1)
LiftUp(1)
nMotorEncoder[LiftRight] = 0;
moveFoward(.

*/

void setLiftMotors(int power)
{
	motor[LiftLeftB] = power;
	motor[LiftLeftM] = power;
	motor[LiftLeftT] = power;
	motor[LiftRightB] = power;
	motor[LiftRightM] = power;
	motor[LiftRightT] = power;
}

void setLeftDtMotors(int power) {
	//set left drivetrain motors to power
	motor[DL] = power;
}

void setRightDtMotors(int power) {
	//set right drivetrain motors to power
	motor[DR] = power;
}

void moveLift(int power) {
	//while time1[T1] is less than time
	//set motors to power
	motor[LiftLeftT] = power;
	motor[LiftLeftB] = power;
	motor[LiftLeftM] = power;
	motor[LiftRightB] = power;
	motor[LiftRightM] = power;
	motor[LiftRightT] = power;
}
void drive(int powerL, int powerR) {
	//while time1[T1] is less than time
	//set drivetrain motors to ptime
	motor[DL] = powerL;
	motor[DR] = powerR;
}
void turnRight(int power) {
	//while time1[T1] is less than time
	//set drivetrain motors to ptime
	motor[DL] = -power;
	motor[DR] = power;
}
void moveHang (int power){
//while time1[T1] is less than time
//set motor to power
motor[Hang] = power;
motor[Hang] = power;
}

task autonomousLeft()
{
	moveLift(-127);
	wait10Msec(40);
	moveLift(60);
	wait10Msec(100);
	moveLift(0);
	wait10Msec(20)
	drive(125,118);
	wait10Msec(147);
	drive(-125,-125);
	wait10Msec(30);
	drive(0,0);
	turnRight(-125);
	wait10Msec(110);
	turnRight(0);
	drive(-125,-125);
	wait10Msec(75);
	drive(0,0);
	moveLift(127);
	wait10Msec(70);
	moveLift(0);
}

task autonomousRight ()
{
	moveLift(-127);
	wait10Msec(40);
	moveLift(60);
	wait10Msec(100);
	moveLift(0);
	wait10Msec(20)
	drive(125,118);
	wait10Msec(147);
	drive(-125,-125);
	wait10Msec(30);
	drive(0,0);
	turnRight(-125);
	wait10Msec(110);
	turnRight(0);
	drive(-125,-125);
	wait10Msec(75);
	drive(0,0);
	moveLift(127);
	wait10Msec(70);
	moveLift(0);
}

task autonomousForward ()
{
	moveLift(-127);
	wait10Msec(30);
	moveLift(40);
	wait10Msec(150);
	drive(125,125);
	moveLift(0);
	wait10Msec(130);
	drive(0,0);

	/*
	turnRight(125);
	wait10Msec(55);
	turnRight(0);
	drive(125,125);
	wait10Msec(30);
	drive(0,0);
	turnLeft(125);
	wait10Msec(30);
	turnLeft(0,0);
	drive(125,125);
	wait10Msec(30);
	drive(0,0);
	turnRight


	drive(125,125)
	turnLeft(
	wait10Msec(150)
	drive(125,125)
	*/
}

task skillsauton()
{
	moveLift(0);
	drive(-127,-127);
	wait10Msec(40);
	drive(0,0);
	moveLift(-127);
	wait10Msec(60);
	{
		while(True){
			moveLift(0);
			drive(0,0);
			wait10Msec(200);
			moveLift(60);
			wait10Msec(70);
			moveLift(0);
			drive(-125,-125);
			wait10Msec(70);
			drive(0,0);
			moveLift(127);
			wait10Msec(110);
			moveLift(0);
			wait10Msec(40);
			moveLift(-127);
			wait10Msec(70);
			moveLift(0);
			drive(125,125);
			wait10Msec(70);
			moveLift(0);
			drive(0,0);
			wait10Msec(200);
			moveLift(60);
			wait10Msec(70);
			moveLift(0);
			drive(-125,-125);
			wait10Msec(70);
			drive(0,0);
			moveLift(127);
			wait10Msec(110);
			moveLift(0);
			wait10Msec(40);
			moveLift(-127);
			wait10Msec(70);
			moveLift(0);
			drive(125,125);
			wait10Msec(70);
			moveLift(0);
			drive(0,0);
			wait10Msec(200);
			moveLift(60);
			wait10Msec(70);
			moveLift(0);
			drive(-125,-125);
			wait10Msec(70);
			drive(0,0);
			moveLift(127);
			wait10Msec(110);
			moveLift(0);
			wait10Msec(40);
			moveLift(-127);
			wait10Msec(70);
			moveLift(0);
			drive(125,125);
			wait10Msec(70);
			moveLift(0);
			drive(0,0);
			wait10Msec(200);
			moveLift(60);
			wait10Msec(70);
			moveLift(0);
			drive(-125,-125);
			wait10Msec(70);
			drive(0,0);
			moveLift(127);
			wait10Msec(110);
			moveLift(0);
			wait10Msec(40);
			moveLift(-127);
			wait10Msec(70);
			moveLift(0);
			drive(125,125);
			wait10Msec(70);
			moveLift(0);
			drive(0,0);
			wait10Msec(200);
		}
	}

	/*
	moveLift(60);
	wait10Msec(50);
	moveLift(0);
	drive(-125,-118);
	wait10Msec(50);
	drive(0,0);
	moveLift(127);
	wait10Msec(50);
	moveLift(-127);
	wait10Msec(60);
	drive(125,118);
	wait10Msec();
	drive(-125,-125);
	moveLift(127);
	moveLift(-127);
	drive(125,125);
	drive(0,0);
	*/
}
task autonomous() {
	if (SensorValue[knob] >0 && SensorValue[knob] <=1000)
	{
		startTask(autonomousLeft);
	}
	else if (SensorValue[knob] >=1000 && SensorValue[knob] <=2000)
	{
		startTask(autonomousRight);
	}
	else if (SensorValue[knob]>=2000 && SensorValue[knob] <=3000)
	{
		startTask(autonomousForward);
	}
	else if (SensorValue[knob]>=3000 && SensorValue[knob] <=4000)
	{
		startTask(skillsauton);
	}
}
/*if(autonChoices.startingTile == "left")
{
startTask(autonomousLeft);
}
if(autonChoices.startingTile == "programmingSkills")
{
//start auto skills task
}
if(autonChoices.startingTile == "right")
{
//start right auto play
}*/
//if
//}
task drivetrainController() {
	int lYRequested,
	rYRequested,
	lYLastSent = 0,
	rYLastSent = 0,
	lY,
	rY,
	slewRateLimit = 15,
	threshold = 15;
	while(true) {
		lYRequested = vexRT[Ch3];
		rYRequested = vexRT[Ch2];
		if (abs(lYRequested - lYLastSent) > slewRateLimit) { //if the new power requested is greater than the slew rate limit
			if (lYRequested > lYLastSent) {
				lY += slewRateLimit; //only increase the power by the max allowed by the slew rate
				} else {
				lY -= slewRateLimit; //only decrease the power by the max allowed by the slew rate
			}
			} else {
			lY = (lYRequested == 0) ? 0 : lY;
		}
		lYLastSent = lY;
		if (abs(rYRequested - rYLastSent) > slewRateLimit) {
			if (rYRequested > rYLastSent) {
				rY += slewRateLimit;
				} else {
				rY -= slewRateLimit;
			}
			} else {
			rY = (rYRequested == 0) ? 0 : rY;
		}
		rYLastSent = rY;
		motor[DL] = (abs(lY) > threshold) ? lY : 0;
		motor[DR] = (abs(rY) > threshold) ? rY : 0;
		wait1Msec(15);
	}
	bool auton = false;
}
task usercontrol()
{
	startTask(drivetrainController);
	//startTask(autonomous);
	while(true)
	{
		if (vexRT[Btn5U]) {
			setLiftMotors(127);
			} else if (vexRT[Btn5D]) {
			setLiftMotors(-127);
			} else {
			setLiftMotors(9);
		}
			if (vexRT[Btn6U]) {
			moveHang(127);
			} else if (vexRT[Btn6D]) {
			moveHang(-127);
		} else {
			moveHang(0);
	}
		wait1Msec(25);
	}
}


//(vexRT[Btn7D && Btn7R] == 1)
