 #ifndef H_MG_SIMULATION
 #define H_MG_SIMULATION


  /* Simulation.h    -----   LIF7 Auto-Didacte */


#include "Car.h"
#include "Track.h"
#include "Generation.h"


/* Simulation structure*/
typedef struct
{
    float speed;
    Car * car;
    Track * track;
    Point * initPosition;
    float initOrientation;

}Simulation;

/* Simulation constructors */
Simulation * newSimulation(float speed, Car * car, Track * track, Point * initPosition, float initOrientation);

/* Simulation get/set */
float getSimSpeed(Simulation * sim);
void setSimSpeed(Simulation * sim, float newSpeed);

Car * getCar(Simulation * sim);
void setCar(Simulation * sim, Car * car);

Point * getInitPosition(Simulation * sim);
void setInitPosition(Simulation * sim, Point * newInitPos);

float getInitOrientation(Simulation * sim);
void setInitOrientation(Simulation * sim, float newOrientation);

/* Simulation functions */


/* Simulation destructor */
void endSimulation(Simulation * sim);

#endif