#include <stdio.h>
#include "airport_header.h"
#include <stdlib.h>
#include <time.h>

void initializer(int srt, float elpu, float etpu)
{
    SIM_RUN_TIME = srt;
    EXPECTED_TAKEOFF_PER_UNIT = etpu;
    EXPECTED_LANDING_PER_UNIT = elpu;
    HEAD_LAND = NULL;
    HEAD_TO = NULL;
    TAIL_LAND = NULL;
    TAIL_TO = NULL;
    AIRCRAFT_NUM = 1;
    RUNWAY_STATUS = 0;
    //srand(time(0));
    return;
}

//Generates Unique aircraft
AIRCRAFT aircraft_generator()
{
    AIRCRAFT PLANE;
    PLANE.aircraft_num = AIRCRAFT_NUM++;
    PLANE.status = rand() % 2;
    if (PLANE.status == 0)
        PLANE.fuel_remaining = rand() % (SIM_RUN_TIME) + 1;
    PLANE.queue_wait_time = 0;
    return PLANE;
}

void queue_generator()
{
    //srand(time(0));
    int generate_queue_aircraft = rand() % 4; //Generates UPTO 5 random aircrafts
    AIRCRAFT temp;
    for (int iterate = 0; iterate < generate_queue_aircraft; iterate++)
    {
        temp = aircraft_generator();
        if (temp.status == 0)
            landing_queue_add(temp);
        else if (temp.status == 1)
            takeoff_queue_add(temp);
    }
}

void main_loop()
{
    queue_generator();
    int idletime = 0;
    for (int i = 0; i < SIM_RUN_TIME; i++)
    {
        printf("%d:\n", i + 1);
        if (HEAD_TO == NULL && HEAD_LAND == NULL)
        {
            RUNWAY_STATUS = 0;
            printf("Runway Idle.\n");
            idletime++;
        }
        else
        {
            RUNWAY_STATUS = 1;
            if (HEAD_LAND == NULL)
            {
                takeoff_queue_remove();
            }
            else
            {
                landing_queue_remove();
            }
        }
        increase_queue_wait_time();
        queue_generator();
    }
}

void increase_queue_wait_time()
{
    LANDING *temp1 = malloc(sizeof(LANDING));
    TAKEOFF *temp2 = malloc(sizeof(TAKEOFF));
    if (HEAD_LAND == NULL)
    {
        //printf("LANDING QUEUE EMPTY.\n");
    }
    else
    {
        temp1 = HEAD_LAND;
        while (temp1 != NULL)
        {
            temp1->plane.queue_wait_time++;
            temp1 = temp1->link;
        }
    }
    if (HEAD_TO == NULL)
    {
        //printf("TAKEOFF QUEUE EMPTY.\n");
    }
    else
    {
        temp2 = HEAD_TO;
        while (temp2 != NULL)
        {
            temp2->plane.queue_wait_time++;
            temp2 = temp2->link;
        }
    }
}