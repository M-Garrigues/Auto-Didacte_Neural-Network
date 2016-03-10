#include "../header/Genome.h"
#include "stdlib.h"
#include "assert.h"
#include "time.h"
#include "stdio.h"

#if 0
void newGenome(const Network * network, Genome * genome)
{
    initGenome(genome);
    genome->tabGenes = malloc(9*getNbNeuronsHiddenLayer(network)*sizeof(float));
    /*  Sera fait en fonction de l'implémentation de Network */
}
#endif

/* 99 serait le nombre de liaisons si les réseaux sont en 9 - 9 -2 */
void initGenome(Genome * genome)
{
    assert(genome != NULL);
    genome->tabGenes = NULL;
}
void newGenomeRandom(Genome * genome)
{
    int i;
    initGenome(genome);
    genome->tabGenes = malloc(99*sizeof(float));
    for(i = 0; i < 99; i++)
    {
        setGene(genome,i,(rand()/(float)RAND_MAX)*(10) - 5);
    }
}

void newGenomeNull(Genome * genome)
{
    int i;
    initGenome(genome);
    genome->tabGenes = malloc(99*sizeof(float));
    for(i = 0; i < 99; i++)
    {
        setGene(genome,i, 0);
    }
}
void deleteGenome(Genome * genome)
{
    free(genome->tabGenes);
    free(genome);
}

float getGene(const Genome * genome, int i)
{
    return genome->tabGenes[i];
}

void setGene(Genome * genome, int i, float value)
{
    genome->tabGenes[i] = value;
}

void crossover(const Genome * genome1, const Genome * genome2, Genome * child)
{
    int i;
    srand(time(NULL));
    for(i = 0; i<99; i++)
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
    for(i =0; i<99; i++)
    {
        if(rand()%99 == 0)
            setGene(genome, i , getGene(genome, i) + (rand()/(float)RAND_MAX)-0.5);
    }
}

void displayGenome(const Genome * genome)
{
    int i;
    for(i = 0; i<99;i++)
    {
        printf("%f  ", getGene(genome, i));
    }
    printf("\n");
}

float fitness(const Genome * genome)
{
    /* la fonction fitness de test  fera la somme des  carrés des genes */
    int i;
    float result;
    result = 0;
    for(i = 0; i<99;i++)
    {
        result+= getGene(genome, i)*getGene(genome, i);
    }
    return result;
}
