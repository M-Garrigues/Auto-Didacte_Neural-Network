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
 * @param[in]  p     Point adress
 *
 * @return     Point abciss
 */
float getX(const Point * p);


/**
 * @brief      Get the y.
 *
 * @param[in]  p     Point adress
 *
 * @return    Point ordonate
 */
float getY(const Point * p);

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
 * @param[in]  centre     Center of the rotation
 * @param[in]  angle      Angle of the rotation
 *
 * 
 */
void rotation (Point * pointInit,const Point * centre ,float angle);

/**
 * @brief      Distance between two points
 *
 * @param[in]   p1    1st point adress
 * @param[in]   p2    2nd point adress
 *
 * @return     distance between two points
 */
float distance (const Point * p1,const Point * p2);



/**
 * @brief      Give the intersection of (p1,p2) and (p3,p3)
 *
 * @param[in]   p1    1st point adress of the 1st segment 
 * @param[in]   p2    2nd point adress of the 1st segment
 * @param[in]   p3    1st point adress of the 2nd segment
 * @param[in]   p4    2nd point adress of the 2nd segment
 *
 * @return     Intersection point adress 
 */
Point * intersectPoint (const Point * p1 ,const Point * p2 ,const Point * p3 ,const Point * p4);


/**
 * @brief      Middle 
 *
 * @param[in]   p1    1st point adress
 * @param[in]   p2    2nd point adress
 *
 * @return    Middle point adress
 */
Point * middle (const Point * p1,const Point * p2);



/**
 * @brief      Return the minimum between nb float
 *
 * @param[in]  f1    tab of nb numbers
 * @param[in]  nb 	 the number of numbers
 *
 * @return     Minimum 
 */
float minimum (const float * f1, int nb);

/**
 * @brief      Return 1 if [p1,p2] intersect with [p3,p4] and 0 else
 *
 * @param[in]   p1    1st point adress of the 1st segment 
 * @param[in]   p2    2nd point adress of the 1st segment
 * @param[in]   p3    1st point adress of the 2nd segment
 * @param[in]   p4    2nd point adress of the 2nd segment
 *
 * @return    1 or 0
 */
int intersect (const Point * p1 ,const Point * p2 ,const Point * p3 ,const Point * p4);




/* ----- Point destructor ----- */


/**
 * @brief      Delete and free a point
 *
 * @param      p     Point adress
 */
void deletePoint(Point * p);


/**
 * @brief      Regression test for point
 */
void unitTestPoint ();
#endif