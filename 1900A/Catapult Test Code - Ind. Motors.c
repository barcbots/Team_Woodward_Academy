#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           rightCatBottom, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           rightCatTop,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           FL,            tmotorVex393TurboSpeed_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port5,           FR,            tmotorVex393TurboSpeed_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port6,           BR,            tmotorVex393TurboSpeed_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port7,           BL,            tmotorVex393TurboSpeed_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port9,           leftCatTop,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          leftCatBottom, tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


/*------------------------------------------------------


Motion / Mechanics Notes

Entire left side is reversed so that robot can go forward
List (FL Speed, BL speed, BR speed, FR) - remember FL and BL are reversed
Forward: 127, 127, 127, 127 - both joysticks forward
Backwards: -127, -127, -127, -127 - both joysticks backwards
Strafe Left: -127, 127, 127, -127 - both joysticks left
Strafe Right: 127, -127, -127, 127 - both joysticks right
Rotate Left: -127, -127, 127, 127 - left joystick down right joystick up
Rotate Right: 127, 127, -127,-127 - left joystick up right joystick down

Controls -

6D/6U - arms go up/down
5D/5U - arm hooks rotate
8C - wind down catapult
8D - release catapult
*Possible* - 7D - extend hook // 7L - retract hook

------------------------------------------------------*/

// Speed Values
const int threshold = 15; //minimum joystick value
const int holdArmSpeed = 20; //motor will hold this value to hold arm at certain level
const int catSpeed = 100;


task main()
{
	//Assign some starter values to the four movement integers
	int LY = 0;
	int LX = 0;
	int RY = 0;
	int RX = 0;

	while(true )
	{
		/*
		Ternary Statement: value = (true boolean) ? (false boolean) : value
		If the absolute value of one of these vexRT Channels is greater than the threshold, assign the value
		If it is NOT greater than threshold, make it 0
		*/
		LX = (abs(vexRT[Ch4]) > threshold) ? vexRT[Ch4] : 0;
		LY = (abs(vexRT[Ch3]) > threshold) ? vexRT[Ch3] : 0;
		RY = (abs(vexRT[Ch2]) > threshold) ? vexRT[Ch2] : 0;
		RX = (abs(vexRT[Ch1]) > threshold) ? vexRT[Ch1] : 0;

		motor[FL] = LY + LX;
		motor[FR] = RY - RX;
		motor[BR] = RY + RX;
		motor[BL] = LY - LX;

		if(vexRT[Btn5U] == 1){ //temporary drive controls
			motor[leftCatTop] = catSpeed;
			motor[leftCatBottom] = catSpeed;
			motor[rightCatTop] = catSpeed;
			motor[rightCatBottom] = catSpeed;
		}
		else if (vexRT[Btn5d] == 1){
			motor[leftCatTop] = -catSpeed;
			motor[leftCatBottom] = -catSpeed;
			motor[rightCatTop] = -catSpeed;
			motor[rightCatBottom] = -catSpeed;
	}
		else {
			motor[leftCatTop] = 0;
			motor[leftCatBottom] = 0;
			motor[rightCatTop] = 0;
			motor[rightCatBottom] = 0;
		}

	}
}