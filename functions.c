/**
 * @file functions.c
 * @brief This file contains all functions to be used by
 * the competition code.
 *
 * @warning DO NOT compile this file
 * by itself, it will not work. Instead, save it
 * and compile main.c
 *
 * @authors		Sean Kelley     sgtkode01@gmail.com
 *				Bernard Suwirjo bsuwirjo@gmail.com
 */

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 GLOBAL VARIABLES
//
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 DRIVETRAIN
//
/////////////////////////////////////////////////////////////////////////////////////////

/**
* @void drive
*
* @desc gives drive control to VexNET controller
*
* @args  half boolean  determines if motors should be running at half speed
*/
void drive(bool half)
{

			if (half==false)//Check if drive toggles half speed.
			{
				motor[BR] = vexRT[Ch2]; //give drive direct control.
				motor[FR] = vexRT[Ch2];
				motor[BL] = vexRT[Ch3];
				motor[FL] = vexRT[Ch3];
			}
			else if(half ==true)
			{
				motor[BR] = vexRT[Ch2]/3;//give drive control but all motor maxes are a third of their orignal max.
				motor[FR] = vexRT[Ch2]/3;
				motor[BL] = vexRT[Ch3]/3;
				motor[FL] = vexRT[Ch3]/3;
			}
}


/**
* @void clearMotor
*
* @desc clears all the motors
*
* @args  N/A
*/
void clearMotor()
{
	motor[FR]=0;
	motor[BR]=0;
	motor[FL]=0;
	motor[BL]=0;
}

/**
* @void motorcheck
*
* @desc runs each motor for 1.5 seconds
*
* @args  N/A
*/
void motorcheck()
{
	motor[FR]=118;
	wait(1.5);
	clearMotor();
	motor[BR]=118;
	wait(1.5);
	clearMotor();
	motor[FL]=118;
	wait(1.5);
	clearMotor();
	motor[BL]=118;
	wait(1.5);
	clearMotor();
}

/**
* @void fullStop
*
* @desc completely stops all motors without drift
*
* @args  N/A
*/
void fullStop(int x=118,int direction=0, bool fancy=false)
{
	if(fancy)
	{
		if(direction==1)
		{
			int FR = x;
			int FL = 0;
			int BR = x;
			int BL = 0;
			motor[FR]=FR*-.1;
			motor[FL]=FL*-.1;
			motor[BR]=BR*-.1;
			motor[BL]=BL*-.1;
			wait1Msec(150);
			clearMotor();
		}
		else if(direction==2)
		{
			int FR = 0;
			int FL = x;
			int BR = 0;
			int BL = x;
			motor[FR]=FR*-.1;
			motor[FL]=FL*-.1;
			motor[BR]=BR*-.1;
			motor[BL]=BL*-.1;
			wait1Msec(150);
			clearMotor();
		}
	}
	else
	{
		if(direction==1)
		{
			int FR = x;
			int FL = -x;
			int BR = x;
			int BL = -x;
			motor[FR]=FR*-.1;
			motor[FL]=FL*-.1;
			motor[BR]=BR*-.1;
			motor[BL]=BL*-.1;
			wait1Msec(150);
			clearMotor();
		}
		else if(direction==2)
		{
			int FR = -x;
			int FL = x;
			int BR = -x;
			int BL = x;
			motor[FR]=FR*-.1;
			motor[FL]=FL*-.1;
			motor[BR]=BR*-.1;
			motor[BL]=BL*-.1;
			wait1Msec(150);
			clearMotor();
		}
		else
		{
			int FR = x;
			int FL = x;
			int BR = x;
			int BL = x;
			motor[FR]=FR*-.1;
			motor[FL]=FL*-.1;
			motor[BR]=BR*-.1;
			motor[BL]=BL*-.1;
			wait1Msec(150);
			clearMotor();
		}
	}
}



/**
* @void forwardSeconds
*
* @desc moves bot forward for a given amount of seconds
*
* @args  s  int    amount of seconds to move forward
				 x  float  speed of motors
*/
void forwardSeconds(float s,float x=118)
{
  motor[FL]=x;
	motor[FR]=x;
	motor[BL]=x;
	motor[BR]=x;
	wait1Msec(s*1000);
	fullStop(x);
}

/**
* @void backwardSeconds
*
* @desc moves bot backwards for a given amount of seconds
*
* @args  s  int    amount of seconds to move forward
*				 x  float  speed of motors
*/
void backwardSeconds(float s, float x=118)
{
  motor[FL]=-x;
	motor[FR]=-x;
	motor[BL]=-x;
	motor[BR]=-x;
	wait1Msec(s*1000);
	fullStop(x);
}

