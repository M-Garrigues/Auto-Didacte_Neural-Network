#ifndef H_GENOME
#define H_GENOME

/*  Genome.h ----- LIF7 Auto-Didacte */


/* Structure Genome */

typedef struct
{
    float * tabGenes;
}Genome;

/* Functions Genome */

void initGenome(Genome * genome);
//void newGenome(const Network * network, Genome * genome);
void newGenomeRandom(Genome * genome);
void newGenomeNull(Genome * genome);
void deleteGenome(Genome * genome);

float getGene(const Genome * genome, int i);
void setGene(Genome * genome, int i, float value);

void crossover(const Genome * genome1, const Genome * genome2, Genome * child);
void mutation(Genome * genome);
void displayGenome(const Genome * genome);
float fitness(const Genome * genome);
#if 0
Network * convertToNetwork(const Genome * genome);
#endif


#endif
