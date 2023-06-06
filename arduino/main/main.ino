#include <TimerOne.h>
//UNO only

void setup()
{
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);

Timer1.initialize(10);  // Frequency, 100us = 10khz, 10 >>>------> 100KHz
// Timer1.pwm(9,512);       // 50% DC on pin 9
Timer1.pwm(9, 255);
//Timer1.pwm(10,255);    // 25% DC on pin 10

// D.C. 
// 10KHz
// You can use 2 to 1023 
// 0 & 1 gives a constant LOW 
// 1024 gives a constant HIGH
// 2 gives ~125ns HIGH pulses
// 1023 gives ~125ns low pulses
// 512 gives 50us
}

void loop()
{
}