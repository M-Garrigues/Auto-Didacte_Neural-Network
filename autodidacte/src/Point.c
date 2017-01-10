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
float getX(const Point * p)
{
	assert(p != NULL);
	return(p->x);
}
float getY(const Point * p)
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
Point * middle (const Point * p1, const Point * p2){
	Point * pointMiddle = newPoint((getX(p1) + getX(p2))/2,(getY(p1) + getY(p2))/2);
	return pointMiddle;
}

float distance (const Point * p1, const Point * p2){
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

void rotation (Point * pointInit,const Point * centre ,float angle){

	float pfX, pfY, piX, piY, cX, cY;

	piX = getX(pointInit);
	piY = getY(pointInit);

	cX = getX(centre);
	cY = getY(centre);

	pfX = (piX - cX)*cos(angle) - (piY - cY)*sin(angle) + cX;
	pfY = (piY - cY)*cos(angle) + (piX - cX)*sin(angle) + cY;

	setX(pointInit, pfX);
	setY(pointInit, pfY);	
}

float minimum (const float * f1, int nb){
	int i;
	int min  = 0;
	for(i = 1; i < nb;i++)
	{
		if(f1[i]<f1[min])
			min = i;
	}
	return f1[min];
}

/* droites p1p2 et p3p4 */
int intersect (const Point * A, const Point * B , const Point * C , const Point * D){

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


Point * intersectPoint (const Point * A, const Point * B , const Point * C , const Point * D){

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


void unitTestPoint ()
{
	Point *p1, *p2, *p3, *p4, *p5, *p6;
 	p1 = newPoint(-10,0);
 	p2 = newPoint(10,0);
 	p3 = newPoint(10,10);
 	p4 = newPoint(-10,-10);
 	assert (getX(p1)==-10);
 	assert (getY(p3)==10);
 	assert (intersect(p1,p2,p3,p4)==1);
 	p5 = intersectPoint(p1,p2,p3,p4);
 	assert (getX(p5)==0);
 	assert (getY(p5)==0);
 	setX(p4,20);
 	setY(p4,10);
 	setX(p1,20);
 	assert (intersect(p1,p2,p3,p4)==0);
 	p6 = middle (p2,p3);
 	assert (getX(p6)==10);
 	assert (getY(p6)==5);
 	assert (distance(p2,p6)==distance(p3,p6));
 	deletePoint(p1);
  	deletePoint(p2);
  	deletePoint(p3);
  	deletePoint(p4);
  	deletePoint(p5);
  	deletePoint(p6);
  	printf("Unit test for Point. OK\n");
}



/* Point destructor */
void deletePoint(Point * p)
{
	assert(p != NULL);

	p->x = 0;
	p->y = 0;

	free(p);
}