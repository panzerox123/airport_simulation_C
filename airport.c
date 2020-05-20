#include <stdio.h>
#include "airport_header.h"
#include <stdlib.h>
#include <time.h>

/*
The initializer function intializes all the constants in the simulation program.
*/
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
    CRASHED_PLANES = 0;
    srand(time(0));
    return;
}
/*
aircraft_generator Generates a unique type of aircraft every time it is called
*/
AIRCRAFT aircraft_generator()
{
    AIRCRAFT PLANE;
    PLANE.aircraft_num = AIRCRAFT_NUM++;
    PLANE.status = rand() % 2;
    if (PLANE.status == 0)
        PLANE.fuel_remaining = rand() % EXPECTED_AIRCRAFTS_PER_UNIT + 1;
    PLANE.queue_wait_time = 0;
    return PLANE;
}

/*
queue_generator generates a randomised queue of aircrafts every unit of time
*/
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

/*
main_loop is the loop that runs for N units of time and generated a queue every unit.
One plane can take off or land per unit, with landing queue being priorotised.
Wait time and fuel consumption is also changed every iteration.
*/
void main_loop()
{
    queue_generator();
    int state;
    for (int i = 0; i < SIM_RUN_TIME; i++)
    {
        printf("%d:\n", i + 1);
        state = immediate_land();
        if (state != 2)
        {
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
        }
        increase_queue_wait_time();
        queue_generator();
    }
}

/*
increase_queue_wait_time function increases the waiting time for all aircrafts that have not landed or taken off.
It also reduces the fuel remaining in all aircrafts.
*/
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
            temp1->plane.fuel_remaining--;
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

/*
number_left function counts the number of aircrafts left in each queue.
*/
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

/*
final_stats function is responsible for calculating the results from running the simulation.
*/

void final_stats()
{
    number_left();
    float runway_idle_percent = (float)RUNWAY_IDLE_NUM * 100 / SIM_RUN_TIME;
    float avg_takeoff_queue = 0, avg_land_queue = 0;
    if (NUMBER_TAKEN_OFF != 0)
        avg_takeoff_queue = (float)QUEUE_TIME_TAKEOFF / NUMBER_TAKEN_OFF;
    if (NUMBER_LANDED != 0)
        avg_land_queue = (float)QUEUE_TIME_LANDED / NUMBER_LANDED;
    printf("\nSIMULATION RESULTS:\nNumber Landed: %d\nNumber Taken off: %d\nNumber left to land: %d\nNumber left to takeoff: %d\nRunway idle time: %.2f percent\nAverage takeoff wait: %.2f units\nAverage land wait: %.2f units\nPlanes crashed: %d\n", NUMBER_LANDED, NUMBER_TAKEN_OFF, NUMBER_LEFT_LAND, NUMBER_LEFT_TAKEOFF, runway_idle_percent, avg_takeoff_queue, avg_land_queue, CRASHED_PLANES);
}

/*
immediate_land function lands a plane that does not have enough fuel to wait in queue immediately.
If the plane has been waiting and the fuel remaining is 0, the plane crashes.
*/

int immediate_land()
{
    LANDING *temp = malloc(sizeof(LANDING));
    int queue = 0;
    if (HEAD_LAND == NULL)
    {
        return 0;
    }
    else
    {
        temp = HEAD_LAND;
        while (temp->link != NULL)
        {
            queue++;
            if (temp->link->plane.fuel_remaining < 0)
            {
                printf("Plane %d has CRASHED. %d units of fuel.\n", temp->link->plane.aircraft_num, temp->link->plane.fuel_remaining);
                temp->link = temp->link->link;
                CRASHED_PLANES++;
                return 1;
            }
            else if (temp->link->plane.fuel_remaining < queue)
            {
                printf("Plane %d has landed (Emergency). Waiting in queue for %d units.\n", temp->link->plane.aircraft_num, temp->link->plane.queue_wait_time);
                NUMBER_LANDED++;
                QUEUE_TIME_LANDED += temp->link->plane.queue_wait_time;
                temp->link = temp->link->link;
                return 2;
            }
            temp = temp->link;
        }
    }
}

/*
menu_loop function runs a switch statement in a loop to run the simulation program as many times as your want.
*/

void menu_loop()
{
    char selection;
    while (1)
    {
        printf("\nAIRPORT TRAFFIC SIMULATION\npress '1' to simulate or '2' to quit.\nChoice: \n");
        scanf(" %c", &selection);
        switch (selection)
        {
        case '1':
            printf("Initialize simulator... \n");
            unsigned int runtime;
            unsigned int max_aircrafts;
            printf("Enter units of time:\n");
            scanf("%d", &runtime);
            printf("Enter maximum number of aircrafts that can be generated per unit of time:\n");
            scanf("%d", &max_aircrafts);
            initializer(runtime, max_aircrafts);
            main_loop();
            final_stats();
            break;

        case '2':
            exit(0);

        default:
            printf("Option entered is incorrect... try again.\n");
        }
    }
}

/*
Version 1.0.0
Kunal Bhat
*/