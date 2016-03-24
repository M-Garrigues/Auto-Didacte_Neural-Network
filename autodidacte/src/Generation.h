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
Generation * newGenerationRandom(int nbSubject);
Generation * newGenerationNull(int nbSubject);
void deleteGeneration(Generation * gen);

/* Getters / Setters */
Genome * getGenome(const Generation * gen, int i);
void setGenome(Generation * gen, int i, Genome * genome);
int getNbGen(const Generation * gen);
void setNbGen(Generation * gen, int nb);
int getNbSubject(const Generation * gen);
void setNbSubject(Generation * gen, int nb);
int getNbSubject(const Generation * gen);
void setNbSubject(Generation * gen, int nb);

/* general functions */
void saveGeneration(const Generation * gen, FILE * f);
void loadGeneration(FILE * f, Generation * gen);
void nextGeneration(Generation * gen);
int getBest(const Generation * gen);
void updateFitnessGeneration(Generation * gen);
void crossoverGeneration(Generation * gen);
void mutationGeneration(Generation * gen);
void regressionTestGeneration();
#endif