/**
* @task lockLeftSide
*
* @desc locks left side motors with PI loop
*
* @args  N/A
*/
/*
task lockLeftSide()
{
	float target = 0;
	float pGain = .3;
	float iGain = .02;
	float error = target-SensorValue[encoderLeft];
	float errorSum=0;
	while(true){
		error=target-SensorValue[encoderLeft];
		errorSum+=error;
		motor[FL] = error*pGain+errorSum*iGain;
		  motor[BL] = error*pGain+errorSum*iGain;
	}
}
*/
/**
* @task lockRightSide
*
* @desc locks right side motors with PI loop
*
* @args  N/A
*/
/*
task lockRightSide()
{
	float target = 0;
	float pGain = .3;
	float iGain = .02;
	float error = target-SensorValue[encoderRight];
	float errorSum=0;
	while(true){
		error=target-SensorValue[encoderRight];
		errorSum+=error;
		motor[FR] = error*pGain+errorSum*iGain;
	  motor[BR] = error*pGain+errorSum*iGain;
	}
}
*/
/**
* @void fancyTurnRightDegrees
*
* @desc turns bot right only using left side motors
*
* @args  degrees   int     amount of degrees to turn right
*        forward   bool    boolean if bot is turning forward or backward
*        x         int     speed of motors
*/
void fancyTurnRightDegrees(int degrees, bool forward=true, int x=80)
{
	// reset encoders
	degrees=degrees*10;
	// reset gyro
	SensorValue[gyro]=0;

	// lock the right side motors
	//startTask(lockRightSide);

	// turn forwards or backwards based on forward boolean
	if(forward)
	{
		while(abs(SensorValue[gyro]) < degrees)
		{
			motor[FL] = x;
		    motor[BL] = x;
		}
		motor[FL] = -10;
		motor[BL] = -10;
		wait1Msec(150);
		motor[FL] = 0;
		motor[BL] = 0;
	}
	else
	{
		while(abs(SensorValue[gyro]) < degrees)
		{
			motor[FL] = -x;
		    motor[BL] = -x;
		}
		motor[FL] = 10;
	  motor[BL] = 10;
	  wait1Msec(150);
	  motor[FL] = 0;
	  motor[BL] = 0;
	}

	// unlock the right side motors
	//stopTask(lockRightSide);
}

/**
* @void fancyTurnLeftDegrees
*
* @desc turns bot left only using left side motors
*
* @args  degrees   int     amount of degrees to turn left
*        forward   bool    boolean if bot is turning forward or backward
*        x         int     speed of motors
*/
void fancyTurnLeftDegrees(int degrees, bool forward=true, int x=80)
{
	// reset encoders
	degrees=degrees*10;
	// reset gyro
	SensorValue[gyro] = 0;

	// lock the left side motors
	//startTask(lockLeftSide);

	// turn forwards or backwards based on forward boolean
	if(forward)
	{
		while(abs(SensorValue[gyro]) < degrees)
		{
			motor[FR] = x;
		    motor[BR] = x;
		}
		motor[FR] = -10;
		motor[BR] = -10;
		wait1Msec(150);
		motor[FR] = 0;
		motor[BR] = 0;
	}
	else
	{
		while(abs(SensorValue[gyro]) < degrees)
		{
			motor[FR] = -x;
		    motor[BR] = -x;
		}
		motor[FR] = 10;
		motor[BR] = 10;
		wait1Msec(150);
		motor[FR] = 0;
		motor[BR] = 0;
	}
// unlock the left side motors
//stopTask(lockLeftSide);
}






