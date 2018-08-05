/* NOTES
Commands need to be adjusted:
1. if(mode_Switch == 1)
2. pin and interrupt No. of mode_Switch
*/

/*______________________________CHANGE LOG______________________________________
August 5, 2018    Main frame finished
*/

#include <Servo.h>

//pins definition
#define AIL1  22
#define ELE2  24
#define THR3  26
#define RUD4  28
#define mode_Switch 30
/*
Here is very important, I set the mode_Switch to ensure the operator can take control of the quad at any moment.
The control of the Arduino and PC might go wrong, so the operator need to take over control immediately once it happens.
*/

//vars definition
unsigned long INAIL;
unsigned long INELE;
unsigned long INTHR;
unsigned long INRUD;

int OUTAIL;
int OUTELE;
int OUTTHR;
int OUTRUD;
int OUT_Motion[OUTTHR, OUTAIL, OUTELE, OUTRUD];

char buffer[4];
char stopSign = ',';

int AILCenter = 1500;
int ELECenter = 1500;
int THRCenter = 1500;
int RUDCenter = 1500;
int Center_Val = [THRCenter, AILCenter, ELECenter, RUDCenter];

int mode = 1;

Servo AIL;
Servo ELE;
Servo THR;
Servo RUD;


void setup()
{
    pinMode(AIL1, INPUT);
    pinMode(ELE2, INPUT);
    pinMode(THR3, INPUT);
    pinMode(RUD4, INPUT);
    pinMode(mode_Switch, INTPUT);

    attachInterrupt(ChangeMode, 2, CHANGE);  //$$

/*
    AIL.attach(4);
    ELE.attach(5);
    THR.attach(6);
    RUD.attach(7);
  */
    Serial.begin(9600);
}


void loop()
{
    if(mode_Switch == 1)
    {
        INAIL = pulseIn(AIL1, HIGH);
        INELE = pulseIn(ELE2, HIGH);
        INTHR = pulseIn(THR3, HIGH);
        INRUD = pulseIn(RUD4, HIGH);

      /*
        OUTAIL = map(INAIL,1010,2007,47,144);
        OUTELE = map(INELE,1010,2007,47,144);
        OUTTHR = map(INTHR,1010,2007,47,144);
        OUTRUD = map(INRUD,1010,2007,47,144);
        */

        AIL.writeMicroseconds(INAIL);
        ELE.writeMicroseconds(OUTELE);
        THR.writeMicroseconds(OUTTHR);
        RUD.writeMicroseconds(OUTRUD);

/*
        Serial.print("AIL=");
        Serial.print(INAIL);
        Serial.print(" ELE=");
        Serial.print(INELE);
        Serial.print(" THR=");
        Serial.print(INTHR);
        Serial.print(" RUD=");
*/
        delay(2);
    }

    else
    {
        if(Serial.available > 0)
        {
            inPutNum = Serial.readBytesUntil(stopSign, buffer, 4);

            //up and down
            if(buffer[0] == 'u')
            {
                OUTTHR = THRCenter + 100;
            }
            else if(buffer[0] == 'd')
            {
                OUTTHR = THRCenter - 100;
            }
            else
            {
                OUTTHR = THRCenter;
            }
            THR.writeMicroseconds(OUTTHR);

            //left and right
            if(buffer[1] == 'l')
            {
                OUTAIL = AILCenter - 100;
            }
            else if(buffer[1] == 'r')
            {
                OUTAIL = AILCenter + 100;
            }
            else
            {
                OUTAIL = AILCenter;
            }
            AIL.writeMicroseconds(OUTAIL);

            //forward and backward
            if(buffer[2] == 'f')
            {
                OUTELE = ELECenter - 100;
            }
            if(buffer[2] == 'b')
            {
                OUTELE = ELECenter + 100;
            }
            ELE.writeMicroseconds(OUTELE);

            //RUD
            if(buffer[3] == 't')
            {
                OUTRUD = RUDCenter - 100;
            }
            if(buffer[3] == 'c')
            {
                OUTRUD = RUDCenter + 100;
            }
            RUD.writeMicroseconds(OUTRUD);

/*      another way
            for(i=0;i<4;i++)
            {
                if(buffer[i] == '0')
                {
                    OUT_Motion[i] = Center_Val[i];
                }
                else if(buffer[i] == '1')
                {
                    OUT_Motion[i] = Center_Val[i] + 100;
                }
                else
                {
                    OUT_Motion[i] = Center_Val[i] - 100;
                }
            }
            THR.writeMicroseconds(OUT_Motion[0]);
            AIL.writeMicroseconds(OUT_Motion[1]);
            ELE.writeMicroseconds(OUT_Motion[2]);
            RUD.writeMicroseconds(OUT_Motion[3]);
*/
        }
        if(Serial.available == 0)
        {
            THR.writeMicroseconds(Center_Val[0]);
            AIL.writeMicroseconds(Center_Val[1]);
            ELE.writeMicroseconds(Center_Val[2]);
            RUD.writeMicroseconds(Center_Val[3]);
        }
    }
}

void ChangeMode()
{
    mode_Switch = !mode_Switch;
}
