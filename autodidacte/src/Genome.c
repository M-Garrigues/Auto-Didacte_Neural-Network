#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


	/*  Genome.C   -----   LIF7 Auto-Didacte */


#include "Genome.h"
#include "stdlib.h"
#include "assert.h"
#include "time.h"
#include "stdio.h"


Genome * newGenomeRandom(int species)
{
    int i;
    Genome * pGenome = malloc(sizeof(Genome));
    assert(pGenome != NULL);
    pGenome->nbInput = 6;
    pGenome->nbHidden = species;
    pGenome->nbOutput = 4;
    pGenome->fitness = 0;
    pGenome->tabGenes = malloc((pGenome->nbInput + pGenome->nbOutput)*pGenome->nbHidden*sizeof(float));
    assert(pGenome->tabGenes != NULL);
    for(i = 0; i < (pGenome->nbInput + pGenome->nbOutput)*pGenome->nbHidden; i++)
    {
        setGene(pGenome,i,(rand()/(float)RAND_MAX)*(10) - 5);
    }
    return pGenome;
}

Genome * newGenomeNull(int species)
{
    int i;
    Genome * pGenome = malloc(sizeof(Genome));
    assert(pGenome != NULL);
    pGenome->nbInput = 6;
    pGenome->nbHidden = species;
    pGenome->nbOutput = 4;
    pGenome->fitness = 0;
    pGenome->tabGenes = malloc((pGenome->nbInput + pGenome->nbOutput)*pGenome->nbHidden*sizeof(float));
    assert(pGenome != NULL);
    for(i = 0; i < (pGenome->nbInput + pGenome->nbOutput)*pGenome->nbHidden; i++)
    {
        setGene(pGenome,i, 0);
    }
    return pGenome;
}
void deleteGenome(Genome * genome)
{
	assert(genome != NULL);
    free(genome->tabGenes);
    free(genome);
}

float getGene(const Genome * genome, int i)
{
	assert(genome != NULL);
    return genome->tabGenes[i];
}

void setGene(Genome * genome, int i, float value)
{
	assert(genome != NULL);
    genome->tabGenes[i] = value;
}

int getNbInput(const Genome * genome)
{
	assert(genome != NULL);
    return genome->nbInput;
}
void setNbInput(Genome * genome, int nb)
{
	assert(genome != NULL);
    genome->nbInput = nb;
}
int getNbHidden(const Genome * genome)
{
	assert(genome != NULL);
    return genome->nbHidden;
}
void setNbHidden(Genome * genome, int nb)
{
	assert(genome != NULL);
    genome->nbHidden = nb;
}
int getNbOutput(const Genome * genome)
{
	assert(genome != NULL);
    return genome->nbOutput;
}
void setNbOutput(Genome * genome, int nb)
{
	assert(genome != NULL);
    genome->nbOutput = nb;
}
int getFitness(const Genome * genome)
{
	assert(genome != NULL);
    return genome->fitness;
}
void setFitness(Genome * genome, int value)
{
	assert(genome != NULL);
    genome->fitness = value;
}




void crossover(const Genome * genome1, const Genome * genome2, Genome * child)
{
    int i;
    assert(genome1->nbHidden == genome2->nbHidden);  /*same species*/
    child->nbInput = genome1->nbInput;
    child->nbHidden = genome1->nbHidden;
    child->nbOutput = genome1->nbOutput;
    child->fitness = 0;
    free(child->tabGenes);
    child->tabGenes = malloc(sizeof(float)*(getNbInput(child) + getNbOutput(child))*getNbHidden(child));
    for(i = 0; i< (getNbInput(child) + getNbOutput(child))*getNbHidden(child); i++)
    {
        if(rand()%2)
            setGene(child, i , getGene(genome1, i));
        else
            setGene(child, i , getGene(genome2, i));
    }
}

