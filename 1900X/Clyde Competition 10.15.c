#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    catapultPot,    sensorPotentiometer)
#pragma config(Sensor, in2,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  platformLock,   sensorDigitalOut)
#pragma config(Sensor, dgtl2,  drumPosEnc,     sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  platformDown,   sensorTouch)
#pragma config(Sensor, dgtl5,  drumZero,       sensorTouch)
#pragma config(Sensor, dgtl6,  drumRatchet,    sensorDigitalOut)
#pragma config(Sensor, dgtl7,  tongue,         sensorDigitalOut)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           lDriveFront,   tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port3,           lDriveBack,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           rCatapult23,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rCatapult1,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           lCatapult1,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           lCatapult23,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           rDriveBack,    tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           rDriveFront,   tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_2)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//platformLock - 0 = out, 1 = in
//tongue - 0 = in, 1 = out
//drumRatchet - 0 = up, 1 = down


// This code is for the VEX cortex platform
#pragma platform(VEX2)
bool DEBUG_ENABLE = true;

// Select Download method as "competition"
//ENABLE THIS LATER
//#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "..\Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	bDisplayCompetitionStatusOnLcd = false;
	bLCDBacklight = true;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

	//gyro calibration
	//wait1Msec(2000);
}

const int UP = 1;
const int DOWN = 0;


//fundamental movement functions
void setDrumMotors (float power) {
	motor[lCatapult1] = power;
	motor[lCatapult23] = power;
	motor[rCatapult1] = power;
	motor[rCatapult23] = power;
}

void setLeftDtMotors(float lFront, float lBack) {
	motor[lDriveFront] = lFront;
	motor[lDriveBack] = lBack;
}

void setRightDtMotors(float rFront, float rBack) {
	motor[rDriveFront] = rFront;
	motor[rDriveBack] = rBack;
}


//CATAPULT SPECIFIC
//if pos is 0(DOWN), the ratchet will be down
//if pos is 1 (UP), the ratchet will be released, which may require moving the catapult down briefly to release the ratchet
void setRatchetPos(int pos) {
	if (pos == 1) {
		setDrumMotors(127);
		wait1Msec(250);
		SensorValue[drumRatchet] = 0;
		wait1Msec(250);
		setDrumMotors(0);
	} else { //pos == 0
		SensorValue[drumRatchet] = 1;
	}
}

//full rev = 360*7
//automatically releases ratchet first
void moveCatapultDrumDist (int count, int direction) {
	int target;
	if (direction == DOWN) {
		setRatchetPos(DOWN);
		target = SensorValue[drumPosEnc] + count;
		writeDebugStreamLine("down target: %d",target);
		while(SensorValue[drumPosEnc] < target) {
			setDrumMotors(127);
			wait1Msec(25);
		}
	} else { //direction == UP
		//move the catapult down a little to release the ratchet
		setRatchetPos(UP);
		//move drum as requested
		target = SensorValue[drumPosEnc] - count;
		writeDebugStreamLine("up target %d",target);
		while(SensorValue[drumPosEnc] < target) {
			setDrumMotors(-127);
			wait1Msec(25);
		}
	}
	setDrumMotors(0);
}

void resetDrumPosition() {
	setRatchetPos(1);
	wait1Msec(1000); //one second to make sure the human has lifted the ratchet
	while (!SensorValue[drumZero] || SensorValue[drumPosEnc] > 100) {
		setDrumMotors(-127);
	}
	setDrumMotors(0);
	SensorValue[drumPosEnc] = 0;
}

void runDebugCode() {
	writeDebugStreamLine("Encoder start position: %d",SensorValue[drumPosEnc]);
	moveCatapultDrumDist(DOWN, 340);
	writeDebugStreamLine("Encoder end position: %d",SensorValue[drumPosEnc]);
}

int catapultPositions[4];



void catapultInit() {
	catapultPositions[0] = 0;
	catapultPositions[1] = 2000;
	catapultPositions[2] = 2300;
	catapultPositions[3] = 2500;
}

void setCatapultPosition(int pos) {
	if (pos == 0) {
		resetDrumPosition();
	} else {
		int currPos = SensorValue[drumPosEnc];
		int desiredPos = catapultPositions[pos];
		writeDebugStreamLine("Catapult desired position: %d",desiredPos);
		writeDebugStreamLine("Current enc val: %d",SensorValue[drumPosEnc]);
		int distReq = desiredPos - currPos;
		writeDebugStreamLine("Dist req: %d",distReq);
		if (distReq < 0) { // move UP
			moveCatapultDrumDist(abs(distReq), UP);
		} else if (distReq > 0) {
			moveCatapultDrumDist(abs(distReq),DOWN);
		}
	}
}

