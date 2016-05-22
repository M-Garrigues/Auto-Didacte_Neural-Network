 #ifndef H_MG_SIMULATION
 #define H_MG_SIMULATION


  /* Simulation.h    -----   LIF7 Auto-Didacte */


#include "Car.h"
#include "Track.h"
#include "Generation.h"
#include "time.h"


enum{ LEFT , RIGHT  , ACCELERATION  ,  DECELERATION  ,  NONE };



/* ----- Simulation struct ----- */



/**
 * @struct Simulation
 * @brief Simulation struct manage the interactions between the car and the track
 * 
 */
typedef struct
{
    float speed; /** Simulation speed */
    Track * track; /** Track adress */
    Car * car; /** Car adress */
    Point * initPosition; /** Starting position adress */
    float initOrientation; /** Initial car's orientation */
    int fitness; /** Car's score */
    int sector; /** Current track's part where the car is */
    int nbTicks; /** Number of simulation's tick done in the current sector */

}Simulation;



/* ----- Simulation constructor ----- */



/**
 * @brief      Initialize a new simulation
 *
 * @param[in]  speed            New simulation speed
 * @param[in,out]     genome           Genome adress to load on the car
 * @param[in,out]     track            Track adress
 * @param[in,out]     initPosition     Initial car's position adress
 * @param[in]  initOrientation	Initial car's orientation  
 *
 * @return     Simulation adress
 */
Simulation * newSimulation(float speed, Genome * genome, Track * track, Point * initPosition, float initOrientation);




/* ----- Simulation getter/setter ----- */



/**
 * @brief      Get the sim speed.
 *
 * @param[in,out]      sim   Simulation adress
 *
 * @return     The simulation's speed
 */
float getSimSpeed(Simulation * sim);

/**
 * @brief      Set the sim speed.
 *
 * @param[in,out]      sim       Simulation adress
 * @param[in]  newSpeed  New simulation speed
 */
void setSimSpeed(Simulation * sim, float newSpeed);

/**
 * @brief      Get the car.
 *
 * @param[in,out]      sim   Simulation adress
 *
 * @return     Car adress
 */
Car * getCar(Simulation * sim);

/**
 * @brief      Set the car.
 *
 * @param[in,out]      sim   Simulation adress
 * @param[in,out]      car   New car adress
 */
void setCar(Simulation * sim, Car * car);

/**
 * @brief      Get the init position.
 *
 * @param[in,out]      sim   Simulation adress
 *
 * @return     Intial position point adress
 */
Point * getInitPosition(Simulation * sim);

/**
 * @brief      Set the init position.
 *
 * @param[in,out]      sim         Simulation adress
 * @param[in,out]     newInitPos  Initial position point adress
 */
void setInitPosition(Simulation * sim, Point * newInitPos);

/**
 * @brief      Get the init orientation.
 *
 * @param[in,out]      sim   Simulation adress
 *
 * @return     Current car's orientation
 */
float getInitOrientation(Simulation * sim);

/**
 * @brief      Set the init orientation.
 *
 * @param[in,out]      sim             Simulation adress
 * @param[in]  newOrientation  New car's orientation
 */
void setInitOrientation(Simulation * sim, float newOrientation);

/**
 * @brief      Get the nb ticks.
 *
 * @param[in,out]      sim   Simulation adress
 *
 * @return     Return the tick number
 */
int getNbTicks(Simulation * sim);

/**
 * @brief      Set the nb ticks.
 *
 * @param[in,out]      sim    Simulation adress
 * @param[in]  newNb  new tick number
 */
void setNbTicks(Simulation * sim, int newNb);

/**
 * @brief      Get the track.
 *
 * @param[in,out]      sim   Simulation adress
 *
 * @return     Track adress
 */
Track * getTrack(Simulation * sim);

/**
 * @brief      Set the track.
 *
 * @param[in,out]      sim    Simulation adress
 * @param[in,out]      track  Track adress
 */
void setTrack(Simulation * sim, Track * track);


/**
 * @brief      Get the sim fitness.
 *
 * @param[in,out]      sim   Simulation adress
 *
 * @return     get the car score
 */
int getSimFitness(Simulation * sim);

/**
 * @brief      Set the sim fitness.
 *
 * @param[in,out]      sim         Simulation adress
 * @param[in]  newFitness  New car score
 */
void setSimFitness(Simulation * sim, int newFitness);

/**
 * @brief      Get the sector.
 *
 * @param[in,out]      sim   Simulation adress
 *
 * @return    Current sector 
 */
int getSector(Simulation * sim);

/**
 * @brief      Set the sector.
 *
 * @param[in,out]      sim        Simulation adress
 * @param[in]  newSector  New sector
 */
void setSector(Simulation * sim, int newSector);



/**
 * @brief      Get the number of ticks.
 *
 * @param[in,out]      sim   Simulation adress
 *
 * @return    Current number of ticks 
 */
int getNbTicks(Simulation * sim);

/**
 * @brief      Set the number of ticks.
 *
 * @param[in,out]      sim        Simulation adress
 * @param[in]  newSector  New number of ticks
 */
void setNbTicks(Simulation * sim, int newSector);





/* ----- Simulation functions ----- */ 



/**
 * @brief      Give the new values to the sensors depending of the car position
 *             in the track
 *
 * @param[in,out]      sim   Simulation adress
 */
void updateSensors(Simulation * sim);

/**
 * @brief      Detect if the car change sector while moving 
 *
 * @param[in,out]      sim   Simulation adress
 *
 * @return     0 if the checkpoint isn't crossed else 1
 */
int detectCheckPointCrossed(Simulation * sim);

/**
 * @brief      Detect if the car collide with the track
 *
 * @param[in,out]      sim     Simulation adress
 * @param[in]  sector  Current sector
 *
 * @return     0 if there is no collide else 1
 */
int detectCollision(Simulation * sim, int sector);

/**
 * @brief      Allow the car to move once ,check all the conditions (checkpoints, collisions) and update the sensors 
 *
 * @param[in,out]      sim   Simulation adress
 *
 * @return     The car's fitness score
 */
int tickSimulation(Simulation * sim);



/*----- Simulation destructor ----- */



/**
 * @brief      Delete a simulation
 *
 * @param[in,out]      sim   Simulation adress
 */
void endSimulation(Simulation * sim);

#endif