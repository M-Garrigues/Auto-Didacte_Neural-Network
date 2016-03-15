#include "../header/Generation.h"
#include "../header/Genome.h"
#include "assert.h"
#include "stdlib.h"

/* 25 sera le nombre d'individus dans une generation */
Generation * newGenerationRandom()
{
    int i;
    Generation * pGen = malloc(sizeof(Generation));
    assert(pGen != NULL);
    pGen->tabGenomes = malloc(sizeof(Genome *)*25);
    for(i = 0; i<25;i++)
    {
        setGenome(&pGen, i, newGenomeRandom(8));
    }
    return pGen;
}
Generation * newGenerationNull()
{
    int i;
    Generation * pGen = malloc(sizeof(Generation));
    assert(pGen != NULL);
    pGen->tabGenomes = malloc(sizeof(Genome *)*25);
    for(i = 0; i<25;i++)
    {
        setGenome(&pGen, i, newGenomeRandom(8));
    }
    return pGen;
}
void deleteGeneration(Generation * gen)
{
    int i;
    for(i =0; i<25; i++)
    {
        deleteGenome(getGenome(gen, i));
    }
    free(gen->tabGenomes);
    free(gen);
}

Genome * getGenome(const Generation * gen, int i)
{
    return gen->tabGenomes[i];
}

void setGenome(Generation ** gen, int i, Genome * genome)
{
    (*gen)->tabGenomes[i] = genome;
}

int getNbGen(const Generation * gen)
{
    return gen->nbGen;
}

void setNbGen(Generation ** gen, int num)
{
    (*gen)->nbGen = num;
}

void sauverGeneration(const Generation * gen, FILE * f)
{

}
void chargerGeneration(Generation ** gen, FILE * f);
