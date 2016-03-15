#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


	/*  Neuron.C   -----   LIF7 Auto-Didacte */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Neuron.h"



Neuron * newInputNeuron(int nbNeuron)  					/*INPUT NEURON CONSTRUCTOR*/
{
	int i;
	Neuron * neuron = NULL;

	neuron = malloc(sizeof(Neuron));
	assert(neuron != NULL);

	neuron->type = INPUT;

	neuron->nbWeights = nbNeuron;

	neuron->value = 0;

	neuron->tabWeights = NULL;
	neuron->tabWeights = malloc(nbNeuron*sizeof(float));
	assert(neuron->tabWeights != NULL);

	for (i = 0; i < neuron->nbWeights; ++i)
	{
		neuron->tabWeights[i] = 0;
	}

	return neuron;
}


Neuron * newHiddenNeuron(int nbNeuron)					/*HIDDEN NEURON CONSTRUCTOR*/
{
	int i;
	Neuron * neuron = NULL;

	neuron = malloc(sizeof(Neuron));
	assert(neuron != NULL);

	neuron->type = HIDDEN;

	neuron->nbWeights = nbNeuron;

	neuron->value = 0;

	neuron->tabWeights = NULL;
	neuron->tabWeights = malloc(nbNeuron*sizeof(float));
	assert(neuron->tabWeights != NULL);

	for (i = 0; i < neuron->nbWeights; ++i)
	{
		neuron->tabWeights[i] = 0;
	}

	return neuron;
}

Neuron * newOutputNeuron(void)							/*OUTPUT NEURON CONSTRUCTOR*/
{
	Neuron * neuron = NULL;

	neuron = malloc(sizeof(Neuron));
	assert(neuron != NULL);

	neuron->type = OUTPUT;

	neuron->nbWeights = 0;

	neuron->value = 0;

	neuron->tabWeights = NULL;

	return neuron;
}

void deleteNeuron(Neuron * neuron)						/*NEURON DESTRUCTOR*/
{
    int i;
    assert(neuron != NULL);

	neuron->value = 0;

	neuron->type = 0;

	if(neuron->type != OUTPUT)
	{
		for (i = 0; i < neuron->nbWeights; i++)
		{
			neuron->tabWeights[i] = 0;
		}
		free(neuron->tabWeights);
	}

	free(neuron);
}





float getValue(const Neuron * neuron)									/*NEURON GET/SET*/
{
	assert(neuron != NULL);
	return neuron->value;
}

void  setValue(Neuron * neuron, float newValue)
{
	assert(neuron != NULL);
	neuron->value = newValue;
}



float getWeight(const Neuron * neuron, int i)
{
	assert(neuron != NULL);

    assert(i < neuron->nbWeights && i > -1);
	return neuron->tabWeights[i];
}

void  setWeight(Neuron * neuron, int i, float newWeight)
{
	assert(neuron != NULL);

    assert(i < neuron->nbWeights && i > -1);
	neuron->tabWeights[i] = newWeight;
}



char getTypeNeuron(const Neuron * neuron)
{
	assert(neuron != NULL);
	return neuron->type;
}

void setTypeNeuron(Neuron * neuron, char newType)
{
	assert(neuron != NULL);
	neuron->type = newType;
}



int getNbWeights(const Neuron * neuron)
{
	assert(neuron != NULL);
	return  neuron->nbWeights;
}

void setNbWeights(Neuron * neuron,int newNbWeights)
{
	assert(neuron != NULL);
	neuron->nbWeights = newNbWeights;
}




