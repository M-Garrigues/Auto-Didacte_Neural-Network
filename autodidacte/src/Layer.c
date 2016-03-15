#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


	/*  Layer.c    -----   LIF7 Auto-Didacte */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "math.h"
#include "Layer.h"



Layer * newInputLayer(int nbNeurons, int nbHiddenNeuron)            /*INPUT LAYER CONSTRUCTOR*/
{
    int i = 0;

	Layer * layer = NULL;

	layer = malloc(sizeof(Layer));
    assert(layer != NULL);

	layer->type = INPUT;

	layer->nbNeurons = nbNeurons;

	layer->tabNeurons= NULL;
	layer->tabNeurons = malloc(nbNeurons*sizeof(Neuron *));
	assert(layer->tabNeurons != NULL);

	for (i = 0; i < nbNeurons; ++i)
	{
		layer->tabNeurons[i] = newInputNeuron(nbHiddenNeuron);
	}
printf("Layer created\n");
	return layer;
}

Layer * newHiddenLayer(int nbNeurons, int nbOutputNeuron)              /*HIDDEN LAYER CONSTRUCTOR*/
{
	int i = 0;

	Layer * layer;

	layer = malloc(sizeof(Layer));
	assert(layer != NULL);

	layer->type = HIDDEN;

	layer->nbNeurons = nbNeurons;

    layer->tabNeurons= NULL;
	layer->tabNeurons = malloc(nbNeurons*sizeof(Neuron *));
	assert(layer->tabNeurons != NULL);

	for (i = 0; i < nbNeurons; ++i)
	{
		layer->tabNeurons[i] = newHiddenNeuron(nbOutputNeuron);
	}
printf("Layer created\n");

	return layer;
}

Layer * newOutputLayer(int nbNeurons)                                  /*OUTPUT LAYER CONSTRUCTOR*/
{
	int i = 0;

	Layer * layer;

	layer = malloc(sizeof(Layer));
	assert(layer != NULL);

	layer->type = OUTPUT;

	layer->nbNeurons = nbNeurons;

    layer->tabNeurons= NULL;
	layer->tabNeurons = malloc(nbNeurons*sizeof(Neuron *));
    assert(layer->tabNeurons != NULL);

	for (i = 0; i < nbNeurons; ++i)
	{
		layer->tabNeurons[i] = newOutputNeuron();
	}
printf("Layer created\n\n");

	return layer;
}


void deleteLayer(Layer * layer)                                     		/*LAYER DESTRUCTOR*/
{
    int i;

    assert(layer != NULL);

	layer->type = 0;

	for (i = 0; i < layer->nbNeurons; ++i)
	{
		deleteNeuron(layer->tabNeurons[i]);
	}

	layer->nbNeurons = 0;

	free(layer->tabNeurons);

	free(layer);
}


int getNbNeurons(const Layer* layer)											/*LAYER GET/SET*/
{
	assert(layer!=NULL);
    return layer->nbNeurons;
}

void setNbNeurons(Layer * layer, int newNbNeurons)
{
	assert(layer!=NULL);
    layer->nbNeurons = newNbNeurons;
}


void updateInputLayer(Layer * layer, float * tabNewValues)							/*LAYER FUNCTIONS*/
{
	int i;

	assert(layer !=NULL);
	assert(layer->type == INPUT);

	for (i = 0; i < layer->nbNeurons; ++i)
	{
		layer->tabNeurons[i]->value = tabNewValues[i];
	}
}	

void updateLayer(Layer * layer1, Layer * layer2)
{
	int i, j;

	assert(layer1 !=NULL && layer2 != NULL);
	assert((layer2->type == HIDDEN && layer1->type == INPUT)||(layer2->type == OUTPUT && layer1->type == HIDDEN));

	if (layer1->type == HIDDEN)
	{
		for (i = 0; i < layer2->nbNeurons; ++i)
		{
			layer2->tabNeurons[i]->value = 0;

			for (j = 0; j < layer1->nbNeurons; ++j)
			{
				layer2->tabNeurons[i]->value += (layer1->tabNeurons[j]->tabWeights[i])*(layer1->tabNeurons[j]->value); /*summing all the entries*/
			}
		}
	}
	else
	{
		for (i = 0; i < layer2->nbNeurons; ++i)
		{
			layer2->tabNeurons[i]->value = 0;

			for (j = 0; j < layer1->nbNeurons; ++j)
			{
				layer2->tabNeurons[i]->value += (layer1->tabNeurons[j]->tabWeights[i])*(layer1->tabNeurons[j]->value); /*summing all the entries*/
			}

			layer2->tabNeurons[i]->value = sigmoid(layer2->tabNeurons[i]->value);
		}
	}
}	


void initialiseLayerTEST(Layer * layer)
{
	int i,j;

	assert(layer != NULL);
	assert(layer->type == INPUT || layer->type == HIDDEN);

	for (i = 0; i < layer->nbNeurons; ++i)
	{
		for (j = 0; j < layer->tabNeurons[0]->nbWeights; ++j)
		{
			layer->tabNeurons[i]->tabWeights[j] = 0.2;
		}
	}
}

float sigmoid(float x)
{
    return (1/(1+exp(-x)));
}
