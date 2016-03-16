#include "Generation.h"
#include "Genome.h"
#include "assert.h"
#include "stdlib.h"


Generation * newGenerationRandom(int nbSubject)
{
    int i;
    Generation * pGen = malloc(sizeof(Generation));
    assert(pGen != NULL);
    pGen->nbGen = 0;
    pGen->nbSubject = nbSubject;
    pGen->tabGenomes = malloc(sizeof(Genome *)*nbSubject);
    for(i = 0; i<nbSubject;i++)
    {
        setGenome(&pGen, i, newGenomeRandom(12));
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
    for(i = 0; i<nbSubject;i++)
    {
        setGenome(&pGen, i, newGenomeNull(12));
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
int getNbSubject(const Generation * gen)
{
    return gen->nbSubject;
}
void setNbSubject(Generation ** gen, int nb)
{
    (*gen)->nbSubject =nb;
}

void sauverGeneration(const Generation * gen, FILE * f)
{

}
void chargerGeneration(Generation ** gen, FILE * f)
{
    
}

void nextGeneration(Generation ** gen)
{
    Genome * pG1;
    int i;
    updateFitnessGeneration(gen);
    pG1 = getBest(*gen);
    printf("Gen: %d -> Bestfitness %f\n",getNbGen(*gen),getFitness(pG1));
    free(pG1);
    /* saveGeneraton */
    crossoverGeneration(gen);
    mutationGeneration(gen);
}
void updateFitnessGeneration(Generation ** gen)
{
    int i;

    for(i = 0; i<getNbSubject(*gen);i++)
    {
        
        updateFitnessGenome(&(*gen)->tabGenomes[i]);
    }
}
void crossoverGeneration(Generation ** gen)
{
    Genome * g1;
    float tempF;
    float * p = malloc(sizeof(float)*(*gen)->nbSubject);
    int * p2 = malloc(sizeof(int)*(*gen)->nbSubject);
    int r1,r2,i,j,k,l,m;
    Generation * temp = newGenerationNull((*gen)->nbSubject);

    setNbGen(&temp, getNbGen(*gen)+1);

    for(i =0;i<(*gen)->nbSubject;i++)
    {
        p[i] = getFitness(getGenome(*gen, i));
        p2[i] = i;
    }

    for(j=0; j<(*gen)->nbSubject;j++)
    {
        for(i = 1;i<(*gen)->nbSubject;i++)
        {
            if(p[i-1]>p[i])
            {
                tempF = p[i-1];
                p[i-1] = p[i];
                p[i] = tempF;
                k = p2[i-1];
                p2[i-1] = p2[i];
                p2[i] = k;
            }
        }
    }
    free(p);
    for(j = 1;j<(*gen)->nbSubject;j++)
    {
        r1 = rand()%(10*(*gen)->nbSubject*((*gen)->nbSubject+1)/2);
        r2 = rand()%(10*(*gen)->nbSubject*((*gen)->nbSubject+1)/2);
        m = ((*gen)->nbSubject)*10;
        for(i = 0; i<(*gen)->nbSubject;i++)
        {
            if(r1 <= m)
                k = i;
            if(r2 <= m)
                l = i;
            m += ((*gen)->nbSubject - (i+1))*10;
        }
        g1 =newCrossover(getGenome(*gen, k), getGenome(*gen,l));
        deleteGenome(getGenome(temp,j));
        setGenome(&temp,j,g1);
    }
    deleteGenome(getGenome(temp,0));
    setGenome(&temp, 0, getBest(*gen));
    free(p2);
    deleteGeneration((*gen));
    *gen = temp;
}
void mutationGeneration(Generation ** gen)
{
    int i;
    Genome * temp;
    for(i = 1; i<(*gen)->nbSubject;i++)
    {
        temp = newMutation(getGenome(*gen, i));
        deleteGenome(getGenome(*gen, i));
        setGenome(gen, i, temp);
    }
}
Genome * getBest(const Generation * gen)
{
    int i,max;
    Genome * pGenome;
    max = 0;
    pGenome = NULL;
    for(i = 1; i< gen->nbSubject;i++)
        if(getFitness(gen->tabGenomes[i]) > getFitness(gen->tabGenomes[max]))
            max = i;   
   
    pGenome = newGenomeNull(getNbHidden(getGenome(gen, max)));
    setFitness(&pGenome, getFitness(gen->tabGenomes[max]));
    for(i = 0; i< (getNbInput(getGenome(gen, max)) + getNbOutput(getGenome(gen, max)))*getNbHidden(getGenome(gen, max));i++)
        setGene(&pGenome, i , getGene(getGenome(gen, max), i)); 
    return pGenome;
}
