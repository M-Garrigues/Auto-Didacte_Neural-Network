#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


	/*  Network.c    -----   LIF7 Auto-Didacte */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Network.h"



Network * newNetwork(int nbInputNeurons, int nbHiddenNeurons, int nbOutputNeurons)  /*NETWORK CONSTRUCTOR*/
{
	Network * net = NULL;

	net = malloc(sizeof(Network));
	assert(net != NULL);

	net->nbInputNeurons = nbInputNeurons;
	net->nbHiddenNeurons = nbHiddenNeurons;
	net->nbOutputNeurons = nbOutputNeurons;

	net->tabLayers = NULL;
	net->tabLayers = malloc(3*sizeof(Layer *));
	assert(net->tabLayers != NULL);

	net->tabLayers[INPUT] = newInputLayer(nbInputNeurons, nbHiddenNeurons);
	net->tabLayers[HIDDEN] = newHiddenLayer(nbHiddenNeurons, nbOutputNeurons);
	net->tabLayers[OUTPUT] = newOutputLayer(nbOutputNeurons);

	return net;
}





int getNbInputNeurons(const Network * net)												/*NETWORK GET/SET*/
{
	assert(net != NULL);
	return net->nbInputNeurons;
}

void setNbInputNeurons(Network * net, int newNbNeurons)
{
	assert(net != NULL);
	net->nbInputNeurons = newNbNeurons;
}


int getNbHiddenNeurons(const Network * net)
{
	assert(net != NULL);
	return net->nbHiddenNeurons;
}

void setNbHiddenNeurons(Network * net, int newNbNeurons)
{
	assert(net != NULL);
	net->nbHiddenNeurons = newNbNeurons;
}


int getNbOutputNeurons(const Network * net)
{
	assert(net != NULL);
	return net->nbOutputNeurons;
}

void setNbOutputNeurons(Network * net, int newNbNeurons)
{
	assert(net != NULL);
	net->nbOutputNeurons = newNbNeurons;
}


Layer * getLayer(const Network * net, int type)
{
	assert(net != NULL);
	assert(type >= INPUT && type <= OUTPUT);
	return net->tabLayers[type];
}

void setLayer(Network * net, int type, Layer * newLayer)
{
	assert(net != NULL);
	assert(type >= INPUT && type <= OUTPUT);
	assert(newLayer != NULL);
	net->tabLayers[type] = newLayer;
}

float getActivationNet(const Network * net)
{
    assert(net != NULL);
    return net->activation;
}

void setActivationNet(Network * net, float newActivation)
{
    assert(net != NULL);
    net->activation = newActivation; 
}

void initialiseNetworkTEST(Network * net)									/*NETWORK FUNCTIONS*/
{
	assert(net != NULL);

	initialiseLayerTEST(getLayer(net, INPUT));
	initialiseLayerTEST(getLayer(net, HIDDEN));
}											

void feedForward(Network * net, float * tabNewValues)
{
	assert(net != NULL);

	updateInputLayer(getLayer(net, INPUT), tabNewValues);
	updateLayer(getLayer(net, INPUT), getLayer(net, HIDDEN));
	updateLayer(getLayer(net, HIDDEN), getLayer(net, OUTPUT));
}

void printNetwork(Network * net)
{
	printLayer(getLayer(net, INPUT));
	printLayer(getLayer(net, HIDDEN));
	printLayer(getLayer(net, OUTPUT));
}

void regressionTestANN(void)
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



void deleteNetwork(Network * net)			/*NETWORK DESTRUCTOR*/
{	

	assert(net != NULL);

	net->nbInputNeurons = 0;
	net->nbHiddenNeurons = 0;
	net->nbOutputNeurons = 0;

	deleteLayer(getLayer(net, INPUT));
	deleteLayer(getLayer(net, HIDDEN));
	deleteLayer(getLayer(net, OUTPUT));

	free(net->tabLayers);

	free(net);
}