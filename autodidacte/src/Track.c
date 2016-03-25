#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


	/*  Track.C   -----   LIF7 Auto-Didacte */


#include "Track.h"
#include "stdlib.h"
#include "assert.h"
#include "stdio.h"

Track * newTrack (){
	Track * nTrack;
	nTrack = malloc (sizeof(Track));
	assert (nTrack != NULL);
	return nTrack;
}

void initTrack (Track * Track){
	int i;
	printf ("Nombre de points ? :\n");
	scanf ("%d",&(Track->nbPoints));
	Track->tabPoints = malloc (Track->nbPoints*sizeof(Point));
	for (i=0 ; i < Track->nbPoints ; i++){
		printf ("Coordonnées point %d :\n",i);
		scanf ("%f",&(Track->tabPoints[i].x));
		scanf ("%f",&(Track->tabPoints[i].y));
	}
}
void printTrack (Track * Track){
	int i;
	printf ("Nombre de points  : %d\n",Track->nbPoints);
	for (i=0 ; i < Track->nbPoints ; i++){
		printf ("Coordonnées point %d :\n",i);
		printf ("%f\n",Track->tabPoints[i].x);
		printf ("%f\n",Track->tabPoints[i].y);
	}
}

void deleteTrack (Track * Track){
	free (Track->tabPoints);
	free (Track);
}