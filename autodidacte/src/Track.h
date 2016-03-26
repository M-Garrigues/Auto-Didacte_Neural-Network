 #ifndef H_FB_TRACK
 #define H_FB_TRACK


  /* Track.h    -----   LIF7 Auto-Didacte */


#include "Point.h"

/* Track structure*/

typedef struct {
	Point * tabPoints;
	int nbPoints;

}Track;


/* Track constructors */
Track * newTrack ();
void initTrack (Track * Track);

/* Track get/set */


/* Track functions */
void printTrack (Track * Track);


/* Track destructor */
void deleteTrack (Track * Track);







#endif