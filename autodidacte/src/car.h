#ifndef H_CAR
#define H_CAR
#include <stdio.h>
/* Car.h ----- LIF7 Auto-Didacte */



typedef struct
{
	float x;
	float y;
}Point;

/* Structure Car */

typedef struct
{
	Point frontLeft;
	Point frontRight;
	Point center;
	Point backLeft;
	Point backRight;
	float speed;
	float orientation;
}Car;

Car * newCar ();
void initCar (Car * car, Point frontLeft);
void printCar (Car * car);
void deleteCar (Car * car);
void refreshOrientation (Car * car);
void turnLeft (Car * car);
void turnRight (Car * car);
void moveStraight (Car * car, float time);
void accelerate (Car * car);
void decellerate (Car * car);
Point rotation (Point pointInit, Point centre ,float angle);
/*void changeOrientation (Car * car , float angle);*/

#endif