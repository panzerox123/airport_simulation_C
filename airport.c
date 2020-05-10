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
    srand(time(0));
    return;
}

//Generates Unique aircraft
AIRCRAFT aircraft_generator()
{
    srand(time(0));
    AIRCRAFT PLANE;
    PLANE.aircraft_num = AIRCRAFT_NUM++;
    PLANE.status = rand() % 2;
    if (PLANE.status == 0)
        PLANE.fuel_remaining = rand() % (SIM_RUN_TIME) + 1;
    return PLANE;
}

void queue_generator()
{
    srand(time(0));
    int generate_queue_aircraft = rand() % 5 + 1; //Generates upto 5 random aircrafts
    AIRCRAFT temp;
    for(int iterate = 0; iterate < generate_queue_aircraft ; iterate++){
        temp = aircraft_generator();
        if(temp.status == 0)
            landing_queue_add(temp);
        else if(temp.status == 1)
            takeoff_queue_add(temp);
    }
}
