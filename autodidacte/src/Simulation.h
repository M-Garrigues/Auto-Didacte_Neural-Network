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
Neuron * newSimulation(float speed, Car * car, Track * track, Point * initPosition, float initOrientation);

/* Simulation get/set */


/* Simulation functions */


/* Simulation destructor */
void endSimulation(Simulation * sim);

#endif