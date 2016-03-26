#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


	/*  Point.C   -----   LIF7 Auto-Didacte */


#include "Point.h"
#include "stdlib.h"
#include "assert.h"
#include "math.h"
#include "stdio.h"


/* Point constructors */
Point * newPoint(float X, float Y)
{
	Point * p = NULL;
	p = malloc(sizeof(Point));
	assert(p != NULL);

	p->x = X;
	p->y = Y;

	return p;
}

/* Point get/set */
float getX(Point * p)
{
	assert(p != NULL);
	return(p->x);
}
float getY(Point * p)
{
	assert(p != NULL);
	return(p->y);
}

void setX(Point * p, float newX)
{
	assert(p != NULL);
	p->x = newX;
}
void setY(Point * p, float newY)
{
	assert(p != NULL);
	p->y = newY;
}

/* Point functions */

Point * rotation (Point * pointInit, Point * centre ,float angle){

	float pfX, pfY, piX, piY, cX, cY;
	Point * pointFinal = newPoint(0,0);

	piX = getX(pointInit);
	piY = getY(pointInit);

	cX = getX(centre);
	cY = getY(centre);

	pfX = (piX - cX)*cos(angle) - (piY - cY)*sin(angle) + cX;
	pfY = (piY - cY)*cos(angle) + (piX - cX)*sin(angle) + cY;

	setX(pointFinal, pfX);
	setY(pointFinal, pfY);

	return pointFinal;	
}

/* Point destructor */
void deletePoint(Point * p)
{
	assert(p != NULL);

	p->x = 0;
	p->y = 0;

	free(p);
}