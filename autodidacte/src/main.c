#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


	/*  main.C   -----   LIF7 Auto-Didacte  TEST ANN */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Generation.h"
#include "Layer.h"
#include "time.h"
/*
#include "Network.h"

void regressionTestANN();
void printNetwork(Network * net);*/
void printLayer(Layer * layer);


int main(int argc, char const *argv[])
{
	Generation * g1; 
	Genome * solution;
	int i;
	srand(time(NULL));
	g1 = newGenerationRandom(10);
	solution = getBest(g1);
	displayGenome(solution);
	while(getFitness(solution)<60 && getNbGen(g1)<20000)
	{
		deleteGenome(solution);
		nextGeneration(&g1);
		updateFitnessGeneration(&g1);
		solution = getBest(g1);
	}
	printf("Gen: %d -> fitness ---> %f\n\n",getNbGen(g1),getFitness(solution));
	displayGenome(solution);
	deleteGenome(solution);
	deleteGeneration(g1);

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

/*
void printNetwork(Network * net)
{
	printLayer(net->tabLayers[INPUT]);
	printLayer(net->tabLayers[HIDDEN]);
	printLayer(net->tabLayers[OUTPUT]);
}*/


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
