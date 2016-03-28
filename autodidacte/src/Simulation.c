#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


	/*  Simulation.C   -----   LIF7 Auto-Didacte */


#include "Simulation.h"
#include "stdlib.h"
#include "assert.h"
#include "stdio.h"





Simulation * newSimulation(float speed, Genome * genome, Track * track, Point * initPosition, float initOrientation)
{
	assert(genome != NULL);
	assert(track != NULL);

	Simulation * sim = NULL;
	sim = malloc(sizeof(Simulation));
	assert(sim != NULL);

	sim->car = NULL;
	sim->car = malloc(sizeof(Car));
	assert(sim->car != NULL);

	initCar(sim->car, genome, initPosition, initOrientation);

	sim->speed = speed;


	sim->track = track;
	sim->initPosition = initPosition;
	sim->initOrientation = initOrientation;

	sim->fitness = 0;

	sim->sector = 0;

	return sim;
}

/* Returns -1 if currently active, the fitness of the genome if it's finished */
int tickSimulation(Simulation * sim)
{
	assert(sim != NULL);
	assert(sim->fitness >= 0);

	float * tabSensors;
	int action;
	Network * net;

	sim->nbTicks++;

	/* UPDATESENSORS  Première étape, si vous voyez ça c'est que j'ai eu la flemme de le coder, déso <3
					  Elle sera à mettre dans Simulation.* */
	tabSensors = getSensors(sim->car);
	net = getCarNetwork(sim->car);

	feedForward(net, tabSensors);

	action = selectHigherValue(getLayer(net, OUTPUT));


	switch (action) {

	case NONE :
		moveStraight(sim->car, 1); /* Try different values for moveStraight */
	 break;

	case RIGHT :
	 	turnRight(sim->car);
	 	moveStraight(sim->car, 0.75);
	 break;

	case LEFT :
		turnLeft(sim->car);
		moveStraight(sim->car, 0.75);
	 break;
}

	if(detectCheckPointCrossed(sim)) /*The car entered a new sector, fitness improves*/
	{
		sim->sector++;

		if (!(detectCollision(sim, sim->sector))&&!(detectCollision(sim, sim->sector-1)))
		{
			sim->fitness++;
			return -1;
		}
		else
			return sim->fitness;
	}
	else
	{
		if (!(detectCollision(sim, sim->sector)))
		{
			sim->fitness++;
			return -1;
		}
		else
			return sim->fitness;
	}

}


void updateSensors(Simulation * sim)
{

}


int detectCheckPointCrossed(Simulation * sim)
{
	assert(sim != NULL);

	Point * CPin,* CPout;
	Point * carFL,  * carFR, * carBR;

	CPin = getTrackIn(sim->track, sim->sector+1);
	CPout = getTrackOut(sim->track, sim->sector+1);

	carFL = getFrontLeft(sim->car);
	carFR = getFrontRight(sim->car);
	carBR = getBackRight(sim->car);

	if(intersect(CPin, CPout, carFL, carFR) || intersect(CPin, CPout, carFR, carBR))
		return 1;
	else
		return 0;
}


int detectCollision(Simulation * sim, int sector)/* Here we consider the Inside of the track is always on the car's right*/
{
	assert(sim != NULL);

	Point * TrInUp,* TrInDown, * TrOutUp, * TrOutDown;
	Point * carFL,  * carFR, * carBL, * carBR;

	TrInUp = getTrackIn(sim->track, sim->sector+1);
	TrInDown = getTrackIn(sim->track, sim->sector);
	TrOutUp = getTrackOut(sim->track, sim->sector+1);
	TrOutDown = getTrackOut(sim->track, sim->sector);

	carFL = getFrontLeft(sim->car);
	carFR = getFrontRight(sim->car);
	carBL = getBackLeft(sim->car);
	carBR = getBackLeft(sim->car);

	if(intersect(TrInUp, TrInDown, carBR, carFR) || intersect(TrOutUp, TrOutDown, carFL, carBL))
		return 1;
	else
		return 0;
}









float getSimSpeed(Simulation * sim)
{
	assert(sim != NULL);
	return sim->speed;
}
void setSimSpeed(Simulation * sim, float newSpeed)
{
	assert(sim != NULL);
	sim->speed = newSpeed;
}

Car * getCar(Simulation * sim)
{
	assert(sim != NULL);
	return sim->car;
}
void setCar(Simulation * sim, Car * car)
{
	assert(sim != NULL);
	sim->car = car;
}

Point * getInitPosition(Simulation * sim)
{
	assert(sim != NULL);
	return sim->initPosition;
}
void setInitPosition(Simulation * sim, Point * newInitPos)
{
	assert(sim != NULL);
	sim->initPosition = newInitPos;
}

float getInitOrientation(Simulation * sim)
{
	assert(sim != NULL);
	return sim->initOrientation;
}
void setInitOrientation(Simulation * sim, float newOrientation)
{
	assert(sim != NULL);
	sim->initOrientation = newOrientation;
}


int getNbTicks(Simulation * sim)
{
	assert(sim != NULL);
	return sim->nbTicks;
}
void setNbTicks(Simulation * sim, int newNb)
{
	assert(sim != NULL);
	sim->nbTicks = newNb;
}

Track * getTrack(Simulation * sim)
{
	assert(sim != NULL);
	return sim->track;
}
void setTrack(Simulation * sim, Track * track)
{
	assert(sim != NULL);
	sim->track = track;
}

int getSimFitness(Simulation * sim)
{
	assert(sim != NULL);
	return sim->fitness;
}
void setimFitness(Simulation * sim, int newFitness)
{
	assert(sim != NULL);
	sim->fitness = newFitness;
}

int getSector(Simulation * sim)
{
	assert(sim != NULL);
	return sim->sector;
}
void setSector(Simulation * sim, int newSector)
{
	assert(sim != NULL);
	sim->sector = newSector;
}


void endSimulation(Simulation * sim)
{
	assert(sim != NULL);

	sim->speed = 0;
	deleteCar(sim->car);
	sim->track = NULL; // A CHANGER PEUT ETRE, EN FONCTION DE TRACK.
	sim->initPosition = NULL; // DE MEME
	sim->initOrientation = 0;

	free(sim);
}
