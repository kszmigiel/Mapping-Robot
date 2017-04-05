/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  wyjście trzeba przekierować do pliku, który potem obrobi klaster
 *                  robot rusza się po kwadracie 50x50cm, bo do testów używałem kwadratu 1x1m z kartonów (sic!)
 *                  argumenty linkera: -lm -lpigpio -lrt -lpthread
 *
 *        Version:  1.0
 *        Created:  07/03/17 19:57:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kacper Szmigiel, szmigielkacper@gmail.com
 *   Organization:  elpire.pl
 *
 * =====================================================================================
 */

#include "mapping.h"

int posx, posy; //pozycja startowa, środek mapki (zależny od rozmiarów)

int main()
{

    if(gpioInitialise()<0) return 1;

    //inicjalizacja wszystkich peryferiów
    dist_init();
    engine_init();
    servo_init();

    posx = 150; //pozycja startowa dla tablicy 301x301, gdzie 1 jednostka to 1cm w rzeczywistości
    posy = 150;

    //liczniki
    int c1, c2, c3;

    for(c1 = 0; c1 < 4; c1++)
    {
        for(c2 = 0; c2 < 6; c2++)
        {
            for(c3 = -9; c3 < 10; c3++)
            {
                gpioServo(SERVO_PIN, 1450 - (c3 * STEP));
                save_vector(c3, get_distance(), c1);
            }
            forward();
            gpioDelay(500000); //w takim czasie robot przejeżdża 10cm, wyznaczone empirycznie :D
            stop();
            change_pos(c1);
        }
        turn_right();
    }

    return 0;
}

//zmiana pozycji po przejechaniu odcinka, zależnie od kierunku w którym porusza się robot
int change_pos(int direction)
{
    if(direction == 0)
    {
        posy -= 10;
    }
    else if(direction == 1)
    {
        posx += 10;
    }
    else if(direction == 2)
    {
        posy += 10;
    }
    else if(direction == 3)
    {
        posx -= 10;
    }
    else
    {
        return -1;
    }
    return 0;
}

//zapisuje wektor na podstawie kąta pod jakim został wykonany pomiar, wartości pomiaru, i kierunku w jakim zwrócony jest robot
//na koniec wypluwa pozycję i wektor, sklejeniem z tego mapki zajmuje się klaster
int save_vector(int angle, int dist, int direction)
{
    int vector_x, vector_y;
    //kąt w radianach
    double absa = (abs(angle*10) * 3.14159) / 180; //1 krok - 10 stopni
    int s = sin(absa) * dist;
    int c = cos(absa) * dist;

    //pewnie można to było zrobić lepiej, ale działa ;)
    if(direction == 0)
    {
        if(angle < 0)
        {
            vector_x = -1 * s;
            vector_y = -1 * c;
        }
        else if(angle == 0)
        {
            vector_x = 0;
            vector_y = -1 * dist;
        }
        else
        {
            vector_x = s;
            vector_y = -1 * c;
        }
    }

    else if(direction == 1)
    {
        if(angle < 0)
        {
            vector_y = -1 * s;
            vector_x = c;
        }
        else if(angle == 0)
        {
            vector_y = 0;
            vector_x = dist;
        }
        else
        {
            vector_y = s;
            vector_x = c;
        }
    }

    else if(direction == 2)
    {
        if(angle < 0)
        {
            vector_x = s;
            vector_y = c;
        }
        else if(angle == 0)
        {
            vector_x = 0;
            vector_y = dist;
        }
        else
        {
            vector_x = -1 * s;
            vector_y = c;
        }
    }

    else if(direction == 3)
    {
        if(angle < 0)
        {
            vector_y = s;
            vector_x = -1 * c;
        }
        else if(angle == 0)
        {
            vector_y = 0;
            vector_x = -1 * dist;
        }
        else
        {
            vector_y = -1 * s;
            vector_x = -1 * c;
        }
    }
    else
    {
        return -1;
    }

    //konieczne jest przekierowanie wyjścia do pliku, przerobieniem tego na mapkę zajmuje się klaster
    printf("%d %d %d %d\n", posx, posy, vector_x, vector_y);

    return 0;
}
