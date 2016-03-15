#include "../header/Genome.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "assert.h"

int main()
{
    srand(time(NULL));
    int i;
    FILE * f = NULL;
    f = fopen("best.gen", "w");
    assert(f != NULL);
    Genome * g1 = newGenomeRandom(8);
    Genome * g2 = newGenomeRandom(8);
    Genome * g3 = crossover(g1, g2);
    saveGenome(g3, f);
    deleteGenome(g1);
    deleteGenome(g2);
    g1 =NULL;
    fclose(f);
    f = NULL;
    f = fopen("best.gen", "r");
    g2 = loadGenome(f);
    for(i = 0; i<(getNbInput(g3)+getNbOutput(g3))*getNbHidden(g3);i++)
    {
        printf("%d. %f : %f\n",i,getGene(g2,i), getGene(g3,i));
    }
    fclose(f);
    deleteGenome(g2);
    deleteGenome(g3);
    return 0;
}
