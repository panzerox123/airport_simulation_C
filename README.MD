# Airport Simulation Program
### Kunal Bhat

## Source files
airport_header.h
main.c
queue_controls.c
airport.c

## Building 
1. Head to the source directory
2. Run make utility:

make -f Makefile 

or 

make simulation_app

or

make


## Jist

This is a PSWC project that simulates the functioning of a small airport. It runs the simulation for N units of time. One plane can take off or land per unit of time. And for every unit of time, there are randomly generated aircrafts added to the queues. The max units of time and the max number of randomly generated aircrafts are decided by the user. 

There is also a randomly generated fuel level on landing aircrafts. This fuel level decreases every unit of time they are waiting in queue. If the aircraft does not have enough fuel to wait in queue, the aircraft in immediately landed. If the plane runs out of fuel, then it crashes.

There are 2 operation modes, the program loop or the command line arguments. The command line argument only runs once and provides results. The program loop, however, can run as many simulations as required. 

## Usage

./simulation_app [max units of time] [max number of randomly generated aircrafts]

or just

./simulation_app 
