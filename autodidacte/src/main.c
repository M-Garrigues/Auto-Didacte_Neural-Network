#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


	/*  main.C   -----   LIF7 Auto-Didacte  TEST ANN */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Generation.h"
#include "Layer.h"
#include "Track.h"
#include "Display_SDL.h"
#include "time.h"

/*void regressionTestANN();
void printNetwork(Network * net);
void printLayer(Layer * layer);
void testRegressionPOINT();
*/

int main()
{
	FILE * f = fopen("data/track.txt", "r");
	int tab[3] = {5, 3, 2};
	float initOrient = 0;
	srand(time(NULL));
	Generation * pGen = newGenerationRandom(30, tab);
	Track * pTrack = newTrack();
	Point * pInit;
	initTrackFile(pTrack,f);
	fclose(f);
	f = fopen("data/firstGen.gen", "w");
	saveGeneration(pGen, f);
	pInit = intersectPoint (pTrack->trackIn[0] , pTrack->trackOut[1] , pTrack->trackOut[0] , pTrack->trackIn[1]);
	displayManagement(pGen , pTrack, pInit, initOrient, 640, 480 , 200, "data/car.png");
	deleteGeneration(pGen);
	deleteTrack(pTrack);
	deletePoint(pInit);
	fclose(f);
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

void testRegressionPOINT()
{
	Point *p1, *p2, *p3, *p4;
	p1 = newPoint(0,0);
	p2 = newPoint(10,10);
	p3 = newPoint(6,4);
	p4 = newPoint(6,0);
	printf("\n%d\n\n", intersect(p1,p2,p3,p4));
	printf("\n%f, %f\n", getX(intersectPoint(p1,p2,p3,p4)), getY(intersectPoint(p1,p2,p3,p4)));
}

*/