#pragma config(Motor,  port3,           rightIntake,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           FL,            tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           FR,            tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           BR,            tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           BL,            tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           leftIntake,    tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*------------------------------------------------------

By Wyatt Johnson. Used on robot 1900A of the Woodward Academy Robotics Team

Motor Pin Diagram:
2. LI - left intake motor -- on current cortex, port 2 is broken, so I'm using port 8 for Left Intake fyi
3. RI - right intake motor
4. FL - front left motor
5. FR - front right motor
6. BR - back right motor
7. BL - back left motor
8. LFB - left four-bar motor -- on current cortex, port 2 is broken, so I'm using port 8 for Left Intake fyi
9. RFB - right four-bar motor

Motion / Mechanics Notes

Entire left side is reversed so that robot can go forward
List (FL Speed, BL speed, BR speed, FR) - remember FL and BL are reversed
Forward: 127, 127, 127, 127 - both joysticks forward
Backwards: -127, -127, -127, -127 - both joysticks backwards
Strafe Left: -127, 127, 127, -127 - both joysticks left
Strafe Right: 127, -127, -127, 127 - both joysticks right
Rotate Left: -127, -127, 127, 127 - left joystick down right joystick up
Rotate Right: 127, 127, -127,-127 - left joystick up right joystick down

Intake

6U - intake stars, both intakes 127
6D - release stars? Intake goes opposite direction


------------------------------------------------------*/

int threshold = 15; //minimum joystick value

task main()
{
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

		if(vexRT[Btn6U] == 1){ //if Button 6U is being pressed, intake stars
			motor[rightIntake] = 127;
			motor[leftIntake] = 127;
		}
		else if(vexRT[Btn6D] == 1){ //if button 6D
			motor[rightIntake] = -127;
			motor[leftIntake] = -127;
		}
		else if ((vexRT[Btn6D] == 0) && (vexRT[Btn6U] == 0)){ //if neither butto is begin pressed, turn the motor off
		motor[rightIntake] = 0;
		motor[leftIntake] = 0;
		}
	}
}
