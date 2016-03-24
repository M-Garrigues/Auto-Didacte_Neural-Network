#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


	/*  main.C   -----   LIF7 Auto-Didacte  TEST ANN */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Generation.h"
#include "Layer.h"
#if 0 
#include "time.h"

void regressionTestANN();
void printNetwork(Network * net);
void printLayer(Layer * layer);


int main(int argc, char const *argv[])
{
	int i;
	float tabFloat[6] = {1, 0.5, 1, 0.8, 0.3, 0.4};
	FILE * f = NULL;
	Network * net = NULL;
	Generation * gen1 = newGenerationRandom(30);
	srand(time(NULL));
	f = fopen("data/generationEnd.gen","w");
	for(i = 0;i<10;i++)
	{
		nextGeneration(gen1);
		updateFitnessGeneration(gen1);
		printf("Gen %d: bestfitness ----> %d\n",getNbGen(gen1),getFitness(getGenome(gen1,getBest(gen1))));
	}
	saveGeneration(gen1,f);
	fclose(f);

	net = convertToNetwork(getGenome(gen1,getBest(gen1)));
	printf("\n\n Meilleur genome de la generation transfere en network:\n\n");
	printNetwork(net);

	feedForward(net, tabFloat);
	printf("\n\n Apres feeed feedForward:\n\n");
	printNetwork(net);


	deleteNetwork(net);

	deleteGeneration(gen1);
	regressionTestGenome();
	regressionTestGeneration();
	printf("\n\n\n");

	/*regressionTestANN();*/

	return 0;
}


/*void regressionTestANN(void)
{
	float tabFloat[5] = {1, 0.5, -2, 0.8, -0.3};

    Network * net = newNetwork(5,3,5);

    initialiseNetworkTEST(net);

    setWeight(net->tabLayers[INPUT]->tabNeurons[1],1, 1.3);
    setWeight(net->tabLayers[INPUT]->tabNeurons[2],0, -0.5);
    setWeight(net->tabLayers[HIDDEN]->tabNeurons[0],1, 2.3);
    setWeight(net->tabLayers[HIDDEN]->tabNeurons[1],0, 1.9);

    feedForward(net, tabFloat);

    printNetwork(net);

    deleteNetwork(net);

    printf("\nNetwork successfully deleted.\n\n\n");
}
*/


void printLayer(Layer * layer)
{
	int i,j;

	assert(layer != NULL);

	if(layer->type == INPUT || layer->type == HIDDEN)
	{
		if (layer->type == INPUT)
			printf("INPUT LAYER:\n\n");

		if (layer->type == HIDDEN)
			printf("HIDDEN LAYER:\n\n");

		for (i = 0; i < layer->nbNeurons; ++i)
		{
			printf("Neuron %d: %f  =====  ",i, layer->tabNeurons[i]->value);

			for (j = 0; j < layer->tabNeurons[0]->nbWeights; ++j)
			{
				printf("W%d: %f | ", j, layer->tabNeurons[i]->tabWeights[j]);
			}
			printf("\n");
			
		}

		printf("\n\n ********************************\n\n");
	}

	else
	{
		printf("OUTPUT LAYER:\n\n");

		for (i = 0; i < layer->nbNeurons; ++i)
		{
			printf("Neuron %d: %f     ",i, layer->tabNeurons[i]->value);
		}
		printf("\n\n ********************************\n\n");
	}
}


void printNetwork(Network * net)
{
	printLayer(net->tabLayers[INPUT]);
	printLayer(net->tabLayers[HIDDEN]);
	printLayer(net->tabLayers[OUTPUT]);
}


