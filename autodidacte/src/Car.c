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

Car * newCar () {
	Car * nCar = malloc(sizeof(Car));
	assert(nCar != NULL);
	
	nCar->frontLeft = NULL;
	nCar->frontLeft = malloc(sizeof(Point));
	assert(nCar->frontLeft != NULL);
	nCar->frontLeft = newPoint(0,0);
	

	nCar->frontRight = NULL;
	nCar->frontRight = malloc(sizeof(Point));
	assert(nCar->frontRight != NULL);
	nCar->frontRight = newPoint(0,0);


	nCar->backLeft = NULL;
	nCar->backLeft = malloc(sizeof(Point));
	assert(nCar->backLeft != NULL);
	nCar->backLeft = newPoint(0,0);


	nCar->backRight = NULL;
	nCar->backRight = malloc(sizeof(Point));
	assert(nCar->backRight != NULL);
	nCar->backRight = newPoint(0,0);

	nCar->center = NULL;
	nCar->center = malloc(sizeof(Point));
	assert(nCar->center != NULL);
	nCar->center = newPoint(0,0);
	
	nCar->speed = 1;
	nCar->orientation = 0;

	nCar->net = NULL;
	nCar->net = malloc(sizeof(Network));
	assert(nCar->net != NULL);

	return nCar;
}


void initCar (Car * nCar, Genome * genome, Point * init, float initOrientation) {
	assert(nCar != NULL);
	assert(genome != NULL);
	assert(init != NULL);

	setX(nCar->frontLeft, getX(init));
	setY(nCar->frontLeft, getY(init));
	
	setX(nCar->frontRight, getX(init) - 10);
	setY(nCar->frontRight, getY(init));
	
	setX(nCar->backRight, getX(init) - 10);
	setY(nCar->backRight, getY(init) - 10);
	
	setX(nCar->backLeft, getX(init));
	setY(nCar->backLeft, getY(init) - 10);
	
	setX(nCar->center, getX(init) - 5);
	setY(nCar->center, getX(init) - 5);
	
	changeOrientation(nCar, initOrientation);

	nCar->net = convertToNetwork(genome);
}

void printCar (Car * car) {

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

	deleteNetwork(car->net);
	free(car);
}



void changeOrientation (Car * car , float angle) {

	assert(car != NULL);
	car->frontLeft = rotation (car->frontLeft , car->center , angle);
	car->frontRight = rotation (car->frontRight , car->center , angle);
	car->backLeft = rotation (car->backLeft , car->center , angle);
	car->backRight = rotation (car->backRight , car->center , angle);

	car->orientation += angle;
	while (car->orientation > 2*PI){
		car->orientation-=2*PI;
	}	
}


void turnLeft (Car * car) {
	assert(car != NULL);
	changeOrientation(car, PI/16);
	printCar(car);

}

void turnRight (Car * car) {
	assert(car != NULL);	
	changeOrientation(car, -PI/16);
	printCar(car);
}


void accelerate (Car * car){
	car->speed += 1;
}

void decelerate (Car * car){
	car->speed -= 1;
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

	printCar(car);
}

Point * getFrontLeft(Car * car)
{
	assert(car != NULL);
	return(car->frontLeft);
}
void setFrontLeft(Car * car, Point * newPoint)
{
	assert(car != NULL);
	car->frontLeft = newPoint;
}

Point  * getFrontRight(Car * car)
{
	assert(car != NULL);
	return(car->frontRight);
}
void setFrontRight(Car * car, Point * newPoint)
{
	assert(car != NULL);
	car->frontRight = newPoint;
}

Point  * getCenter(Car * car)
{
	assert(car != NULL);
	return(car->center);
}
void setCenter(Car * car, Point * newPoint)
{
	assert(car != NULL);
	car->center = newPoint;
}

Point * getBackLeft(Car * car)
{
	assert(car != NULL);
	return(car->backLeft);
}
void setBackLeft(Car * car, Point * newPoint)
{
	assert(car != NULL);
	car->backLeft = newPoint;
}

Point * getBackRight(Car * car)
{
	assert(car != NULL);
	return(car->backRight);
}
void setBackRight(Car * car, Point * newPoint)
{
	assert(car != NULL);
	car->backRight = newPoint;
}

float getSpeed(Car * car)
{
	assert(car != NULL);
	return(car->speed);
}
void setSpeed(Car * car, float newSpeed)
{
	assert(car != NULL);
	car->speed = newSpeed;
}

float getOrientation(Car * car)
{
	assert(car != NULL);
	return(car->orientation);
}
void setOrientation(Car * car, float newOrientation)
{
	assert(car != NULL);
	car->orientation = newOrientation;
}

Network * getCarNetwork(Car * car)
{
	assert(car != NULL);
	return car->net;
}
void setCarNetwork(Car * car, Network * newNetwork)
{
	assert(car != NULL);
	car->net = newNetwork;
}

float * getSensors(Car * car)
{
	assert(car != NULL);
	return car->tabSensors;
}
void setSensors(Car * car, float * newTabSensors)
{
	assert(car != NULL);
	car->tabSensors = newTabSensors;
}