/**
* @void turnRightDegrees
*
* @desc turns bot right a given amount of degrees
*
* @args  degree  int    amount of degrees to turn right
*				 x       float  speed of motors
*/
void turnRightDegrees(float degree, float x=90)
{
	SensorValue[gyro]=0;
	degree=degree*10;
	float first=degree*.6;



	while(abs(SensorValue[gyro]) < first)
	{
		/*if( abs(SensorValue[encoderLeft]) >= abs(SensorValue[encoderRight])+5 ){
			motor[FL]=x*.8;
    	motor[FR]=-x;
    	motor[BL]=x*.8;
    	motor[BR]=-x;
		} else if( abs(SensorValue[encoderRight]) >= abs(SensorValue[encoderLeft])+5 ){
			motor[FL]=x;
    	motor[FR]=-x*.8;
    	motor[BL]=x;
    	motor[BR]=-x*.8;
		} else {*/
			motor[FL] = x;
        	motor[FR] = -x;
        	motor[BL] = x;
        	motor[BR] = -x;
		//}
	}
	while(abs(SensorValue[gyro]) <degree)
	{
		if(x*.35<40)
		{
			motor[FL] = 40;
        	motor[FR] = -40;
        	motor[BL] = 40;
        	motor[BR] = -40;
		}
		else
		{
			/*if( abs(SensorValue[encoderLeft]) >= abs(SensorValue[encoderRight])+5 ){
				motor[FL]=x*.4*.8;
	    	motor[FR]=-x*.4;
	    	motor[BL]=x*.4*.8;
	    	motor[BR]=-x*.4;
			} else if( abs(SensorValue[encoderRight]) >= abs(SensorValue[encoderLeft])+5 ){
				motor[FL]=x*.4;
	    	motor[FR]=-x*.4*.8;
	    	motor[BL]=x*.4;
	    	motor[BR]=-x*.4*.8;
			} else {*/
				motor[FL] = x*.35;
    	    	motor[FR] = -x*.35;
    	    	motor[BL] = x*.35;
    	    	motor[BR] = -x*.35;
			//}
    }
	}
  //fullStop();
	clearMotor();
}

/**
* @void turnLeftDegrees
*
* @desc turns bot left a given amount of degrees
*
* @args  degree  int    amount of degrees to turn left
*				 x       float  speed of motors
*/
void turnLeftDegrees(float degree, float x=90)
{
	SensorValue[gyro]=0;
	degree=degree*10;
	float first=degree*.6;




	while(abs(SensorValue[gyro]) < first)
	{
			/*if( abs(SensorValue[encoderLeft]) >= abs(SensorValue[encoderRight])+5 ){
				motor[FL]=-x*.8;
	    	motor[FR]=x;
	    	motor[BL]=-x*.8;
	    	motor[BR]=x;
			} else if( abs(SensorValue[encoderRight]) >= abs(SensorValue[encoderLeft])+5 ){
				motor[FL]=-x;
	    	motor[FR]=x*.8;
	    	motor[BL]=-x;
	    	motor[BR]=x*.8;
			} else {*/
				motor[FL] = -x;
	    	    motor[FR] = x;
	    	    motor[BL] = -x;
	    	    motor[BR] = x;
			//}
	}
	while(abs(SensorValue[gyro]) < degree)
	{
		if(x*.35<40)
		{
			motor[FL] = -40;
    	    motor[FR] = 40;
    	    motor[BL] = -40;
    	    motor[BR] = 40;
		}
		else
		{
			/*if( abs(SensorValue[encoderLeft]) >= abs(SensorValue[encoderRight])+5 ){
				motor[FL]=-x*.4*.8;
	    	motor[FR]=x*.4;
	    	motor[BL]=-x*.4*.8;
	    	motor[BR]=x*.4;
			} else if( abs(SensorValue[encoderRight]) >= abs(SensorValue[encoderLeft])+5 ){
				motor[FL]=-x*.4;
	    	motor[FR]=x*.4*.8;
	    	motor[BL]=-x*.4;
	    	motor[BR]=x*.4*.8;
			} else {*/
				motor[FL] = -x*.35;
	    	    motor[FR] = x*.35;
	    	    motor[BL] = -x*.35;
	    	    motor[BR] = x*.35;
			//}
    }
	}
  //fullStop();
	clearMotor();
}


/**
* @void turnRightSeconds
*
* @desc turns bot right a given amount of seconds
*
* @args  seconds   int    amount of seconds to turn right
*				 x         float  speed of motors
*/
void turnRightSeconds(float seconds, float x=118)
{
	motor[FL]=x;
	motor[BL]=x;
	motor[FR]=-x;
	motor[BR]=-x;
	wait1Msec(seconds*1000);
	fullStop();
}

/**
* @void turnLeftSeconds
*
* @desc turns bot left a given amount of seconds
*
* @args  seconds   int    amount of seconds to turn left
*				 x         float  speed of motors
*/
void turnLeftSeconds(float seconds, float x=118)
{
	motor[FL] = -x;
	motor[BL] = -x;
	motor[FR] = x;
	motor[BR] = x;
	wait1Msec(seconds*1000);
	fullStop();
}

