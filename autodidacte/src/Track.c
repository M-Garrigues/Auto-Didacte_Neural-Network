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
void initTrack (Track * track , int nbPoints){
	assert (track != NULL);
	setnbPoints(track, nbPoints);
	track->trackIn = malloc(nbPoints * sizeof(Point));
	track->trackOut = malloc(nbPoints * sizeof(Point));
	assert (track->trackIn != NULL);
	assert (track->trackOut != NULL);

}


/*Track Get/Set */

Point * getTrackOut (const Track * track , int position){
	assert (track != NULL);
	assert (position < getnbPoints(track));
	return track->trackOut[position];

}

void setTrackOut (Track * track , int position , Point * newPoint){
	assert (track != NULL);
	assert (position < getnbPoints(track));
	track->trackOut[position] = newPoint;
}

int getnbPoints(const Track * track){
	assert (track != NULL);
	return track->nbPoints;
}
void setnbPoints(Track * track , int newNbPoints){
	assert (track != NULL);
	track->nbPoints = newNbPoints;
}

	

Point * getTrackIn (const Track * track , int position){
	assert (track != NULL);
	assert (position < getnbPoints(track));
	return track->trackIn[position];
}
void setTrackIn (Track * track , int position , Point * newPoint){
	assert (track != NULL);
	assert (position < getnbPoints(track));
	track->trackIn[position] = newPoint;
}



/* Track functions */
void printTrack (Track * track){
	Point * pointTemp;
	int counter;
	assert (track != NULL);
	for (counter = 0 ; counter < getnbPoints(track) ; counter++){
		pointTemp = getTrackIn(track , counter);
		printf("Point intérieur n° %d : %f , %f\n",counter ,getX(pointTemp), getY(pointTemp));
	}
	for (counter = 0 ; counter < getnbPoints(track) ; counter++){
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
