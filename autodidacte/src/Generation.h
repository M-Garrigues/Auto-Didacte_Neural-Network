#ifndef H_GENERATION
#define H_GENERATION
#include "Genome.h"
#include "stdio.h"

typedef struct
{
    int nbGen;
    int nbSubject;
    Genome ** tabGenomes;
}Generation;

Generation * newGenerationRandom(int nbSubject);
Generation * newGenerationNull(int nbSubject);
void deleteGeneration(Generation * gen);

Genome * getGenome(const Generation * gen, int i);
void setGenome(Generation ** gen, int i, Genome * genome);
int getNbGen(const Generation * gen);
void setNbGen(Generation ** gen, int nb);
int getNbSubject(const Generation * gen);
void setNbSubject(Generation ** gen, int nb);
int getNbSubject(const Generation * gen);
void setNbSubject(Generation ** gen, int nb);


void saveGeneration(const Generation * gen, FILE * f);
Generation * loadGeneration(FILE * f);
void nextGeneration(Generation ** gen);
Genome * getBest(const Generation * gen);
void updateFitnessGeneration(Generation ** gen);
void crossoverGeneration(Generation ** gen);
void mutationGeneration(Generation ** gen);

#endif