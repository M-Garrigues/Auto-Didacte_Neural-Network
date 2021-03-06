#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


	/*  Car.c    -----   LIF7 Auto-Didacte */


#include "Car.h"
#include "math.h"
#include "assert.h"
#include <stdio.h>
#include <stdlib.h>


const float PI = 3.14159265359;

Car * newCar () 
{
	Car * nCar = malloc(sizeof(Car));
	assert(nCar != NULL);
	
	nCar->frontLeft = NULL;
	nCar->frontLeft = newPoint(0,0);
	assert(nCar->frontLeft != NULL);

	nCar->frontRight = NULL;
	nCar->frontRight = newPoint(0,0);
	assert(nCar->frontRight != NULL);


	nCar->backLeft = NULL;
	nCar->backLeft = newPoint(0,0);
	assert(nCar->backLeft != NULL);

	nCar->backRight = NULL;
	nCar->backRight = newPoint(0,0);
	assert(nCar->backRight != NULL);

	nCar->center = NULL;
	nCar->center = newPoint(0,0);
	assert(nCar->center != NULL);
	
	nCar->speed = 0;
	nCar->orientation = 0;

	nCar->net = NULL;

	nCar->tabSensors = malloc(sizeof(float)*6);
	assert(nCar->tabSensors !=NULL);

	return nCar;
}


void initCar (Car * nCar, const Genome * genome, const Point * init, float initOrientation, float lenght, float width) {
	assert(nCar != NULL);
	assert(genome != NULL);
	assert(init != NULL);

	setX(nCar->center, getX(init));
	setY(nCar->center, getY(init));

	setX(nCar->frontRight, getX(init) + lenght/2);
	setY(nCar->frontRight, getY(init) + width/2);

	setX(nCar->backRight, getX(init) - lenght/2);
	setY(nCar->backRight, getY(init) + width/2);
	
	setX(nCar->backLeft, getX(init) - lenght/2);
	setY(nCar->backLeft, getY(init) - width/2);
	
	setX(nCar->frontLeft, getX(init) + lenght/2);
	setY(nCar->frontLeft, getY(init) - width/2);

	nCar->net = convertToNetwork(genome);

	changeOrientation(nCar, initOrientation);

}

void printCar (const Car * car) {

	assert(car != NULL);
	printf("\n\n\n\nPositions :\n");
	printf("frontLeft : %f    %f\n",(getX(car->frontLeft)) , getY(car->frontLeft));
	printf("frontRight : %f    %f\n",(getX(car->frontRight)) , getY(car->frontRight));
	printf("backLeft : %f    %f\n",(getX(car->backLeft)) , getY(car->backLeft));
	printf("backRight : %f    %f\n",(getX(car->backRight)) , getY(car->backRight));
	printf("center : %f    %f\n",(getX(car->center)) , getY(car->center));
	printf("Vitesse : %f\n",car->speed);
	printf("Orientation : %f\n\n\n\n",car->orientation);
}

void deleteCar (Car * car) {
	assert(car != NULL);

	deletePoint(car->frontLeft);
	deletePoint(car->frontRight);
	deletePoint(car->backRight);
	deletePoint(car->backLeft);
	deletePoint(car->center);
	free(car->tabSensors);
	deleteNetwork(car->net);
	free(car);
}



void changeOrientation (Car * car , float angle) {

	assert(car != NULL);
	rotation (car->frontLeft , car->center , angle);
	rotation (car->frontRight , car->center , angle);
	rotation (car->backLeft , car->center , angle);
	rotation (car->backRight , car->center , angle);

	car->orientation += angle;
	while (car->orientation > 2*PI){
		car->orientation-=2*PI;
	}	
}


void turnLeft (Car * car) {
	assert(car != NULL);
	changeOrientation(car, -PI/128);

}

void turnRight (Car * car) {
	assert(car != NULL);	
	changeOrientation(car, PI/128);
}


void accelerate (Car * car){
	if (car->speed < 1)
		car->speed += 0.25;
	else if (car->speed < 2.5)
		car->speed += 0.5;
	else if (car->speed < 5)
		car->speed += 0.2;
	
	if(car->speed > 5)
		car->speed = 5;
}

