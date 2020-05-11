#include <stdio.h>
#include "airport_header.h"
#include <stdlib.h>
#include <time.h>

void initializer(int srt, int eapu)
{
    SIM_RUN_TIME = srt;
    EXPECTED_AIRCRAFTS_PER_UNIT = eapu;
    HEAD_LAND = NULL;
    HEAD_TO = NULL;
    TAIL_LAND = NULL;
    TAIL_TO = NULL;
    AIRCRAFT_NUM = 1;
    RUNWAY_STATUS = 0;
    NUMBER_LANDED = 0;
    NUMBER_TAKEN_OFF = 0;
    NUMBER_LEFT_LAND = 0;
    NUMBER_LEFT_TAKEOFF = 0;
    RUNWAY_IDLE_NUM = 0;
    QUEUE_TIME_TAKEOFF = 0;
    QUEUE_TIME_LANDED = 0;
    srand(time(0));
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
    int generate_queue_aircraft = rand() % (EXPECTED_AIRCRAFTS_PER_UNIT + 1); //Generates UPTO EXPECTED_AIRCRAFTS_PER_UNIT random aircrafts
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
    for (int i = 0; i < SIM_RUN_TIME; i++)
    {
        printf("%d:\n", i + 1);
        if (HEAD_TO == NULL && HEAD_LAND == NULL)
        {
            RUNWAY_STATUS = 0;
            printf("Runway Idle.\n");
            RUNWAY_IDLE_NUM++;
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

void number_left()
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
            temp1 = temp1->link;
            NUMBER_LEFT_LAND++;
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
            temp2 = temp2->link;
            NUMBER_LEFT_TAKEOFF++;
        }
    }
}

void final_stats()
{
    number_left();
    float runway_idle_percent = (float)RUNWAY_IDLE_NUM * 100 / SIM_RUN_TIME;
    float avg_takeoff_queue = 0, avg_land_queue = 0;
    if (NUMBER_TAKEN_OFF != 0)
        avg_takeoff_queue = (float)QUEUE_TIME_TAKEOFF / NUMBER_TAKEN_OFF;
    if (NUMBER_LANDED != 0)
        avg_land_queue = (float)QUEUE_TIME_LANDED / NUMBER_LANDED;
    printf("\nSIMULATION RESULTS:\nNumber Landed: %d\nNumber Taken off: %d\nNumber left to land: %d\nNumber left to takeoff: %d\nRunway idle time: %.2f percent\nAverage takeoff wait: %.2f units\nAverage land wait: %.2f units\n", NUMBER_LANDED, NUMBER_TAKEN_OFF, NUMBER_LEFT_LAND, NUMBER_LEFT_TAKEOFF, runway_idle_percent, avg_takeoff_queue, avg_land_queue);
}