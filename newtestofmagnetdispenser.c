#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     HTPB,           sensorI2CCustom9V)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorH,        tmotorNone, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorNormal, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//4 arm
//2 ball stopper
#include "JoystickDriver.c"
#include "common.h"
#include "HTAC-driver.h"
#include "HTMAG-driver.h"
#include "HTMC-driver.h"
#include "LEGOLS-driver.h"
#include "LEGOTS-driver.h"
#include "HTPB-driver.h"
#include "HTIRS2-driver.h"
#include "HTGYRO-driver.h"

//

bool control = true;
void initializeRobot()
{

  servo[servo1] = 10; //needs to be this
  servo[servo2] = 10;
  servo[servo3] = 250;
  servo[servo2] = 0;

  return;
}

task magnetSensor()
{

while (true)
{
// servoChangeRate[servo2] = 4;

long inputdata = 2;
  int valtime4 = time1[T4];

  HTPBsetupIO(HTPB, 0x02);
  HTPBwriteIO(HTPB,0x00);

  while (control) {

    // Read sensor from port b5
    inputdata = HTPBreadIO(HTPB, 0x20);// 0x20 is the mask for port b5


    //writeDebugStreamLine("Input Data is: %d", inputdata);

    if (!inputdata) // not found
    {
       HTPBwriteIO(HTPB,0);    // Turn LED on
   // servoChangeRate[servo2] = 1;
  //  servo[servo2] = 50;
    servoChangeRate[servo2] = 5;
    servo[servo2] = 125;     // in down position
    }
    else
    {
      HTPBwriteIO(HTPB,0x02);//  Turn LED off

      servo[servo2] = 0;
      //PlaySound(soundUpwardTones);
      wait1Msec(2000);

    }
     //wait1Msec(50);
  }
}
}

//int threshold = 20;
//bool direction = true;

task main()
{
  initializeRobot();
  waitForStart();

StartTask (magnetSensor);
int threshold = 20;

  while(1)
  {

														    getJoystickSettings(joystick);
														    if(abs(joystick.joy1_y2) > threshold)   // If the right analog stick's Y-axis readings are either above or below the threshold:
														    {
														     // if (direction)
														    motor[motorI] = joystick.joy1_y2;         // Motor B is assigned a power level equal to the right analog stick's Y-axis reading.
														  //    else
														     //   motor[motorG] = joystick.joy1_y2*2/3;
														    }
														    else                                    // Else if the readings are within the threshold:
														    {
														      motor[motorI] = 0;                        // Motor B is stopped with a power level of 0.
														    }


														    if(abs(joystick.joy1_y1) > threshold)   // If the left analog stick's Y-axis readings are either above or below the threshold:
														    {
														  //   if (direction)
														      motor[motorH] = joystick.joy1_y1;         // Motor C is assigned a power level equal to the left analog stick's Y-axis reading.
														 //   else
														 //     motor[motorF] = joystick.joy1_y1*2/3;
														    }
														    else                                    // Else if the readings are within the threshold:
														    {
														      motor[motorH] = 0;                        // Motor C is stopped with a power level of 0.
														    }


    if(abs(joystick.joy2_y1) > threshold)
    {
      motor[motorG] = joystick.joy2_y1;
    }
    else
    {
      motor[motorG] = 0;
    }

    //Ball Pickeruper

    if(abs(joystick.joy2_y2) > threshold)
    {
      motor[motorF] = joystick.joy2_y2;
    }
    else
    {
      motor[motorF] = 0;
    }

 //NEED TO FIND SERVO VALUES *****************************************************************************
/*
     if(joy2Btn(1)) //crate flipper
   servo[servo1] = 30;//90
 else
   servo[servo1] = 124;//90
   if (joy2Btn(3))
     servo[servo1] = 240;//234
      else
     servo[servo1] = 124;//234
//
*/

if(joy1Btn(1))
{
//if(servo[servo1] <= 120)
  servoChangeRate[servo1] = 0;
  servo[servo1] += 1;
}
else if (joy1Btn(3))
{
servoChangeRate[servo1] = 0;
if(servo[servo1] >= 10)
  servo[servo1] -= 1;
}


   if(joy2Btn(2))//Ball holder
   servo[servo3] = 150;//127
   else
     servo[servo3] = 250;//249

      if(joy1Btn(5)) //nxt motors
          motor[motorC] = 100;   // Motor C is run at a power level of 100.
     else if (joy1Btn(7))
      motor[motorC] = -100;
    else
      motor[motorC] = 0;


     // if (joy1Btn(6))
     //   direction = false;
   //   if (joy1Btn(8))
     //   direction = true;

if(joy2Btn(6))
{
control = false;
if(servo[servo2] <= 125)
  servo[servo2] += 1;
}
else if(joy2Btn(8))
{
control = false;
if(servo[servo2] >= 0)
  servo[servo2] -= 1;
}

else if(joy2Btn(1))
 {
  control = false;
  servoChangeRate[servo2] = 5;
  servo[servo2] = 125;
 }
else if(joy2Btn(3))
 {
 control = false;
 servoChangeRate[servo2] = 5;
 servo[servo2] = 0;
 }
else if(joy2Btn(4))
  control = true;


if(joy2Btn(5))
    motor[motorE] = 100;   // Motor C is run at a power level of 100.
  else if (joy2Btn(7))
      motor[motorE] = -100;
    else
      motor[motorE] = 0;


 wait1Msec(10);
  }
}
