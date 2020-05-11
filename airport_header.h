//Simulation constants
int SIM_RUN_TIME;
float EXPECTED_TAKEOFF_PER_UNIT;
float EXPECTED_LANDING_PER_UNIT;
int AIRCRAFT_NUM;
int RUNTIME;

/*
RUNWAY_STATUS is 0 when idle, 1 when occupied
*/
int RUNWAY_STATUS;

//Aircraft info
typedef struct aircraft
{
    int aircraft_num;
    int status;         //0 is for landing and 1 is for takeoff
    int fuel_remaining; //landing case, given in units of time
    int queue_wait_time;
} AIRCRAFT;

//Landing queue

typedef struct landing_queue
{
    AIRCRAFT plane;
    struct landing_queue *link;
} LANDING;

LANDING *HEAD_LAND;
LANDING *TAIL_LAND;

//Takeoff queue

typedef struct takeoff_queue
{
    AIRCRAFT plane;
    struct takeoff_queue *link;
} TAKEOFF;

TAKEOFF *HEAD_TO;
TAKEOFF *TAIL_TO;

//Function Definitions

void initializer(int, float, float);
AIRCRAFT aircraft_generator();
void queue_generator();
void main_loop();
void increase_queue_wait_time();

//Queue controllers
void landing_queue_add(AIRCRAFT);
void landing_queue_remove();
void takeoff_queue_add(AIRCRAFT);
void takeoff_queue_remove();

