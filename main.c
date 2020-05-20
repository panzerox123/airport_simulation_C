#include <stdio.h>
#include "airport_header.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        menu_loop();
    }
    else if (argc == 2 || argc > 3)
    {
        printf("Invalid number of arguments detected.\nUsage:\nsimulation_app <units of time> <maximum number of aircrafts generated per unit>\n");
        return -1;
    }
    else if (argc == 3)
    {
        int i, flag = 0;
        for (i = 0; i < strlen(argv[1]); i++)
        {
            if (!isdigit(argv[1][i]))
                flag = 1;
        }
        for (i = 0; i < strlen(argv[2]); i++)
        {
            if (!isdigit(argv[2][i]))
                flag = 1;
        }
        if (flag != 0)
        {
            printf("Invalid arguments detected. Must by of type Integer.\nUsage:\nsimulation_app <units of time> <maximum number of aircrafts generated per unit>\n");
            return -2;
        }
        unsigned int time_input = atoi(argv[1]);
        unsigned int max_rand = atoi(argv[2]);
        initializer(time_input, max_rand);
        main_loop();
        final_stats();
    }
    return 0;
}