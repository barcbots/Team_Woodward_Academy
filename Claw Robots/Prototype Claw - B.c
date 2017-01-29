#pragma config(Sensor, in1,    arm,            sensorPotentiometer)
#pragma config(Sensor, in2,    claw,           sensorPotentiometer)
#pragma config(Sensor, in3,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  rDriveEnc,      sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  lDriveEnc,      sensorQuadEncoder)
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

#include "autonomousLib.c"
//setDumpMotors and setClawMotors are in autonomousLib.c

//potentiometer value for lift: 2150
int liftTarget;
int clawTarget;
task liftTask()
{
	liftToPotTarget(liftTarget,127);
}
task clawTask()
{
	moveClaw(127,clawTarget);
}
task autonomous() {
	liftTarget = 2150;
	clawTarget = 1000;//A
	startTask(liftTask);
	startTask(clawTask);
	diagonalLeft(127,160);
	waitForLift(2150,50);
	waitForClaw(1000,50);//A
	wait1Msec(250);
	straight(127,600);
	wait1Msec(125);
	straight(-127,100);
	//point turn
	//lift down
	//wait
	//strafe
	//wait
	//close
	//wait
	//raise arm
	//wait a short amount of time
	//open claw
	//wait
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

task clawControl()
{
     int PIDTargetValue;
     float kp = 0.5; //these constants might change down the road, but they are good for now
     float ki = 0.01;
     float kd = 0.00001;
     int error;
     int integral = 0;
     int derivative;
     int lastError;
     int PIDDrive;
     while(true)
     {
          if(vexRT[Btn6U]) //opens claw
          {
               setClawMotors(127);
               PIDTargetValue = SensorValue[claw];
          }
          else if(vexRT[Btn6D]) //closes claw
          {
               setClawMotors(-127);
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
task main()
{
	//startTask(autonomous);
	//stopTask(main);
	//setClawMotors(127);
	//wait1Msec(750);
	//setClawMotors(-127);
	//wait1Msec(400);
	startTask(clawControl); //simple control and PID for compensation on claw

	int LY = 0;
	int LX = 0;
	int RY = 0;
	int RX = 0;
	int threshold = 15;
	int armCompPower = 12; //compensation power for arm/lift
	int armPotMaxLimit = 620; //software limit for potentiometer to limit arm movement from going over the top (protects potentiometer)
	bool enableSoftwareArmPosLimit = true; //experimental software limit for arm, see above
	//int clawCompPower = 15
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

  	//untested
	  if (vexRT[Btn5U] && (SensorValue[arm] > armPotMaxLimit || !enableSoftwareArmPosLimit)) {
	  	setDumpMotors(127);
		} else if (vexRT[Btn5D]) { //second part of condition is to prevent motors from jittering if 5U and 5D are pressed down
			setDumpMotors(-127);
		} else {
			if (SensorValue[arm] > 3700) { //arm is all the way down; no compensation power
				setDumpMotors(0);
			} else if (SensorValue[arm] > 1400) { //arm is up but has not gone past vertical (behind back of robot).  Positive compensation power
				setDumpMotors(armCompPower);
			} else { //arm is up and behind the back of the robot.  Negative compensation power (and increased compensation power to protect potentiometer from crossing its physical limit and counter momentum)
				setDumpMotors(-armCompPower);
			}
		}

  	/*if (vexRT[Btn6U]) {
			setClawMotors(127);
			clawCompPower = 15;
		} else if (vexRT[Btn6D]) {
			setClawMotors(-127);
			clawCompPower = -20;
		}	else {
			setClawMotors(clawCompPower);
		}*/

  	wait1Msec(25);
	}
}
