/************************************************************************
This program is the control part in the project


Change Log
2018.4.13       Coding start, set up the framework and some basic definitions.

************************************************************************/

#include<MsTimer2.h>
#include<Servo.h>


//PINs definition
int IN_ELE = 0;  //elevater input
int IN_AIL = 0;  //aileron input
int IN_THR = 0;  //throttle input
int IN_RUD = 0;  //rudder input
int Arduino_SWITCH = 0;  //(de)activate Arduino
int OUT_ELE = 0;  //elevater output
int OUT_AIL = 0;  //aileron output
int OUT_THR = 0;  //throttle output
int OUT_RUD = 0;  //rudder output
int RX = 0;  //

void setup() {
    attachInterrupt(?, Activate_Arduino, RISING);
    attachInterrupt(?, Deactivate_Arduino, FALLING);
    attachInterrupt(?, ReceivingData, RISING);

}

void loop() {
  // put your main code here, to run repeatedly:

}

void Activate_Arduino()
{
    
}

void ReceivingData()
{
    
}

