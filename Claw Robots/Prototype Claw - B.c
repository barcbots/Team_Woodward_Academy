#pragma config(Sensor, in1,    claw,           sensorPotentiometer)
#pragma config(Sensor, in2,    arm,            sensorNone)
#pragma config(Sensor, in3,    gyro,           sensorNone)
#pragma config(Sensor, dgtl1,  rDriveEnc,      sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  lDriveEnc,      sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  liftDown,       sensorTouch)
#pragma config(Sensor, dgtl6,  liftEnc,        sensorQuadEncoder)
#pragma config(Motor,  port1,           leftClaw,      tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           lDriveFront,   tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           lDriveBack,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           lDump12,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           lDump3,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           rDump3,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           rDump12,       tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           rDriveBack,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           rDriveFront,   tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          rightClaw,     tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Competition stuff
// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

//global variables
int LEFT = 1; //note that changing this value could affect gyro rotation function if LEFT is used for the value of the direction parameter in that function
int RIGHT = 2;
int AUTON_SIDE = 0; //either LEFT or RIGHT, as above
int AUTON_PLAY = 0;
int armPotOffset = 0; //The value of the claw potentiometer when the claw is fully closed and touching the physical limit

//Our includes
#include "autonomousLib B.c"
#include "../State/Position PID - 4 Motor Struct.c"
#include "LCD Wizard.c"
//setDumpMotors and setClawMotors are in autonomousLib.c


void pre_auton()
{
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	bDisplayCompetitionStatusOnLcd = false;

	bLCDBacklight = true;
	bool testLcdWizard = false;
	if (bIfiRobotDisabled || testLcdWizard) { //Only show auton play wizard when the robot is in competition mode & disabled on initial startup
		startTask(LCDSelect);
	}
}

int getArmPos() {
	return SensorValue[claw] - armPotOffset;
}


//potentiometer value for lift: 2150
int liftTarget;
int clawTarget;
int liftgo = 0;
task liftTask()
{
	while(1)
	{
		if(liftgo == 1)
		{
			liftToPotTarget(liftTarget,127);
			liftgo = 0;
		}
	}
}
task clawTask()
{
	moveClaw(127,clawTarget);
}

