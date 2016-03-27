#ifndef H_MG_POINT
#define H_MG_POINT


  /* Point.h    -----   LIF7 Auto-Didacte */

typedef struct
{
	float x;
	float y;
}Point;

/* Point constructors */
Point * newPoint(float X, float Y);

/* Point get/set */
float getX(Point * p);
float getY(Point * p);

void setX(Point * p, float newX);
void setY(Point * p, float newY);

/* Point functions */
Point * rotation (Point * pointInit, Point * centre ,float angle);
/* droites p1p2 et p3p4 */
int intersect (Point * p1 , Point * p2 , Point * p3 , Point * p4);

/* Point destructor */
void deletePoint(Point * p);

#endif