void prepareCatapult() {
	if (!SensorValue[platformDown] || SensorValue[drumPosEnc] > 15) { //if the platform is not down, get the platform down first
		//add potentiometer check
		resetDrumPosition(); //reset the drum to lower the platform
	} else {

	}
}

void fireCatapult() {
	if (SensorValue[drumPosEnc] > 100) {
		SensorValue[tongue] = 0; //move the tongue in before shooting; it will stay out until the platform is all the way up
		SensorValue[platformLock] = 1; //release the platform to fire objects

    bool catapultUpTimedOut = false;
    int catapultTimeOutTime = 3000; //in milliseconds; wait 3 seconds at most for the catapult to go all the way up
    time1[T1] = 0; //start timing how long we've been waiting for the catapult to go all the way up
		while(SensorValue[catapultPot] < 2550) { //when the catapult is up - CHECK VAL
			if (time1[T1] > catapultTimeOutTime) {
				catapultUpTimedOut = true;
				break; //exit this while loop
			}
			wait1Msec(25);
		}

		//once catapult is up, start resetting the drum
		resetDrumPosition();

		if (!catapultUpTimedOut) { //if catapult up didn't time out
			time1[T1] = 0;
			int catapultResetTimeOutTime = 7000; //check this value
			while (!SensorValue[platformDown] || SensorValue[catapultPot] > 2550) { //when platform is attached and catapult is down, move one; CHECK VAL
				if (time1[T1] > catapultResetTimeOutTime) {
					break; //exit this while loop
				}
				wait1Msec(25);
			}
		}

		//if either wait operation times out, the catapult will stop moving and the platform solenoid will extend out; the variable platform released is not used
		SensorValue[platformLock] = 0; //reattach platform
		SensorValue[tongue] = 1;

		}

}


task driverCatapult() {
	while(1) {
	if (vexRT[Btn8U]) {
			//prepareCatapult();
		} else if (vexRT[Btn8D]) {
			fireCatapult();
		}
		wait1Msec(25);
	}
}

#include "Clyde Auton 10.15.c"

task autonomous()
{
	startTask(auton);

}

const bool DEBUG_AUTON = false;

task usercontrol()
{
	catapultInit();
	startTask(driverCatapult);
	if (DEBUG_AUTON) {
		startTask(autonomous);
		stopTask(usercontrol);
	}
	//resetDrumPosition();
	bLCDBacklight = true;
	clearLCDLine(0);
	int LY = 0;
	int LX = 0;
	int RY = 0;
	int RX = 0;
	int threshold = 15;
	while (1) {
		displayLCDNumber(0,1,SensorValue[drumPosEnc],1);
		displayLCDNumber(1,0,SensorValue[drumZero],1);
		/*if (vexRT[Btn8U]) {
			setDrumMotors(-127);
		} else if (vexRT[Btn8D]) {
			setDrumMotors(127);
		} else {
			setDrumMotors(0);
		}*/

		//8U - reset
		if (vexRT[Btn7D] == 1) {
		  setCatapultPosition(1);
		} else if (vexRT[Btn7L] == 1) {
			setCatapultPosition(2);
		} else if (vexRT[Btn7R] == 1) {
			setCatapultPosition(3);
		}

		//platform lock
		if (vexRT[Btn5U]) {
			SensorValue[platformLock] = 0;
		} else if (vexRT[Btn5D]) {
			SensorValue[platformLock] = 1;
		}

		//tongue
		if (vexRT[Btn6U]) {
			SensorValue[tongue] = 0;
		} else if (vexRT[Btn6D]) {
			SensorValue[tongue] = 1;
		}

		if (vexRT[Btn8L]) {
			SensorValue[drumRatchet] = 0;
		} else if (vexRT[Btn8R]) {
			SensorValue[drumRatchet] = 1;
		}




		//for deadzones; when the joystick value for an axis is below the threshold, the motors controlled by that joystick will not move in that direction
		LY = (abs(vexRT[Ch3]) > threshold) ? vexRT[Ch3] : 0;
		LX = (abs(vexRT[Ch4]) > threshold) ? vexRT[Ch4] : 0;
		RY = (abs(vexRT[Ch2]) > threshold) ? vexRT[Ch2] : 0;
		RX = (abs(vexRT[Ch1]) > threshold) ? vexRT[Ch1] : 0;
		motor[lDriveFront] = LY + LX;
		motor[lDriveBack] = LY - LX;
		motor[rDriveFront] = RY - RX;
		motor[rDriveBack] = RY + RX;
		wait1Msec(20);

	}
}