task progSkills() {
	SensorValue[rDriveEnc] = 0;
	SensorValue[lDriveEnc] = 0;
	liftTarget = 800;
	clawTarget = 1750;
	startTask(clawTask);
	straight(-127, 200);
	waitForClaw(1750,50);
	wait10Msec(250);
	moveClaw(127, 3200);
	straight(127,150);
	setClawMotors(-127);
	wait1Msec(500);
	setClawMotors(-25);
	straight(-127,1150);
	liftgo = 1;
	startTask(liftTask);
	waitForLift(800,50);
	stopTask(liftTask);
	setDumpMotors(127);
	wait1Msec(1250);
	startTask(clawTask);
	waitForClaw(1750,50);
	setDumpMotors(0);
	wait10Msec(80);
	straight(127,150)
	setDumpMotors(-127);
	while(SensorValue[liftDown] == 0)
	{
		wait1Msec(25);
	}
	setDumpMotors(0);
	startTask(clawTask);
	straight(127,1075);
	wait10Msec(100);
	moveClaw(127, 3200);
	straight(127,150);
	setClawMotors(-127);
	wait1Msec(500);
	setClawMotors(-25);
	straight(-127,1220);
	liftgo = 1;
	startTask(liftTask);
	waitForLift(800,50);
	stopTask(liftTask);
	setDumpMotors(127);
	wait1Msec(1850);
	startTask(clawTask);
	waitForClaw(1750,50);
	setDumpMotors(0);
	wait10Msec(80);
	straight(127,150);
	setDumpMotors(-127);
	while(SensorValue[liftDown] == 0)
	{
		wait1Msec(25);
	}
	setDumpMotors(0);
	straight(127,150);
	strafeleft(100,127);
	moveClaw(127,2550);
	SensorValue[rDriveEnc] = 0;
	while(abs(SensorValue[rDriveEnc]) < 340.5)
	{
	setRightDtMotors(-85);
	setLeftDtMotors(85);
	}
	setRightDtMotors(0);
	setLeftDtMotors(0);
	straight(127,1050);
	setClawMotors(-127);
	wait10Msec(100);
	setClawMotors(-30);
	liftToPotTarget(800,127);
	SensorValue[rDriveEnc] = 0;
	while(abs(SensorValue[rDriveEnc]) < 340.5)
	{
	setRightDtMotors(85);
	setLeftDtMotors(-85);
	}
	setRightDtMotors(0);
	setLeftDtMotors(0);
	stopTask(liftTask);
	setDumpMotors(127);
	wait1Msec(1250);
	startTask(clawTask);
	waitForClaw(1750,50);
	setDumpMotors(0);
	wait10Msec(80);
	setDumpMotors(-127);
	while(SensorValue[liftDown] == 0)
	{
		wait1Msec(25);
	}
	setDumpMotors(0);
	/*SensorValue[rDriveEnc] = 0;
	while(SensorValue[rDriveEnc] < 735)
	{
	setRightDtMotors(85);
	setLeftDtMotors(-85);
	}
	setRightDtMotors(0);
	setLeftDtMotors(0);
	liftToPotTarget(3900, -127)
	moveClaw(127, 1900);*/
	straight(127, 175);
	moveClaw(127, 3200);
	setClawMotors(-127);
	wait1Msec(500);
	setClawMotors(-25);
	straight(-127, 350);
	liftgo = 1;
	startTask(liftTask);
	waitForLift(800,50);
	stopTask(liftTask);
	setDumpMotors(127);
	wait1Msec(1250);
	startTask(clawTask);
	waitForClaw(1750,50);
	setDumpMotors(0);
	wait10Msec(80);
	setDumpMotors(-127);
	while(SensorValue[liftDown] == 0)
	{
		wait1Msec(25);
	}
	setDumpMotors(0);
	//straight(127, 200)
	straight(127,1075);
	moveClaw(127, 3200);
	setClawMotors(-50);
	wait10Msec(100);
	straight(-127,1075);
	stopTask(liftTask);
	liftTarget = 800;
	liftgo = 1;
	startTask(liftTask);
	waitForLift(800,50);
	stopTask(liftTask);
	setDumpMotors(127);
	wait1Msec(1250);
	startTask(clawTask);
	waitForClaw(1750,50);
	setDumpMotors(0);
	wait10Msec(80);
	straight(127,150);
	setDumpMotors(-127);
	while(SensorValue[liftDown] == 0)
	{
		wait1Msec(25);
	}
	setDumpMotors(0);
	straight(127,150);
	startTask(clawTask);
	/*SensorValue[rDriveEnc] = 0;
	while(SensorValue[rDriveEnc] < 735)
	{
	setRightDtMotors(85);
	setLeftDtMotors(-85);
	}
	setRightDtMotors(0);
	setLeftDtMotors(0);
	liftToPotTarget(3900, -127)
	moveClaw(127, 1900);*/
	strafeRight(700, 127);
	straight(127,750);
	wait10Msec(100);
	moveClaw(127, 3200);
	straight(127,150);
	setClawMotors(-127);
	wait1Msec(500);
	setClawMotors(-25);
	straight(-127,1220);
	liftgo = 1;
	startTask(liftTask);
	waitForLift(800,50);
	stopTask(liftTask);
	setDumpMotors(127);
	wait1Msec(1850);
	startTask(clawTask);
	waitForClaw(1750,50);
	setDumpMotors(0);
	wait10Msec(80);
	straight(127,150);
	setDumpMotors(-127);
	while(SensorValue[liftDown] == 0)
	{
		wait1Msec(25);
	}
	setDumpMotors(0);

}

