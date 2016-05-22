#ifndef H_VG_GENERATION
#define H_VG_GENERATION


  /* Generation.h    -----   LIF7 Auto-Didacte */


#include "Genome.h"

/* structure Generation*/

typedef struct
{
    int nbGen;
    int nbSubject;
    Genome ** tabGenomes;
}Generation;


/* Functions Genome */

/* Constructors and destructor */
/**
 * @brief      Creates a generation with random genomes
 *
 * @param[in]  nbSubject  The number of genomes in the generation
 * @param      species    The species of the genomes
 *
 * @return     A pointer on the generation
 */
Generation * newGenerationRandom(int nbSubject, int * species);
/**
 * @brief      Creates a generation with null genomes
 *
 * @param[in]  nbSubject  The number of genomes
 * @param      species    The species of the genomes
 *
 * @return     A pointer on the generation
 */
Generation * newGenerationNull(int nbSubject, int * species);
/**
 * @brief      Deletes a generation
 *
 * @param      gen   The generation to delete
 */
void deleteGeneration(Generation * gen);

/* Getters / Setters */
/**
 * @brief      Get the ith genome.
 *
 * @param[in]  gen   The generation you want the genome
 * @param[in]  i     the number of the genome
 *
 * @return     Genome.
 */
Genome * getGenome(const Generation * gen, int i);
/**
 * @brief      Set the ith genome.
 *
 * @param      gen     The generation you want to change the genome
 * @param[in]  i       the number of the genome
 * @param      genome  The new genome
 */
void setGenome(Generation * gen, int i, Genome * genome);
/**
 * @brief      Get the nb gen.
 *
 * @param[in]  gen   The generation you want the number
 *
 * @return     Nb gen.
 */
int getNbGen(const Generation * gen);
/**
 * @brief      Set the nb gen.
 *
 * @param      gen   The generation you want to change the number 
 * @param[in]  nb    the new number of generation
 */
void setNbGen(Generation * gen, int nb);
/**
 * @brief      Get the nb subject.
 *
 * @param[in]  gen   The generation you want the number of genomes
 *
 * @return     Nb subject.
 */
int getNbSubject(const Generation * gen);
/**
 * @brief      Set the nb subject.
 *
 * @param      gen   The generation you want to change the number of genomes
 * @param[in]  nb    the new number of genomes
 */
void setNbSubject(Generation * gen, int nb);

/* general functions */
/**
 * @brief      save a generation in a file
 *
 * @param[in]  gen   The generation to save
 * @param      f     the file where you save the generation
 */
void saveGeneration(const Generation * gen, FILE * f);
/**
 * @brief      load a generaton from a file
 *
 * @param      f     the file where you load the generation
 * @param      gen   The generation where is stored
 */
void loadGeneration(FILE * f, Generation * gen);
/**
 * @brief      Go to the next generation 
 *
 * @param      gen   The generation 
 */
void nextGeneration(Generation * gen);
/**
 * @brief      Get the best genome of a generation.
 *
 * @param[in]  gen   The generation you want the best genome
 *
 * @return     the number of th best genome.
 */
int getBest(const Generation * gen);
/**
 * @brief      does a crossover on all the genomes in a generation
 *
 * @param      gen   The generation to do the crossover on
 */

void crossoverGeneration(Generation * gen);
/**
 * @brief      does a mutation on some of the genomes from a generation
 *
 * @param      gen   The generation to do the mutation on
 */
void mutationGeneration(Generation * gen, int intensity);
/**
 * @brief      the unit test of generation
 */
void regressionTestGeneration();
#endif