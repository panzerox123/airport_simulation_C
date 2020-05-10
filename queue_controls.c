#include <stdio.h>
#include "airport_header.h"
#include <stdlib.h>

//Landing queue controls
void landing_queue_add(AIRCRAFT dat)
{
    LANDING *temp = malloc(sizeof(LANDING));
    if (HEAD_LAND == NULL)
    {
        temp->plane = dat;
        HEAD_LAND = temp;
        TAIL_LAND = temp;
        printf("Plane %d ready to land.\n", temp->plane.aircraft_num);
    }
    else
    {
        temp->plane = dat;
        TAIL_LAND->link = temp;
        TAIL_LAND = temp;
    }
    temp = NULL;
    free(temp);
}

void landing_queue_remove()
{
    if (HEAD_LAND == NULL)
    {
        printf("\nLANDING QUEUE IS EMPTY");
    }
    else
    {
        HEAD_LAND = HEAD_LAND->link;
    }
}

//Takeoff queue controls

void takeoff_queue_add(AIRCRAFT dat)
{
    TAKEOFF *temp = malloc(sizeof(TAKEOFF));
    if (HEAD_TO == NULL)
    {
        temp->plane = dat;
        HEAD_TO = temp;
        TAIL_TO = temp;
        printf("Plane %d ready to takeoff.\n", temp->plane.aircraft_num);
    }
    else
    {
        temp->plane = dat;
        TAIL_TO->link = temp;
        TAIL_TO = temp;
    }
    temp = NULL;
    free(temp);
}

void takeoff_queue_remove()
{
    if (HEAD_TO == NULL)
    {
        printf("\nTAKEOFF QUEUE IS EMPTY");
    }
    else
    {
        HEAD_TO = HEAD_TO->link;
    }
}