/* void inportGenome(Genome * genome, Network * net)
// {
// 	int i,j,c;
// 	c=0;

// 	assert(net != NULL);
// 	assert(genome != NULL);

// 	genome->nbInputNeuron = net->nbInputNeuron;
// 	genome->nbHiddenNeuron = net->nbHiddenNeuron;
// 	genome->nbOutputNeuron = net->nbOutputNeuron;


// 	int nbWeightsInput = net->tabLayer[INPUT]->tabNeurons[0]->nbWeights;
// 	int nbWeightsHidden = net->tabLayer[HIDDEN]->tabNeurons[0]->nbWeights;

// 	int tailleTab = (net->nbInputNeuron)*nbWeightsInput + (net->nbHiddenNeuron)*nbWeightsHiddenv ;

// 	genome->tabGenome = malloc(tailleTab*sizeof(float));

// 	for (i = 0; i < net->nbInputNeuron; ++i)
// 	{
// 		for (j = 0; j < nbWeightsInput; ++j)
// 		{
// 			assert(c < tailleTab);
// 			genome->tabGenome[c] = net->tabLayers[INPUT]->tabNeurons[i]->tabWeights[j];
// 			c++;
// 		}
// 	}

// 	for (i = 0; i < net->nbHiddenNeuron; ++i)
// 	{
// 		for (j = 0; j < nbWeightsHidden; ++j)
// 		{
// 			assert(c < tailleTab);
// 			genome->tabGenome[c] = net->tabLayers[HIDDEN]->tabNeurons[i]->tabWeights[j];
// 			c++;
// 		}
// 	}
// }

// void exportGenome(Genome * genome, Network * net)
// {
// 	int i,j,c;
// 	c=0;

// 	assert(net != NULL);
// 	assert(genome != NULL);

// 	net->nbInputNeuron = genome->nbInputNeuron;
// 	net->nbHiddenNeuron = genome->nbHiddenNeuron;
// 	net->nbOutputNeuron = genome->nbOutputNeuron;

// } */
#endif
#include <stdio.h>
#include <chipmunk/chipmunk.h>

int main(void){
  // cpVect is a 2D vector and cpv() is a shortcut for initializing them.
  cpVect gravity = cpv(0, -100);
  
  // Create an empty space.
  cpSpace * space = cpSpaceNew();
  cpSpaceSetGravity(space, gravity);
  
  // Add a static line segment shape for the ground.
  // We'll make it slightly tilted so the ball will roll off.
  // We attach it to space->staticBody to tell Chipmunk it shouldn't be movable.
  cpShape *ground = cpSegmentShapeNew(space->staticBody, cpv(-20, 5), cpv(20, -5), 0);
  cpShapeSetFriction(ground, 1);
  cpSpaceAddShape(space, ground);
  
  // Now let's make a ball that falls onto the line and rolls off.
  // First we need to make a cpBody to hold the physical properties of the object.
  // These include the mass, position, velocity, angle, etc. of the object.
  // Then we attach collision shapes to the cpBody to give it a size and shape.
  
  cpFloat radius = 5;
  cpFloat mass = 1;
  
  // The moment of inertia is like mass for rotation
  // Use the cpMomentFor*() functions to help you approximate it.
  cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
  
  // The cpSpaceAdd*() functions return the thing that you are adding.
  // It's convenient to create and add an object in one line.
  cpBody *ballBody = cpSpaceAddBody(space, cpBodyNew(mass, moment));
  cpBodySetPos(ballBody, cpv(0, 15));
  
  // Now we create the collision shape for the ball.
  // You can create multiple collision shapes that point to the same body.
  // They will all be attached to the body and move around to follow it.
  cpShape *ballShape = cpSpaceAddShape(space, cpCircleShapeNew(ballBody, radius, cpvzero));
  cpShapeSetFriction(ballShape, 0.7);
  
  // Now that it's all set up, we simulate all the objects in the space by
  // stepping forward through time in small increments called steps.
  // It is *highly* recommended to use a fixed size time step.
  cpFloat timeStep = 1.0/60.0;
  for(cpFloat time = 0; time < 2; time += timeStep){
    cpVect pos = cpBodyGetPos(ballBody);
    cpVect vel = cpBodyGetVel(ballBody);
    printf(
      "Time is %5.2f. ballBody is at (%5.2f, %5.2f). It's velocity is (%5.2f, %5.2f)\n",
      time, pos.x, pos.y, vel.x, vel.y
    );
    
    cpSpaceStep(space, timeStep);
  }
  
  // Clean up our objects and exit!
  cpShapeFree(ballShape);
  cpBodyFree(ballBody);
  cpShapeFree(ground);
  cpSpaceFree(space);
  
  return 0;
}