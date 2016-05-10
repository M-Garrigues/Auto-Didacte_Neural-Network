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
Point * middle (Point * p1, Point * p2){
	Point * pointMiddle = newPoint((getX(p1) + getX(p2))/2,(getY(p1) + getY(p2))/2);
	return pointMiddle;
}

float distance (Point * p1, Point * p2){
	float distance;
	distance = sqrt ((getX(p1)-getX(p2))*(getX(p1)-getX(p2)) +(getY(p1)-getY(p2))*(getY(p1)-getY(p2)));
	return distance;
}

float distanceCheck (float f){
	if (f >=40)
	{
		return 0;
	}
	else return (1-f/40);
}

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

float minimum (float f1, float f2, float f3, float f4){
	if (f1 < f2)
	{
		if (f1 < f3)
		{
			if (f1 < f4)
			{
				return f1;
			}
			else return f4;
		}
		else
		{
			if (f3 < f4)
			{
				return f3;
			}
			else return f4;
		}
	}
	else 
	{
		if (f2 < f3)
		{
			if (f2 < f4)
			{
				return f2;
			}
			else return f4;
		}
		else
		{
			if (f3 < f4)
			{
				return f3;
			}
			else return f4;
		}
	}
}

/* droites p1p2 et p3p4 */
int intersect (Point * A, Point * B , Point * C , Point * D){

        float Ix, Iy, Jx, Jy;
        float Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
        float m, k;
        Ax = getX(A);
        Ay = getY(A);
        Bx = getX(B);

        By = getY(B);
        Cx = getX(C);
        Cy = getY(C);
        Dx = getX(D);
        Dy = getY(D);

        Ix = (Ax-Bx);
        Iy = (Ay-By);
        Jx = (Cx-Dx);
        Jy = (Cy-Dy);

        m = (-Ix*Ay + Ix*Cy + Iy*Ax - Iy*Cx)/(Ix*Jy - Iy*Jx);
        k = ( Ax*Jy - Cx*Jy - Jx*Ay + Jx*Cy)/(Ix*Jy - Iy*Jx);
        if((k>=0 && k<=1)&&(m>=0 && m<=1))
            return 1;
        else
            return 0;
    }


Point * intersectPoint (Point * A, Point * B , Point * C , Point * D){

        float Ix, Iy, Jx, Jy;
        float Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
        float m;
        Point * P;

        P = malloc(sizeof(Point));

        Ax = getX(A);
        Ay = getY(A);
        Bx = getX(B);
        By = getY(B);
        Cx = getX(C);
        Cy = getY(C);
        Dx = getX(D);
        Dy = getY(D);

        Ix = (Ax-Bx);
        Iy = (Ay-By);
        Jx = (Cx-Dx);
        Jy = (Cy-Dy);

        m = -(-Ix*Ay + Ix*Cy + Iy*Ax - Iy*Cx)/(Ix*Jy - Iy*Jx);
      

        setX(P, Cx + m* Jx);
        setY(P, Cy + m* Jy);

        return P;
    }


/* Point destructor */
void deletePoint(Point * p)
{
	assert(p != NULL);

	p->x = 0;
	p->y = 0;

	free(p);
}