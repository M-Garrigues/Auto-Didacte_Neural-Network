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
		setNeuron(layer, i, newInputNeuron(nbHiddenNeuron));
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
		setNeuron(layer, i, newHiddenNeuron(nbOutputNeuron));
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
		setNeuron(layer, i, newOutputNeuron());
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
		deleteNeuron(getNeuron(layer, i));
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


int getTypeLayer(const Layer * layer)
{
	assert(layer != NULL);
	return layer->type;
}

void setTypeLayer(Layer * layer, int newType)
{
	assert(layer != NULL);
	layer->type = newType;
}


Neuron * getNeuron(const Layer * layer, int i)
{
	assert(layer != NULL);
	assert(layer->nbNeurons >= i && i >= 0);
	return layer->tabNeurons[i]; 
}

void setNeuron(Layer * layer, int i, Neuron * newNeuron)
{
	assert(layer != NULL);
	assert(layer->nbNeurons >= i && i >= 0);
	assert(newNeuron != NULL);
	layer->tabNeurons[i] = newNeuron;
}





void updateInputLayer(Layer * layer, float * tabNewValues)							/*LAYER FUNCTIONS*/
{
	int i;

	assert(layer !=NULL);
	assert(layer->type == INPUT);

	for (i = 0; i < layer->nbNeurons; ++i)
	{
		setValue(getNeuron(layer, i), tabNewValues[i]);
	}
}	

void updateLayer(Layer * layer1, Layer * layer2)
{
	int i, j;

	assert(layer1 !=NULL && layer2 != NULL);
	assert((layer2->type == HIDDEN && layer1->type == INPUT)||(layer2->type == OUTPUT && layer1->type == HIDDEN));

		for (i = 0; i < layer2->nbNeurons; ++i)
		{
			layer2->tabNeurons[i]->value = 0;

			for (j = 0; j < layer1->nbNeurons; ++j)
			{	
				/*summing all the entries*/
				setValue(getNeuron(layer2, i), getValue(getNeuron(layer2, i)) + getWeight(getNeuron(layer1,j), i) * getValue(getNeuron(layer1,j))); 
			}

			setValue(getNeuron(layer2, i), sigmoid(getValue(getNeuron(layer2, i))));
		}
}	


void initialiseLayerTEST(Layer * layer)
{
	int i,j;

	assert(layer != NULL);
	assert(layer->type == INPUT || layer->type == HIDDEN);

	for (i = 0; i < layer->nbNeurons; ++i)
	{
		for (j = 0; j < getNbWeights(getNeuron(layer, 0)); ++j)
		{
			setWeight(getNeuron(layer, i), j, 0.2);
		}
	}
}

float sigmoid(float x)
{
    return (1/(1+exp(-x)));
}
