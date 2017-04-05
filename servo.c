/*
 * =====================================================================================
 *
 *       Filename:  servo.c
 *
 *    Description:  zainicjalizowanie serva, wyrzuci³em do oddzielnego pliku bo ³adniej ;)
 *
 *        Version:  1.0
 *        Created:  16/01/17 20:42:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kacper Szmigiel (), szmigielkacper@gmail.com
 *   Organization:  elpire.pl
 *
 * =====================================================================================
 */


#include "mapping.h"

void servo_init(){

	gpioSetMode(SERVO_PIN, PI_OUTPUT);
	gpioServo(SERVO_PIN, 1450);

}