void mutation(Genome * genome)
{
    int i;
    for(i =0; i<(getNbInput(genome) + getNbOutput(genome))*getNbHidden(genome); i++)
    {
        if(rand()%(getNbInput(genome) + getNbOutput(genome))*getNbHidden(genome) == 0)
            setGene(genome, i , getGene((genome), i) + (rand()/(float)RAND_MAX)-0.5);
        else
            setGene(genome,i,getGene(genome,i));
    }
}

void displayGenome(const Genome * genome)
{
    int i;
    for(i = 0; i<(getNbInput(genome) + getNbOutput(genome))*getNbHidden(genome);i++)
    {
        printf("%f : ", getGene(genome, i));
    }
    printf("\n");
}


void saveGenome(const Genome * genome, FILE * f)
{
    int i;
    fprintf(f,"#nbInput:%d\n",getNbInput(genome));
    fprintf(f,"#nbHidden:%d\n",getNbHidden(genome));
    fprintf(f,"#nbOutput:%d\n",getNbOutput(genome));
    fprintf(f,"#fitness:%d\n",getFitness(genome));
    for(i=0;i<(getNbInput(genome) + getNbOutput(genome))*getNbHidden(genome);i++)
        fprintf(f, "%f ", getGene(genome, i));
    fprintf(f, "\n");
}

void loadGenome(FILE * f, Genome * genome)
{
    int i;
    float a;
    fscanf(f,"#nbInput:%d\n",&i);
    setNbInput(genome, i);
    fscanf(f,"#nbHidden:%d\n",&i);
    setNbHidden(genome, i);
    fscanf(f,"#nbOutput:%d\n",&i);
    setNbOutput(genome, i);
    fscanf(f, "#fitness:%d\n",&i);
    setFitness(genome, i);
    free(genome->tabGenes);
    genome->tabGenes = malloc(sizeof(float)*(getNbInput(genome) + getNbOutput(genome))*getNbHidden(genome));
    for(i = 0; i< (getNbInput(genome) + getNbOutput(genome))*getNbHidden(genome); i++)
    {
        fscanf(f,"%f ", &a);
        setGene(genome, i, a);
    }
    fscanf(f,"\n");
}
void updateFitnessGenome(Genome * genome)
{
    int i;
    setFitness(genome, 1);
    for(i =0; i<(getNbInput(genome) + getNbOutput(genome))*getNbHidden(genome);i++)
    {
        if(getGene(genome,i)<0)
            setFitness(genome, getFitness(genome)+1);
    }
}

Network * convertToNetwork(const Genome * genome)
{
	int i, j, c;

    Network * net = NULL;
    Layer * InLayer = NULL;
   	Layer * HidLayer = NULL;
	int nbWeightsIn, nbWeightsHid, tailleTab;

	assert(genome != NULL);

    net = newNetwork(getNbInput(genome),getNbHidden(genome),getNbOutput(genome));
    assert(net != NULL);

    InLayer = getLayer(net, INPUT);
    HidLayer = getLayer(net, HIDDEN);

    nbWeightsIn = getNbWeights(getNeuron(InLayer, 0));
    nbWeightsHid = getNbWeights(getNeuron(HidLayer, 0));

    tailleTab = getNbNeurons(InLayer)*nbWeightsIn + getNbNeurons(HidLayer)*nbWeightsHid;
    c = 0;

    for (i = 0; i < getNbNeurons(InLayer); ++i)  /*Setting all weights for Input Layer*/
    {
    	for (j = 0; j < nbWeightsIn; ++j)
    	{
    		assert(c < tailleTab);
    		setWeight(getNeuron(InLayer, i), j, getGene(genome, c));
    		c++;
    	}
    }

    for (i = 0; i < getNbNeurons(HidLayer); ++i)  /*Setting all weights for Hidden Layer*/
    {
    	for (j = 0; j < nbWeightsHid; ++j)
    	{
    		assert(c < tailleTab);
    		setWeight(getNeuron(HidLayer, i), j, getGene(genome, c));
    		c++;
    	}
    }

    assert(c == tailleTab);

    return net;
}

void regressionTestGenome()
{

}

