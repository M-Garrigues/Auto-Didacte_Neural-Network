#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


    /*  Generation.C   -----   LIF7 Auto-Didacte */


#include "Generation.h"
#include "Genome.h"
#include "assert.h"
#include "stdlib.h"

int randomProba(int * tabProba, int choices)
{
    int i;
    int result, random;
    assert(tabProba != NULL && choices > 0);
    result = 0;
    for(i = 0; i < choices;i++) /* make the summ of the probas*/
        result += tabProba[i];
    random = rand()%result;
    result = 0;
    for(i= 0; i< choices; i++){
        if(random>=result && random < result + tabProba[i]){/* the range varies due to the weights of probas*/
            return i;
        }
        result += tabProba[i];
    }
    assert(0);/* shouldn't be going there*/
}
Generation * newGenerationRandom(int nbSubject, int * species)
{
    int i;
    float activation = (rand()/(float)RAND_MAX)/2 + 0.25;/* activation is the same for a generation*/
    Generation * pGen = malloc(sizeof(Generation));
    assert(nbSubject>0);
    assert(pGen != NULL);
    pGen->nbGen = 1;
    pGen->nbSubject = nbSubject;
    pGen->tabGenomes = malloc(sizeof(Genome *)*nbSubject);
    assert(pGen->tabGenomes != NULL);
    for(i = 0; i<nbSubject;i++)
    {
        setGenome(pGen, i, newGenomeRandom(species));
        setActivationGen(getGenome(pGen,i),activation);
    }
    return pGen;
}
Generation * newGenerationNull(int nbSubject, int * species)
{
    int i;
    Generation * pGen = malloc(sizeof(Generation));
    assert(nbSubject>0);
    assert(pGen != NULL);
    pGen->nbGen = 1;
    pGen->nbSubject = nbSubject;
    pGen->tabGenomes = malloc(sizeof(Genome *)*nbSubject);
    assert(pGen->tabGenomes != NULL);
    for(i = 0; i<nbSubject;i++)
    {
        setGenome(pGen, i, newGenomeNull(species));
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
    assert(gen !=NULL);
    assert(i >= 0 && i < getNbSubject(gen));
    return gen->tabGenomes[i];
}

void setGenome(Generation * gen, int i, Genome * genome)
{
    assert(gen != NULL);
    assert(i >= 0 && i < getNbSubject(gen));
    assert(genome != NULL);
    gen->tabGenomes[i] = genome;
}

int getNbGen(const Generation * gen)
{
    assert(gen !=NULL);
    return gen->nbGen;
}

void setNbGen(Generation * gen, int num)
{
    assert(gen !=NULL);
    assert(num>0);
    gen->nbGen = num;
}
int getNbSubject(const Generation * gen)
{
    assert(gen != NULL);
    return gen->nbSubject;
}
void setNbSubject(Generation * gen, int nb)
{
    assert(gen !=NULL);
    assert(nb>0);
    (gen)->nbSubject =nb;
}


void nextGeneration(Generation * gen)
{
    assert(gen !=NULL);
    crossoverGeneration(gen);/* first step of the new generation is to crossover*/
    mutationGeneration(gen, 1);/* the second step the mutation on each genomes*/
}
void crossoverGeneration(Generation * gen)
{
    Genome * genome;
    float newActivation;
    int * p = malloc(sizeof(int)*getNbSubject(gen));/* a tab with the fitness of each genomes of gen*/
    int * rank = malloc(sizeof(int)*getNbSubject(gen));/* a tab with the rank of each genome of gen*/
    int i,j,temp,subject1, subject2;
    int tab[3] = {getNbInput(getGenome(gen, 0)), getNbHidden(getGenome(gen, 0)), getNbOutput(getGenome(gen, 0))};
    int bestGenome = getBest(gen);
    newActivation = getActivationGen(gen->tabGenomes[0])+((((rand()/(float)RAND_MAX)-0.5)*2)/(float)getFitness(getGenome(gen,bestGenome)));
    /* activation changes less with higher fitness*/
    if(newActivation<0.2)
        newActivation = 0.2;
    else if(newActivation>0.8)
        newActivation = 0.8;
    Genome ** pGenomes = gen->tabGenomes;
    assert(gen != NULL);
    gen->tabGenomes = malloc(sizeof(Genome*)*gen->nbSubject);
    setNbGen(gen , getNbGen(gen)+1);
    for(i =0;i<(gen)->nbSubject;i++)/* initialise p*/
    {
        p[i] = getFitness(pGenomes[i]);
    }
    for(i = 0;i<gen->nbSubject;i++)/* fill rank with the ranks*/
    {
        temp = 1;
        for(j = 0;j<gen->nbSubject;j++)
        {
            if(p[i]>p[j])
            {
                temp++;
            }
        }
        rank[i] = temp;
    }

    for(i = 1; i<gen->nbSubject;i++)
    {
        genome = newGenomeNull(tab);
        subject1 = randomProba(rank, gen->nbSubject);/* rank can be replaced by p to choose the by fitness selection*/
        subject2 = randomProba(rank, gen->nbSubject);/* rank can be replaced by p to choose the by fitness selection*/
        crossover(pGenomes[subject1] ,pGenomes[subject2], genome);
        setActivationGen(genome,newActivation);
        setGenome(gen, i, genome);

    }
    free(p);
    free(rank);
    setGenome(gen,0,pGenomes[bestGenome]);

    for(i =0; i<gen->nbSubject;i++){
        if(i != bestGenome){/* delete all genome exept the best that we keep in the next generation*/
            deleteGenome(pGenomes[i]);
        }
    }
    free(pGenomes);
}
void mutationGeneration(Generation * gen, int intensity)
{
    int i;
    assert(gen != NULL);
    for(i = 1; i<(gen)->nbSubject;i++)
    {   
        if(1)/* can be changed if you want less mutations*/
        {
            mutation(getGenome(gen, i), intensity);
        }
    }
}
int getBest(const Generation * gen)
{
    int i,max;
    assert(gen !=NULL);
    max = 0;

    for(i = 1; i< gen->nbSubject;i++)
        if(getFitness(gen->tabGenomes[i]) > getFitness(gen->tabGenomes[max]))
            max = i;   
   return max;
}

void loadGeneration(FILE * f, Generation * gen)
{
    int i;
    assert(f != NULL);
    assert(gen != NULL);
    fscanf(f,"#nbGen:%d\n",&i);
    setNbGen(gen, i);
    fscanf(f,"#nbSubject:%d\n",&i);
    assert(i == getNbSubject(gen));
    for(i=0;i<getNbSubject(gen);i++)
    {
        loadGenome(f,getGenome(gen,i));
    }
}
void saveGeneration(const Generation * gen, FILE * f)
{
    int i;
    assert(gen != NULL);
    assert(f != NULL);
    fprintf(f,"#nbGen:%d\n",getNbGen(gen));
    fprintf(f,"#nbSubject:%d\n",getNbSubject(gen));
    for(i=0;i<getNbSubject(gen);i++)
        saveGenome(getGenome(gen,i),f);
}
void regressionTestGeneration()
{
    FILE * f = fopen("data/testGen.gen","w+");
    int tab[3] = {5, 8, 3};
    Generation * g1 = newGenerationRandom(20, tab);
    Generation * g2 = newGenerationNull(20 , tab);
    nextGeneration(g1);
    saveGeneration(g1, f);
    rewind(f);
    loadGeneration(f,g2);
    deleteGeneration(g1);
    deleteGeneration(g2);
    fclose(f);
    printf("Generation ... OK\n");
}