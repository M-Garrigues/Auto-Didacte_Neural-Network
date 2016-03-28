 #ifndef H_MG_SIMULATION
 #define H_MG_SIMULATION


  /* Simulation.h    -----   LIF7 Auto-Didacte */


#include "Car.h"
#include "Track.h"
#include "Generation.h"


enum{	NONE , LEFT , RIGHT   };


/* Simulation structure*/
typedef struct
{
    float speed;
    Track * track;
    Car * car;
    Point * initPosition;
    float initOrientation;
    float nbTicks;
    int fitness;
    int sector;

}Simulation;

/* Simulation constructors */
Simulation * newSimulation(float speed, Genome * genome, Track * track, Point * initPosition, float initOrientation);

/* Simulation get/set */
float getSimSpeed(Simulation * sim);
void setSimSpeed(Simulation * sim, float newSpeed);

Car * getCar(Simulation * sim);
void setCar(Simulation * sim, Car * car);

Point * getInitPosition(Simulation * sim);
void setInitPosition(Simulation * sim, Point * newInitPos);

float getInitOrientation(Simulation * sim);
void setInitOrientation(Simulation * sim, float newOrientation);

int getNbTicks(Simulation * sim);
void setNbTicks(Simulation * sim, int newNb);

Track * getTrack(Simulation * sim);
void setTrack(Simulation * sim, Track * track);

int getSimFitness(Simulation * sim);
void setSimFitness(Simulation * sim, int newFitness);

int getSector(Simulation * sim);
void setSector(Simulation * sim, int newSector);


/* Simulation functions */
void updateSensors(Simulation * sim, int sector);
int detectCheckPointCrossed(Simulation * sim);
int detectCollision(Simulation * sim, int sector);
int tickSimulation(Simulation * sim);

/* Simulation destructor */
void endSimulation(Simulation * sim);

#endif