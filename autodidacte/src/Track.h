 #ifndef H_TRACK
 #define H_TRACK

#include "Point.h"
  /* Track.h    -----   LIF7 Auto-Didacte */

/* structure Track */
typedef struct {

	Point ** trackOut;
	Point ** trackIn;
	int nbPointIn;
	int nbPointOut;

}Track;

/* Track constructors */
Track * newTrack ();
void initTrack (Track * track , int IN , int OUT);


/* Track Get/Set */
Point * getTrackOut (const Track * track , int position);
void setTrackOut (Track * track, int position , Point * newPoint);
Point * getTrackIn (const Track * track , int position);
void setTrackIn (Track * track, int position , Point * newPoint);
int getnbPointIn (const Track * track);
void setnbPointIn (Track * track , int nbPoints);
int getnbPointOut (const Track * track);
void setnbPointOut (Track * track , int nbPoints);
void printTrack (Track * track);


/* Track functions */
void printTrack (Track * track);




/* Track destructor */
void deleteTrack (Track * track);
#endif
