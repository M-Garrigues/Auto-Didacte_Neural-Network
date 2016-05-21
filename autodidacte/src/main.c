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
/*
void unitTestPoint (){
	Point *p1, *p2, *p3, *p4, *p5, *p6;
 	p1 = newPoint(-10,0);
 	p2 = newPoint(10,0);
 	p3 = newPoint(10,10);
 	p4 = newPoint(-10,-10);
 	assert (getX(p1)==-10);
 	assert (getY(p3)==10);
 	assert (intersect(p1,p2,p3,p4)==1);
 	p5 = intersectPoint(p1,p2,p3,p4);
 	assert (getX(p5)==0);
 	assert (getY(p5)==0);
 	setX(p4,20);
 	setY(p4,10);
 	setX(p1,20);
 	assert (intersect(p1,p2,p3,p4)==0);
 	p6 = middle (p2,p3);
 	assert (getX(p6)==10);
 	assert (getY(p6)==5);
 	assert (distance(p2,p6)==distance(p3,p6));
 	deletePoint(p1);
  	deletePoint(p2);
  	deletePoint(p3);
  	deletePoint(p4);
  	deletePoint(p5);
  	deletePoint(p6);
  	printf("Unit test for Point.* OK\n");
}

void unitTestCar (){
	Car *c1;
	Genome *g1;
	Point *p1, *p2, *p3;
	int tab[3] = {6, 5, 4};
	p1 = newPoint (0,0);
	g1 = newGenomeRandom(tab);
	c1 = newCar();
	initCar (c1, g1, p1, 0, 100, 50);
	p2 = getFrontLeft(c1);
	assert(getX(p2)==50);
	assert(getY(p2)==-25);
	p3 = getCenter(c1);
	assert(getX(p3)==0);
	assert(getY(p3)==0);
	turnLeft(c1);
	assert(getOrientation(c1)<0);
	turnRight(c1);
	assert(getOrientation(c1)==0);
	deleteCar (c1);
	printf("Unit test for Car.* OK\n");
}

void unitTestTrack (){
	Track *t1, *t2;
	Point *p0, *p1, *p2, *p3, *p4;
	p0 = newPoint (0,0);
	p1 = newPoint (10,50);
	p3 = newPoint (10,10);
	p4 = newPoint (50,50);
	FILE * f = fopen("data/track.txt", "r");
	t1 = newTrack();
	initTrack(t1,2);
	setTrackOut(t1,0,p1);
	setTrackOut(t1,1,p0);
	setTrackIn(t1,0,p3);
	setTrackIn(t1,1,p4);
	p2 = getTrackOut (t1,0);
	assert(getX(p2)==getX(p1));
	assert(getY(p2)==getY(p1));
	assert(getNbPoints(t1)==2);
	deleteTrack(t1);
	t2 = newTrack();
	initTrackFile (t2,f);
	assert(getNbPoints(t2)!=0);
	fclose(f);
	deleteTrack(t2);
	printf("Unit test for Track.* OK\n");

}*/
int main()
{
	FILE * f = fopen("data/circle.track", "r");
	int tab[3] = {6, 5, 4};
	float initOrient = 0;
	srand(time(NULL));
	Generation * pGen = newGenerationRandom(30, tab);
	Track * pTrack = newTrack();
	Point * pInit;
	initTrackFile(pTrack,f);
	fclose(f);
	pInit = intersectPoint (pTrack->trackIn[0] , pTrack->trackOut[1] , pTrack->trackOut[0] , pTrack->trackIn[1]);
	displayManagement(pGen , pTrack, pInit, initOrient, 641, 540 , 60, "data/car.png");


	deleteGeneration(pGen);
	deleteTrack(pTrack);
	deletePoint(pInit);
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