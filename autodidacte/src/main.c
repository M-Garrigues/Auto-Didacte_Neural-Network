#include "../header/Genome.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main()
{
    srand(time(NULL));
    int i,j;
    j = 0;
    Genome g1,g2,g3;
    printf("Auto-Diacte \n\n");
    newGenomeRandom(&g1);
    newGenomeRandom(&g2);
    newGenomeNull(&g3);
    crossover(&g1,&g2,&g3);
    mutation(&g3);
    for(i = 0; i<99; i++)
    {
        if(getGene(&g1,i)==getGene(&g3,i))
            j++;
    }
    printf("g1 et g3 on %d genes en commun\n", j);
    printf("Les fitness sont:\n\n g1 : %f \n g2 : %f\n g3 : %f\n",fitness(&g1),fitness(&g2),fitness(&g3));
    deleteGenome(&g1);
    deleteGenome(&g2);
    deleteGenome(&g3);
    return 0;
}
