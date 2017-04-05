/*
 * =====================================================================================
 *
 *       Filename:  engine.c
 *
 *    Description:  Biblioteka do obsługi silników DC w robocie
 *
 *        Version:  1.0
 *        Created:  22/02/17 14:49:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kacper Szmigiel (), szmigielkacper@gmail.com
 *   Organization:  elpire.pl
 *
 * =====================================================================================
 */

#include "mapping.h"

void engine_init()
{

    //regulacja prędkości silników
    gpioSetMode(PWM1, PI_OUTPUT);
    gpioSetMode(PWM2, PI_OUTPUT);
    gpioPWM(PWM1, SPEED1);
    gpioPWM(PWM2, SPEED2);

    //sterowanie silnikami
    gpioSetMode(ENG1, PI_OUTPUT);
    gpioSetMode(ENG2, PI_OUTPUT);
    gpioSetMode(6, PI_OUTPUT);
    gpioSetMode(4, PI_OUTPUT);
}


void forward()
{
    gpioWrite(ENG1, 1);
    gpioWrite(ENG2, 1);
}

void stop()
{
    gpioWrite(ENG1, 0);
    gpioWrite(ENG2, 0);
}

void turn_right()
{
    gpioWrite(ENG1, 1);
    gpioDelay(40000);w
    gpioWrite(ENG1, 0);
}
