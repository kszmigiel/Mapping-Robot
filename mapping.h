/*
 * =====================================================================================
 *
 *       Filename:  incl.h
 *
 *    Description:  piny wg. BCM dla RPi B+
 *
 *        Version:  1.0
 *        Created:  07/03/17 19:25:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kacper Szmigiel (), szmigielkacper@gmail.com
 *   Organization:  elpire.pl
 *
 * =====================================================================================
 */

#ifndef INCLUDED
#define INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include <math.h>

//czujnik odległości
#define SONAR_TRIGGER 17
#define SONAR_ECHO 27
#define SIZE 20 //rozmiar tablicy w której przechowywane są pomiary

//silniki
#define ENG1 8
#define ENG2 24

#define PWM1 10
#define PWM2 9

#define SPEED1 150  //różnica wynika z niedokładności silników w robocie
#define SPEED2 168

//servo
#define SERVO_PIN 22
#define STEP 94 //wartość o jaką należy zmienic wypełnienie, żeby servo zmieniło kąt o 10 stopni

//czujnik odległości
void sonarTrigger(void);
void sonarEcho(int gpio, int level, uint32_t tick);
int compare(const void * a, const void * b);
int get_distance();
void dist_init();

//silniki
void engine_init();
void forward();
void stop();

//servo
void servo_init();

#endif
