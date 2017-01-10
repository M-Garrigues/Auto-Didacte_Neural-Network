 #ifndef H_TRACK
 #define H_TRACK

#include "Point.h"
#include "stdio.h"
  /* Track.h    -----   LIF7 Auto-Didacte */




/* ----- Track structure ----- */




/**
 * @struct Track
 * @brief ...
 * 
 */
typedef struct {

	Point ** trackOut; /** Point adress array contain the outer limit */
	Point ** trackIn; /** Point adress array contain the inner limit */
	int nbPoints; /** Number of point used to draw the outer limit or the inner limit */

}Track;





/* ----- Track constructor ----- */




/**
 * @brief      Create a new track
 *
 * @return     Track adress
 */
Track * newTrack ();

/**
 * @brief      Create 2 point adress array in the track
 *
 * @param      track     Track adress
 * @param[in]  nbPoints  Number of points to draw the track
 */
void initTrack (Track * track , int nbPoints);




/* ----- Track getter/setter ----- */




/**
 * @brief      Get the track out.
 *
 * @param[in]  track     Track adress
 * @param[in]  position  Point position to return
 *
 * @return     Point adress
 */
Point * getTrackOut (const Track * track , int position);

/**
 * @brief      Set the track out.
 *
 * @param      track     Track adress
 * @param[in]  position  Point position to change
 * @param      newPoint  New point adress
 */
void setTrackOut (Track * track, int position , Point * newPoint);

/**
 * @brief      Get the track in.
 *
 * @param[in]  track     Track adress
 * @param[in]  position  Point position to return
 *
 * @return     Point adress
 */
Point * getTrackIn (const Track * track , int position);

/**
 * @brief      Set the track in.
 *
 * @param      track     Track adress
 * @param[in]  position  Point position to change
 * @param      newPoint  New point adress
 */
void setTrackIn (Track * track, int position , Point * newPoint);

/**
 * @brief      Get the nb points.
 *
 * @param[in]  track  Track adress
 *
 * @return     Number of points 
 */
int getNbPoints(const Track * track);

/**
 * @brief      Set the nb points.
 *
 * @param      track     Track adress
 * @param[in]  nbPoints  New point number
 */
void setNbPoints(Track * track , int nbPoints);




/* ----- Point function ----- */




/**
 * @brief      Print the track's information
 *
 * @param      track  Track adress
 */
void printTrack (Track * track);

/**
 * @brief      Initialize a Track from a file
 *
 * @param      track  Track adress
 * @param      f      File adress
 */
void initTrackFile (Track * track, FILE * f);

/**
 * @brief      Save a Track from a file
 *
 * @param      track  Track adress
 * @param      f      File adress
 */
void saveTrackFile (Track * track, FILE * f);


/**
 * @brief      Track's regression test.
 */
void unitTestTrack ();



/* ----- Track destructor ----- */




/**
 * @brief      Delete a track
 *
 * @param      track  Track adress
 */
void deleteTrack (Track * track);
#endif
