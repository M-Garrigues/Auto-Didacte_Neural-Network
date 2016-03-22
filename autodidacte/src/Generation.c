#include "Generation.h"
#include "Genome.h"
#include "assert.h"
#include "stdlib.h"

int randomProba(int * tabProba, int choices)
{
    int i;
    int result, random;
    result = 0;
    for(i = 0, i < choices;i++)
        result += tabProba[i];
    random = rand()%result;
    result = 0;
    for(i= 0; i< choices; i++){
        if(random>=result && random < result + tabProba[i])
            return i;
        result += tabProba[i];
    }

}
Generation * newGenerationRandom(int nbSubject)
{
    int i;
    Generation * pGen = malloc(sizeof(Generation));
    assert(pGen != NULL);
    pGen->nbGen = 0;
    pGen->nbSubject = nbSubject;
    pGen->tabGenomes = malloc(sizeof(Genome *)*nbSubject);
    assert(pGen->tabGenomes != NULL);
    for(i = 0; i<nbSubject;i++)
    {
        setGenome(pGen, i, newGenomeRandom(12));
    }
    return pGen;
}
Generation * newGenerationNull(int nbSubject)
{
    int i;
    Generation * pGen = malloc(sizeof(Generation));
    assert(pGen != NULL);
    pGen->nbGen = 0;
    pGen->nbSubject = nbSubject;
    pGen->tabGenomes = malloc(sizeof(Genome *)*nbSubject);
    assert(pGen->tabGenomes != NULL);
    for(i = 0; i<nbSubject;i++)
    {
        setGenome(pGen, i, newGenomeNull(12));
    }
    return pGen;
}
void deleteGeneration(Generation * gen)
{
    int i;
    for(i =0; i<gen->nbSubject; i++)
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

void setGenome(Generation * gen, int i,const Genome * genome)
{
    gen->tabGenomes[i] = genome;
}

int getNbGen(const Generation * gen)
{
    return gen->nbGen;
}

void setNbGen(Generation * gen, int num)
{
    gen->nbGen = num;
}
int getNbSubject(const Generation * gen)
{
    return gen->nbSubject;
}
void setNbSubject(Generation * gen, int nb)
{
    (gen)->nbSubject =nb;
}

void sauverGeneration(const Generation * gen, FILE * f)
{

}
void chargerGeneration(Generation * gen, FILE * f)
{
    
}

void nextGeneration(Generation * gen)
{
    updateFitnessGeneration(gen);
    crossoverGeneration(gen);
    mutationGeneration(gen);
}
void updateFitnessGeneration(Generation * gen)
{
    int i;

    for(i = 0; i<getNbSubject(gen);i++)
    {
        
        updateFitnessGenome(gen->tabGenomes[i]);
    }
}
void crossoverGeneration(Generation * gen)
{
    int * p = malloc(sizeof(int)*gen->nbSubject);
    int i,j,subject1, subject2;
    Genome ** pGenomes = gen->tabGenomes;
    gen->tabGenomes = malloc(sizeof(Genome*)*gen->nbSubject)
    setNbGen(gen , getNbGen(gen)+1);
    for(i =0;i<(gen)->nbSubject;i++)
    {
        p[i] = getFitness(getGenome(gen, i));
    }
    for(i = 0; i<gen->nbSubject;i++)
    {
        subject1 = randomProba(p, gen->nbSubject);
        subject2 = randomProba(p, gen->nbSubject);
        crossoverGenome(pGenome[subject1]
    } 
}
void mutationGeneration(Generation * gen)
{
    int i;
    for(i = 1; i<(gen)->nbSubject;i++)
    {   
        if(rand()%5 == 0)
        {
            mutation(getGenome(gen, i));
        }
    }
}
int getBest(const Generation * gen)
{
    int i,max;
    Genome * pGenome;
    max = 0;
    pGenome = NULL;
    for(i = 1; i< gen->nbSubject;i++)
        if(getFitness(gen->tabGenomes[i]) > getFitness(gen->tabGenomes[max]))
            max = i;   
   return max;
}