void decelerate (Car * car){
	if(car->speed > 0.25)
		car->speed -= 0.2;
	if(car->speed > 0.1)
		car->speed -= 0.1;
}


void moveStraight (Car * car, float timeM) {
	
	float distance;
	float diffAbcisse;
	float diffOrdonnee ;

	assert(car != NULL);
	distance = (car->speed)*timeM;

	diffAbcisse = cos (car->orientation) * distance;
	diffOrdonnee = sin (car->orientation) * distance;

	setX(car->center, getX(car->center) + diffAbcisse);
	setY(car->center, getY(car->center) + diffOrdonnee);

	setX(car->frontLeft, getX(car->frontLeft) + diffAbcisse);
	setY(car->frontLeft, getY(car->frontLeft) + diffOrdonnee);

	setX(car->frontRight, getX(car->frontRight) + diffAbcisse);
	setY(car->frontRight, getY(car->frontRight) + diffOrdonnee);

	setX(car->backRight, getX(car->backRight) + diffAbcisse);
	setY(car->backRight, getY(car->backRight) + diffOrdonnee);
	
	setX(car->backLeft, getX(car->backLeft) + diffAbcisse);
	setY(car->backLeft, getY(car->backLeft) + diffOrdonnee);

}

Point * getFrontLeft(const Car * car)
{
	assert(car != NULL);
	return(car->frontLeft);
}
void setFrontLeft(Car * car, Point * newPoint)
{
	assert(car != NULL);
	car->frontLeft = newPoint;
}

Point  * getFrontRight(const Car * car)
{
	assert(car != NULL);
	return(car->frontRight);
}
void setFrontRight(Car * car, Point * newPoint)
{
	assert(car != NULL);
	car->frontRight = newPoint;
}

Point  * getCenter(const Car * car)
{
	assert(car != NULL);
	return(car->center);
}
void setCenter(Car * car, Point * newPoint)
{
	assert(car != NULL);
	car->center = newPoint;
}

Point * getBackLeft(const Car * car)
{
	assert(car != NULL);
	return(car->backLeft);
}
void setBackLeft(Car * car, Point * newPoint)
{
	assert(car != NULL);
	car->backLeft = newPoint;
}

Point * getBackRight(const Car * car)
{
	assert(car != NULL);
	return(car->backRight);
}
void setBackRight(Car * car, Point * newPoint)
{
	assert(car != NULL);
	car->backRight = newPoint;
}

float getSpeed(const Car * car)
{
	assert(car != NULL);
	return(car->speed);
}
void setSpeed(Car * car, float newSpeed)
{
	assert(car != NULL);
	car->speed = newSpeed;
}

float getOrientation(const Car * car)
{
	assert(car != NULL);
	return(car->orientation);
}
void setOrientation(Car * car, float newOrientation)
{
	assert(car != NULL);
	car->orientation = newOrientation;
}

Network * getCarNetwork(const Car * car)
{
	assert(car != NULL);
	return car->net;
}
void setCarNetwork(Car * car, Network * newNetwork)
{
	assert(car != NULL);
	car->net = newNetwork;
}

float * getSensors(const Car * car)
{
	assert(car != NULL);
	return car->tabSensors;
}
void setSensors(Car * car,float * newTabSensors)
{
	assert(car != NULL);
	car->tabSensors = newTabSensors;
}


void unitTestCar ()
{
	Car *c1;
	Genome *g1;
	Point *p1, *p2, *p3;
	int tab[3] = {6, 5, 4};
	p1 = newPoint (0,0);
	g1 = newGenomeRandom(tab);
	c1 = newCar();
	initCar (c1, g1, p1, 0, 100, 50);
	p2 = getFrontLeft(c1);
	assert(getX(p2)==50);
	assert(getY(p2)==-25);
	p3 = getCenter(c1);
	assert(getX(p3)==0);
	assert(getY(p3)==0);
	turnLeft(c1);
	assert(getOrientation(c1)<0);
	turnRight(c1);
	assert(getOrientation(c1)==0);
	deleteCar (c1);
	printf("Unit test for Car.* OK\n");
}