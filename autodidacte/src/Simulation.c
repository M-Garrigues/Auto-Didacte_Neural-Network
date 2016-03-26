#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


	/*  Simulation.C   -----   LIF7 Auto-Didacte */


#include "Simulation.h"
#include "stdlib.h"
#include "assert.h"
#include "stdio.h"



Neuron * newSimulation(float speed, Car * car, Track * track, Point * initPosition, float initOrientation)
{
	asssert(car =! NULL);
	assert(track != NULL);

	Simulation * sim = NULL;
	sim = malloc(sizeof(Simulation));
	assert(sim != NULL);

	sim->speed = speed;

	sim->car = newCar();
	initCar(sim->car, initPosition, initOrientation);

	sim->track = track;
	sim->initPosition = initPosition;
	sim->initOrientation = initOrientation;

	return sim;
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
