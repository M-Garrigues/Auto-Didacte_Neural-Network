#ifndef H_MG_POINT_SDL
#define H_MG_POINT_SDL


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

void setX(Point * p, newX);
void setY(Point * p, newY);

/* Point functions */


/* Point destructor */
void deletePoint(Point * p);