task autonomous() {
	wait10Msec(250);
	startTask(progSkills);
	//Auton plays and their numbers, for reference.  These numbers are set as the value of the AUTON_PLAY variable to control which auton play runs
	//#1 Big
	//#2 Small
	//#3 Cube (score middle cube and block)
	//#4 Fence (3 stars, corner)
	//#5 Nothing
	//#6 Prog skills

	//plays should differentiate between left and right using AUTON_SIDE and changing certain values accordingly (ex: running the right side version of a function)
	if (AUTON_PLAY == 1) { //uncomment line inside this block when task exists
		//startTask(autonBig);
		} else if (AUTON_PLAY == 2) {
		//startTask(autonSmall);
		} else if (AUTON_PLAY == 3) {
		//startTask(autonCube);
		} else if (AUTON_PLAY == 4) {
		//startTask(autonFence);
		} else if (AUTON_PLAY == 5) {
		//Do nothing
		} else if (AUTON_PLAY == 6) {
		startTask(progSkills);
		stopTask(autonomous);
	}
	stoptask(autonomous)
	SensorValue[rDriveEnc] = 0;
	SensorValue[lDriveEnc] = 0;
	liftTarget = 800;
	clawTarget = 1750;//A
	//startTask(liftTask);
	//liftgo = 1;
	startTask(clawTask);
	diagonalLeft(-127,50);
	//waitForLift(2000,50);
	waitForClaw(1750,50);//A
	wait1Msec(250);
	straight(-127,1200);
	//wait1Msec(125);
	straight(127,150);
	/*SensorValue[rDriveEnc] = 0;
	while(SensorValue[rDriveEnc] < 735)
	{
	setRightDtMotors(85);
	setLeftDtMotors(-85);
	}
	setRightDtMotors(0);
	setLeftDtMotors(0);
	liftToPotTarget(3900, -127)
	moveClaw(127, 1900);*/
	strafeRight(1020, 127);
	straight(127, 75);
	moveClaw(127, 3200);
	setClawMotors(-127);
	wait1Msec(500);
	setClawMotors(-25);
	straight(-127, 350);
	liftgo = 1;
	startTask(liftTask);
	waitForLift(800,50);
	stopTask(liftTask);
	setDumpMotors(127);
	wait1Msec(1100);
	startTask(clawTask);
	waitForClaw(1750,50);
	setDumpMotors(0);
	wait10Msec(80);
	setDumpMotors(-127);
	while(SensorValue[liftDown] == 0)
	{
		wait1Msec(25);
	}
	setDumpMotors(0);
	//straight(127, 200)
	straight(127,1075);
	moveClaw(127, 3200);
	setClawMotors(-50);
	wait10Msec(100);
	straight(-127,1075);
	stopTask(liftTask);
	liftTarget = 800;
	liftgo = 1;
	startTask(liftTask);
	waitForLift(800,50);
	stopTask(liftTask);
	setDumpMotors(127);
	wait1Msec(1250);
	startTask(clawTask);
	waitForClaw(1750,50);
	setDumpMotors(0);
	wait10Msec(80);
	liftToPotTarget(4000,-127);
	//arm down
	//wait
	//drive forward
	//wait
	//close claw
	//wait
	//lift arm
	//drive back
	//wait
	//raise arm
	//open claw
	//wait
}

/*task progSkills() {
	straight(-127,250);
	clawTarget = 2700;//A
	startTask(clawTask);
	waitForClaw(2700,100);
	setClawMotors(15);
	wait1Msec(1000);
	//clawTarget = 4095;
	//startTask(clawTask);
	//waitForClaw(4075,25);
	//setClawMotors(-20);
	//wait1Msec(1000);
	//liftTarget = 3670;
	//startTask(liftTask);
	//straight(-127,700);
	//wait1Msec(250);
	//liftTarget = 2100;
	//startTask(liftTask);
	//straight(-127,500);


	//liftTarget = 1950;

}*/

task clawControl()
{
	int PIDTargetValue;
	float kp = 0.5; //these constants might change down the road, but they are good for now
	float ki = 0.01;
	float kd = 0.00001;
	int error;
	int integral = 0;
	int derivative;
	int lastError = 0; //start this at 0 so the first time `derivative = error - lastError` runs there's no issue
	int PIDDrive;
	while(true)
	{
		if(vexRT[Btn6U]) //opens claw
		{
			setClawMotors(127);
			//do we want to clear the integral and lastError terms here?
			PIDTargetValue = SensorValue[claw];
		}
		else if(vexRT[Btn6D]) //closes claw
		{
			setClawMotors(-127);
			//do we want to clear the integral and lastError terms here?
			PIDTargetValue = SensorValue[claw];
		}
		else //holds position with PID
		{
			error = PIDTargetValue - SensorValue[claw];
			integral += error;
			derivative = error - lastError;
			PIDDrive = kp*error + ki*integral + kd*derivative;
			setClawMotors(PIDDrive);
			lastError = error;
		}
		wait1Msec(25); //prevents cpu hogging
	}
}


