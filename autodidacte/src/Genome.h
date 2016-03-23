#ifndef H_GENOME
#define H_GENOME


/*  Genome.h ----- LIF7 Auto-Didacte */


#include "stdio.h"
#include "Network.h"


/* Structure Genome */

typedef struct
{
    int nbInput;
    int nbHidden;
    int nbOutput;
    int fitness;
    float * tabGenes;
}Genome;

/* Functions Genome */


/* constructors and destructor */
Genome * newGenomeRandom(int species);
Genome * newGenomeNull(int species);
void deleteGenome(Genome * genome);

/* getters and setters */
float getGene(const Genome * genome, int i);
void setGene(Genome * genome, int i, float value);
int getNbInput(const Genome * genome);
void setNbInput(Genome * genome, int nb);
int getNbHidden(const Genome * genome);
void setNbHidden(Genome * genome, int nb);
int getNbOutput(const Genome * genome);
void setNbOutput(Genome * genome, int nb);
int getFitness(const Genome * genome);
void setFitness(Genome * genome, int value);

/* general functions */
void updateFitnessGenome(Genome * genome);
void displayGenome(const Genome * genome);
void saveGenome(const Genome * genome, FILE * f);
void crossover(const Genome * genome1, const Genome * genome2, Genome * child);
void mutation(Genome * genome);
void loadGenome(FILE * f, Genome * genome);
Network * convertToNetwork(const Genome * genome);
void regressionTestGenome();



#endif
