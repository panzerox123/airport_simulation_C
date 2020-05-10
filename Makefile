simulation_app: main.o airport.o queue_controls.o
	gcc main.o airport.o queue_controls.o -o simulation_app

airport.o: airport.c airport_header.h
	gcc -c airport.c

queue_controls.o: queue_controls.c airport_header.h
	gcc -c queue_controls.c

main.o: main.c airport_header.h
	gcc -c main.c