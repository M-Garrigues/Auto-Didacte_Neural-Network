#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif

        /*  Track.C   -----   LIF7 Auto-Didacte */

#include "Track.h"
#include "stdlib.h"
#include "assert.h"
#include "stdio.h"
#include "Point.h"
#include "stdlib.h"



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

void initTrackFile (Track * track, FILE * f){
	int i;
	float temp1;
	float temp2;
	Point * pointTemp;
	assert (track != NULL);
	assert (f != NULL);
	fscanf (f,"#nbPoints:%d\n",&i);
	initTrack (track , i);
	for (i=0 ; i< getnbPoints(track); i++){
		fscanf(f,"%f %f\n", &temp1 , &temp2);
		pointTemp = newPoint(temp1,temp2);
		setTrackIn(track ,i, pointTemp);
	}
	for (i=0 ; i< getnbPoints(track); i++){
		fscanf(f,"%f %f\n", &temp1 , &temp2);
		pointTemp = newPoint(temp1,temp2);
		setTrackOut(track ,i, pointTemp);
	}
}

void saveTrackFile (Track * track, FILE * f){
	int i;
	assert (track != NULL);
	assert (f != NULL);
	fprintf(f,"#nbPoints:%d\n",getnbPoints(track));
	for (i=0 ; i < getnbPoints(track); i++){
		fprintf(f, "%f %f\n",getX(getTrackIn(track,i)),getX(getTrackIn(track,i)));
	}
	for (i=0 ; i < getnbPoints(track); i++){
		fprintf(f, "%f %f\n",getX(getTrackOut(track,i)),getX(getTrackOut(track,i)));
	}
}

/* Track destructor */
void deleteTrack (Track * track){
	Point * pointTemp;
	int i;
	for (i=0 ; i < getnbPoints(track); i++){
		pointTemp = getTrackIn (track, i);
		deletePoint (pointTemp);
		pointTemp = getTrackOut (track, i);
		deletePoint (pointTemp);
	}
	free (track->trackIn);
	free (track->trackOut);
	free (track);
}
