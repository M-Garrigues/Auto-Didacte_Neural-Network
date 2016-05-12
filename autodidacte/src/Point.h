#ifndef H_MG_POINT
#define H_MG_POINT


  /* Point.h    -----   LIF7 Auto-Didacte */


/**
 * @struct Point
 * @brief Points are used for calculation and for dispaly 
 * 
 */
typedef struct
{
	float x; /** Point abciss */
	float y; /** Point ordonate*/
}Point;


/* ----- Point constructor ----- */

/**
 * @brief      Create a new point
 *
 * @param[in]  X     Abciss of the new point
 * @param[in]  Y     Ordinate of the new point
 *
 * @return     New point adress
 */
Point * newPoint(float X, float Y);




/* ----- Point getter/setter ----- */


/**
 * @brief      Get the x
 *
 * @param      p     Point adress
 *
 * @return     Point abciss
 */
float getX(Point * p);


/**
 * @brief      Get the y.
 *
 * @param      p     Point adress
 *
 * @return    Point ordonate
 */
float getY(Point * p);

/**
 * @brief      Set the x.
 *
 * @param      p     Point adress
 * @param[in]  newX  New abciss for the point
 */
void setX(Point * p, float newX);


/**
 * @brief      Set the y.
 *
 * @param      p     Point adress
 * @param[in]  newY  New ordonate for the point
 */
void setY(Point * p, float newY);






/* ----- Point functions ----- */



/**
 * @brief      Apply a rotation to a point
 *
 * @param      pointInit  Adress of the point to apply rotation
 * @param      centre     Center of the rotation
 * @param[in]  angle      Angle of the rotation
 *
 * 
 */
void rotation (Point * pointInit, Point * centre ,float angle);

/**
 * @brief      Distance between two points
 *
 * @param      p1    1st point adress
 * @param      p2    2nd point adress
 *
 * @return     distance between two points
 */
float distance (Point * p1, Point * p2);



/**
 * @brief      Give the intersection of (p1,p2) and (p3,p3)
 *
 * @param      p1    1st point adress of the 1st segment 
 * @param      p2    2nd point adress of the 1st segment
 * @param      p3    1st point adress of the 2nd segment
 * @param      p4    2nd point adress of the 2nd segment
 *
 * @return     Intersection point adress 
 */
Point * intersectPoint (Point * p1 , Point * p2 , Point * p3 , Point * p4);


/**
 * @brief      Middle 
 *
 * @param      p1    1st point adress
 * @param      p2    2nd point adress
 *
 * @return    Middle point adress
 */
Point * middle (Point * p1, Point * p2);



/**
 * @brief      Return the minimum between nb float
 *
 * @param[in]  f1    tab of nb numbers
 * @param[in]  nb 	 the number of numbers
 *
 * @return     Minimum 
 */
float minimum (float * f1, int nb);

/**
 * @brief      Return 1 if [p1,p2] intersect with [p3,p4] and 0 else
 *
 * @param      p1    1st point adress of the 1st segment 
 * @param      p2    2nd point adress of the 1st segment
 * @param      p3    1st point adress of the 2nd segment
 * @param      p4    2nd point adress of the 2nd segment
 *
 * @return    1 or 0
 */
int intersect (Point * p1 , Point * p2 , Point * p3 , Point * p4);




/* ----- Point destructor ----- */


/**
 * @brief      Delete and free a point
 *
 * @param      p     Point adress
 */
void deletePoint(Point * p);
#endif