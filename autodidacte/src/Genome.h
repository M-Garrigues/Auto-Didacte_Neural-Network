#ifndef H_GENOME
#define H_GENOME
#include "stdio.h"
/*  Genome.h ----- LIF7 Auto-Didacte */


/* Structure Genome */

typedef struct
{
    int nbInput;
    int nbHidden;
    int nbOutput;
    float fitness;
    float * tabGenes;
}Genome;

/* Functions Genome */


/* constructors and destructor */
Genome * newGenomeRandom(int species);
Genome * newGenomeNull(int species);
void deleteGenome(Genome * genome);

/* getters and setters */
float getGene(const Genome * genome, int i);
void setGene(Genome ** genome, int i, float value);
int getNbInput(const Genome * genome);
void setNbInput(Genome ** genome, int nb);
int getNbHidden(const Genome * genome);
void setNbHidden(Genome ** genome, int nb);
int getNbOutput(const Genome * genome);
void setNbOutput(Genome ** genome, int nb);
float getFitness(const Genome * genome);
void setFitness(Genome ** genome, float value);

/* general functions */
Genome * crossover(const Genome * genome1, const Genome * genome2);
Genome * mutation(const Genome * genome);
void updateFitnessGenome(Genome ** genome);
void displayGenome(const Genome * genome);
void saveGenome(const Genome * genome, FILE * f);
Genome * loadGenome(FILE * f);
#if 0
Network * convertToNetwork(const Genome * genome);
#endif
void regressionTest();



#endif
