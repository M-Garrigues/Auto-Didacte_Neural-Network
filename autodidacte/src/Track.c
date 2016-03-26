#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif

        /*  Track.C   -----   LIF7 Auto-Didacte */

#include "Track.h"
#include "stdlib.h"
#include "assert.h"
#include "stdio.h"
#include "Point.h"



/* Track constructors */
Track * newTrack (){
	Track * nTrack;
	nTrack = malloc (sizeof(Track));
	assert (nTrack != NULL);
	return nTrack;

}
void initTrack (Track * track , int IN , int OUT){
	assert (track != NULL);
	setnbPointIn (track , IN);
	setnbPointOut (track , OUT);
	track->trackIn = malloc(IN * sizeof(Point));
	track->trackOut = malloc(OUT * sizeof(Point));
	assert (track->trackIn != NULL);
	assert (track->trackOut != NULL);

}


/*Track Get/Set */

Point * getTrackOut (const Track * track , int position){
	assert (track != NULL);
	assert (position < getnbPointOut(track));
	return track->trackOut[position];

}

void setTrackOut (Track * track , int position , Point * newPoint){
	assert (track != NULL);
	assert (position < getnbPointOut(track));
	track->trackOut[position] = newPoint;
}

int getnbPointIn (const Track * track){
	assert (track != NULL);
	return track->nbPointIn;
}
void setnbPointIn (Track * track , int nbPoints){
	assert (track != NULL);
	track->nbPointIn = nbPoints;
}
int getnbPointOut (const Track * track){
	assert (track != NULL);
	return track->nbPointOut;
}
void setnbPointOut (Track * track , int nbPoints){
	assert (track != NULL);
	track->nbPointOut = nbPoints;
}

Point * getTrackIn (const Track * track , int position){
	assert (track != NULL);
	assert (position < getnbPointIn(track));
	return track->trackIn[position];
}
void setTrackIn (Track * track , int position , Point * newPoint){
	assert (track != NULL);
	assert (position < getnbPointIn(track));
	track->trackIn[position] = newPoint;
}



/* Track functions */
void printTrack (Track * track){
	Point * pointTemp;
	int counter;
	assert (track != NULL);
	for (counter = 0 ; counter < getnbPointIn(track) ; counter++){
		pointTemp = getTrackIn(track , counter);
		printf("Point intérieur n° %d : %f , %f\n",counter ,getX(pointTemp), getY(pointTemp));
	}
	for (counter = 0 ; counter < getnbPointOut(track) ; counter++){
		pointTemp = getTrackOut(track , counter);
		printf("Point extérieur n° %d : %f , %f\n",counter ,getX(pointTemp), getY(pointTemp));
	}
}


/* Track destructor */
void deleteTrack (Track * track){
	free (track->trackIn);
	free (track->trackOut);
	free (track);
}
