/*
 * =====================================================================================
 *
 *       Filename:  odl2.c
 *
 *    Description:  Obs³uga HC-SR04
 *
 *        Version:  1.0
 *        Created:  04/03/17 23:44:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kacper Szmigiel (), szmigielkacper@gmail.com
 *   Organization:  elpire.pl
 *
 * =====================================================================================
 */

#include "mapping.h"

int dist;

//inicjaizowanie czujnika odleg³oœci
void dist_init()
{
    gpioSetMode(SONAR_TRIGGER, PI_OUTPUT);
    gpioWrite  (SONAR_TRIGGER, PI_OFF);
    gpioSetMode(SONAR_ECHO,    PI_INPUT);
    gpioSetAlertFunc(SONAR_ECHO, sonarEcho);
}


//te dwie funkcje podebra³em z http://abyz.co.uk/rpi/pigpio/ex_sonar_ranger.html i trochê zmodyfikowa³em pod swoje potrzeby
void sonarTrigger(void)
{
    /*  trigger a sonar reading */

    gpioWrite(SONAR_TRIGGER, PI_ON);

    gpioDelay(10); /*  10us trigger pulse */

    gpioWrite(SONAR_TRIGGER, PI_OFF);
}

void sonarEcho(int gpio, int level, uint32_t tick)
{
    static uint32_t startTick;

    int diffTick;

    if (level == PI_ON)
    {
        startTick = tick;
    }
    else if (level == PI_OFF)
    {
        diffTick = tick - startTick;

        dist = (diffTick * 17150) / 1000000;
    }
}

//funkcja porównuj¹ca dla qsorta
int compare (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}


int get_distance()
{
    int tab[SIZE];
    int counter;

    //pobranie 20 pomiarów
    for(counter = 0; counter < SIZE; counter++)
    {
        sonarTrigger();
        gpioDelay(100000);
        tab[counter] = dist;
    }

    //uporz¹dkowanie rosn¹co
    qsort(tab, SIZE, sizeof(int), compare);
    int sum = 0;

    //obciêcie dwóch skrajnych wyników i wyliczenie œredniej
    for(counter = 2; counter < SIZE-2; counter++)
    {
        sum += tab[counter];
    }
    int wynik = sum / (SIZE-4);
    return wynik;
}