bool holdDown = false;
bool liftCompStarted = false;

task liftComp() {
	int target = SensorValue[liftEnc];
	liftToTargetPIDEnc(target+5,1000,2,0.00035,.2);
	while(1) {
		wait1Msec(500); //keep this task alive until it stops; the wait time here doesn't really matter, since the task will be stopped when it is no longer needed
	}
}

task usercontrol()
{
	int LY = 0;
	int LX = 0;
	int RY = 0;
	int RX = 0;
	int threshold = 15;
	int armEncMaxLimit = 118; //software limit for potentiometer to limit arm movement from going over the top (protects potentiometer)
	bool enableSoftwareArmPosLimit = true; //experimental software limit for arm, see above
	int clawCompPower = 15;
  while(1)
  {
  	//for deadzones; when the joystick value for an axis is below the threshold, the motors controlled by that joystick will not move in that direction
  	LY = (abs(vexRT[Ch3]) > threshold) ? vexRT[Ch3] : 0;
  	LX = (abs(vexRT[Ch4]) > threshold) ? vexRT[Ch4] : 0;
  	RY = (abs(vexRT[Ch2]) > threshold) ? vexRT[Ch2] : 0;
  	RX = (abs(vexRT[Ch1]) > threshold) ? vexRT[Ch1] : 0;
    motor[lDriveFront] = LY + LX;
  	motor[lDriveBack] = LY - LX;
  	motor[rDriveFront] = RY - RX;
  	motor[rDriveBack] = RY + RX;

  	//old lift macros
    //if(vexRT[Btn7U])
		//{
		//	liftgo = 1;
		//	clawTarget = 2000;
		//	liftTarget = 2000;
		//	startTask(clawTask);
		//	startTask(liftTask);
		//}
		//if(vexRT[Btn7L])
		//{
		//	liftgo = 1;
		//	clawTarget = 2000;
		//	liftTarget = 2300;
		//	startTask(clawTask);
		//	startTask(liftTask);
		//}

    if (vexRT[Btn5U] && (SensorValue[liftEnc] < armEncMaxLimit || !enableSoftwareArmPosLimit || vexRT[Btn8U])) {
	  	stopTask(liftComp);
	  	liftCompStarted = false;
	  	setDumpMotors(127);
	  	holdDown = false;
		} else if (vexRT[Btn5D] && !SensorValue[liftDown]) { //second part of condition is to prevent motors from jittering if 5U and 5D are pressed down
			stopTask(liftComp);
			liftCompStarted = false;
			setDumpMotors(-127);
		} else {
			//vertical at 117
			/*if (SensorValue[arm] > 3890) { //arm is all the way down; no compensation power
				setDumpMotors(0);
			} else if (SensorValue[arm] > 1350) { *///arm is up but has not gone past vertical (behind back of robot).  Positive compensation power
				if (SensorValue[liftDown]) {
					holdDown = true;
				}
				if (holdDown || SensorValue[liftEnc] >= 117) {
					stopTask(liftComp);
					liftCompStarted = false;
					setDumpMotors(-12);
				} else if (!liftCompStarted) { //don't restart this task unless the lift has moved
					startTask(liftComp);
					liftCompStarted = true;
				}
			/*} else { //arm is up and behind the back of the robot.  Negative compensation power (and increased compensation power to protect potentiometer from crossing its physical limit and counter momentum)
				setDumpMotors(-armCompPower - 5);
			}*/
		}

  	if (vexRT[Btn6U]) {
			setClawMotors(127);
			clawCompPower = 15;
		} else if (vexRT[Btn6D]) {
			setClawMotors(-127);
			clawCompPower = -20;
		}	else {
			setClawMotors(clawCompPower);
		}

  	wait1Msec(25);
	}
}
