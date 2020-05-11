#include <stdio.h>
#include "airport_header.h"
#include <stdlib.h>

int main()
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
    return 0;
}