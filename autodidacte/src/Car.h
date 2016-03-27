#ifndef H_FB_CAR
#define H_FB_CAR


/* Car.h   ----- LIF7 Auto-Didacte */


#include <stdio.h>
#include "Point.h"


/* Structure Car */

typedef struct
{
	Point * frontLeft;
	Point * frontRight;
	Point * center;
	Point * backLeft;
	Point * backRight;
	float speed;
	float orientation;
}Car;


/* Car constructors */
Car * newCar ();
void initCar (Car * car, Point * frontLeft, float initOrientation);


/* Car get/set */
Point * getFrontLeft(Car * car);
void setFrontLeft(Car * car, Point * newPoint);

Point  * getFrontRight(Car * car);
void setFrontRight(Car * car, Point * newPoint);

Point  * getCenter(Car * car);
void setCenter(Car * car, Point * newPoint);

Point * getBackLeft(Car * car);
void setBackLeft(Car * car, Point * newPoint);

Point * getBackRight(Car * car);
void setBackRight(Car * car, Point * newPoint);

float getSpeed(Car * car);
void setSpeed(Car * car, float newSpeed);

float getOrientation(Car * car);
void setOrientation(Car * car, float newOrientation);

/* Car functions */
void printCar (Car * car);
void changeOrientation (Car * car , float angle);
void turnLeft (Car * car);
void turnRight (Car * car);
void moveStraight (Car * car, float time);
void accelerate (Car * car);
void decelerate (Car * car);


/* Car destructor */
void deleteCar(Car * Car);


/*void changeOrientation (Car * car , float angle);*/

#endif