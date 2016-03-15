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
        setGene(&pGenome,i,(rand()/(float)RAND_MAX)*(10) - 5);
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
        setGene(&pGenome,i, 0);
    }
    return pGenome;
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

void setGene(Genome ** genome, int i, float value)
{
    (*genome)->tabGenes[i] = value;
}

int getNbInput(const Genome * genome)
{
    return genome->nbInput;
}
void setNbInput(Genome ** genome, int nb)
{
    (*genome)->nbInput = nb;
}
int getNbHidden(const Genome * genome)
{
    return genome->nbHidden;
}
void setNbHidden(Genome ** genome, int nb)
{
    (*genome)->nbHidden = nb;
}
int getNbOutput(const Genome * genome)
{
    return genome->nbOutput;
}
void setNbOutput(Genome ** genome, int nb)
{
    (*genome)->nbOutput = nb;
}
float getFitness(const Genome * genome)
{
    return genome->fitness;
}
void setFitness(Genome ** genome, float value)
{
    (*genome)->fitness = value;
}




Genome * crossover(const Genome * genome1, const Genome * genome2)
{
    assert(genome1->nbHidden == genome2->nbHidden);  /*same species*/
    int i;
    Genome * child = malloc(sizeof(Genome));
    child->nbInput = 6;
    child->nbHidden = getNbHidden(genome1);
    child->nbOutput = 2;
    child->fitness =0;
    child->tabGenes = malloc((getNbInput(child)+getNbOutput(child))*getNbHidden(child)*sizeof(float));
    for(i = 0; i< (getNbInput(child) + getNbOutput(child))*getNbHidden(child); i++)
    {
        if(rand()%2)
            setGene(&child, i , getGene(genome1, i));
        else
            setGene(&child, i , getGene(genome2, i));
    }
    return child;
}

void mutation(Genome ** genome)
{
    int i;
    for(i =0; i<(getNbInput(*genome) + getNbOutput(*genome))*getNbHidden(*genome); i++)
    {
        if(rand()%(getNbInput(*genome) + getNbOutput(*genome))*getNbHidden(*genome) == 0)
            setGene(genome, i , getGene((*genome), i) + (rand()/(float)RAND_MAX)-0.5);
    }
}

void displayGenome(const Genome * genome)
{
    int i;
    for(i = 0; i<(getNbInput(genome) + getNbOutput(genome))*getNbHidden(genome);i++)
    {
        printf("%f", getGene(genome, i));
    }
    printf("\n");
}


void saveGenome(const Genome * genome, FILE * f)
{
    int i;
    fprintf(f,"#nbInput:%d\n",getNbInput(genome));
    fprintf(f,"#nbHidden:%d\n",getNbHidden(genome));
    fprintf(f,"#nbOutput:%d\n",getNbOutput(genome));
    fprintf(f,"#fitness:%f\n",getFitness(genome));
    for(i=0;i<(getNbInput(genome) + getNbOutput(genome))*getNbHidden(genome);i++)
        fprintf(f, "%f ", getGene(genome, i));
    fprintf(f, "\n");
}

Genome * loadGenome(FILE * f)
{
    int i;
    float a;
    Genome * pGenome = malloc(sizeof(Genome));
    fscanf(f,"#nbInput:%d\n",&i);
    setNbInput(&pGenome, i);
    fscanf(f,"#nbHidden:%d\n",&i);
    setNbHidden(&pGenome, i);
    fscanf(f,"#nbOutput:%d\n",&i);
    setNbOutput(&pGenome, i);
    fscanf(f, "#fitness:%f\n",&a);
    setFitness(&pGenome, a);
    pGenome->tabGenes = malloc((getNbInput(pGenome) + getNbOutput(pGenome))*getNbHidden(pGenome)*sizeof(float));
    for(i = 0; i< (getNbInput(pGenome) + getNbOutput(pGenome))*getNbHidden(pGenome); i++)
    {
        fscanf(f,"%f ", &a);
        setGene(&pGenome, i, a);
    }
    fscanf(f,"\n");
    return pGenome;
}
#if 0
Network * convertToNetwork(const Genome * genome)
{
    Network * pNet = malloc(sizeof(Network));

}
#endif
void regressionTest()
{
    Genome * p1,p2,p3;

}

