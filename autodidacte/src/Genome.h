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
/**
 * @brief      Initialise a genome with random genes
 *
 * @param[in]      species a 3 int tab that contains the number of each type of neurons  
 *
 * @return     Pointer on Genome
 */
Genome * newGenomeRandom(int * species);
/**
 * @brief      Initialise a genome with null genes
 *
 * @param      species a 3 int tab that contains the number of each type of neurons
 *
 * @return     Pointer on Genome
 */
Genome * newGenomeNull(int * species);
/**
 * @brief      Delete a genome
 *
 * @param      genome is the genome to delete
 */
void deleteGenome(Genome * genome);

/* getters and setters */
/**
 * @brief      Get the gene.
 *
 * @param[in]  genome  The genome you want the gene
 * @param[in]  i       the number of the gene
 *
 * @return     The float of the gene
 */
float getGene(const Genome * genome, int i);
/**
 * @brief      Set the gene.
 *
 * @param[in,out]     genome  The genome you want to change
 * @param[in]  i       the number of the gene
 * @param[in]  value   the new value of the gene
 */
void setGene(Genome * genome, int i, float value);
/**
 * @brief      Get the nb input.
 *
 * @param[in]  genome  The genome you want the number of input neuron
 *
 * @return     The number of input neuron
 */
int getNbInput(const Genome * genome);
/**
 * @brief      Set the nb input.
 *
 * @param      genome  the genome you want to change the number of input neuron
 * @param[in]  nb The new number of input neuron
 */
void setNbInput(Genome * genome, int nb);
/**
 * @brief      Get the nb hidden.
 *
 * @param[in]  genome  The genome you want the number of hidden neuron 
 *
 * @return     the number of hidden neuron.
 */
int getNbHidden(const Genome * genome);
/**
 * @brief      Set the nb hidden.
 *
 * @param      genome   The genome you want to change the number of hidden neuron
 * @param[in]  nb 		the new number of hidden neuron
 */
void setNbHidden(Genome * genome, int nb);
/**
 * @brief      Get the nb output.
 *
 * @param[in]  genome  The genome you want the number output
 *
 * @return     the number of output neuron.
 */
int getNbOutput(const Genome * genome);
/**
 * @brief      Set the nb output.
 *
 * @param      genome  The genome you want to change the number of output neuron
 * @param[in]  nb      the new number of output neuron
 */
void setNbOutput(Genome * genome, int nb);
/**
 * @brief      Get the fitness.
 *
 * @param[in]  genome  The genome you want the fitness
 *
 * @return     the fitness.
 */
int getFitness(const Genome * genome);
/**
 * @brief      Set the fitness.
 *
 * @param      genome  The genome you want to change the fitness
 * @param[in]  value   The new fitness value
 */
void setFitness(Genome * genome, int value);

/* general functions */
/**
 * @brief      display all the data about a genome
 *
 * @param[in]  genome  The genome you want to know about
 */
void displayGenome(const Genome * genome);
/**
 * @brief      save a genome in a file
 *
 * @param[in]  genome  The genome you want to save
 * @param[out]      f       the file where you want to save genome
 */
void saveGenome(const Genome * genome, FILE * f);
/**
 * @brief      does a crossover of 2 genomes
 *
 * @param[in]  genome1  The first genome parent of the crossover
 * @param[in]  genome2  The second genome parent of the crossover
 * @param[out] child    The result of the crossover
 */
void crossover(const Genome * genome1, const Genome * genome2, Genome * child);
/**
 * @brief      does a mutation on a genome
 *
 * @param      genome  The genome you want to mutate
 */
void mutation(Genome * genome);
/**
 * @brief      load a genome from a file
 *
 * @param      f       the file where the genome is
 * @param      genome  The genome where will be stored the genome
 */
void loadGenome(FILE * f, Genome * genome);
/**
 * @brief      convert a genome into a network
 *
 * @param[in]  genome  The genome you want to convert
 *
 * @return     A pointer on the network
 */
Network * convertToNetwork(const Genome * genome);
/**
 * @brief      the unit test of genome
 */
void regressionTestGenome();



#endif
