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
	
	(nCar->frontLeft).x = 0;
	(nCar->frontLeft).y = 0;
	
	(nCar->frontRight).x = 0;
	(nCar->frontRight).y = 0;
	
	(nCar->backRight).x = 0;
	(nCar->backRight).y = 0;
	
	(nCar->backLeft).x = 0;
	(nCar->backLeft).y = 0;		
	
	(nCar->center).x = 0;
	(nCar->center).y = 0;
	
	nCar->speed = 1;
	nCar->orientation = 0;

	return nCar;
}


void initCar (Car * nCar, Point init) {
	assert(nCar != NULL);

	(nCar->frontLeft).x = init.x;
	(nCar->frontLeft).y = init.y;
	
	(nCar->frontRight).x = init.x - 10;
	(nCar->frontRight).y = init.y;
	
	(nCar->backRight).x = init.x - 10;
	(nCar->backRight).y = init.y - 10;
	
	(nCar->backLeft).x = init.x;
	(nCar->backLeft).y = init.y - 10;		
	
	(nCar->center).x = init.x - 5;
	(nCar->center).y = init.y -5;
}

void printCar (Car * car) {

	assert(car != NULL);
	printf("\n\n\n\nPositions :\n");
	printf("frontLeft : %f    %f\n",(car->frontLeft).x , (car->frontLeft).y);
	printf("frontRight : %f    %f\n",(car->frontRight).x , (car->frontRight).y);
	printf("backLeft : %f    %f\n",(car->backLeft).x , (car->backLeft).y);
	printf("backRight : %f    %f\n",(car->backRight).x , (car->backRight).y);
	printf("center : %f    %f\n",(car->center).x , (car->center).y);
	printf("Vitesse : %f\n",car->speed);
	printf("Orientation : %f\n\n\n\n",car->orientation);
}

void deleteCar (Car * car) {
	assert(car != NULL);
	free(car);
}

Point rotation (Point pointInit, Point centre ,float angle){
	Point pointFinal;

	pointFinal.x = (pointInit.x-centre.x)*cos(angle) - (pointInit.y-centre.y)*sin(angle) + centre.x;
	pointFinal.y = (pointInit.y-centre.y)*cos(angle) + (pointInit.x-centre.x)*sin(angle) + centre.y;

	return pointFinal;	
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

	(car->center.x)+=diffAbcisse;
	(car->center.y)+=diffOrdonnee;

	(car->frontLeft.x)+=diffAbcisse;
	(car->frontLeft.y)+=diffOrdonnee;

	(car->frontRight.x)+=diffAbcisse;
	(car->frontRight.y)+=diffOrdonnee;

	(car->backRight.x)+=diffAbcisse;
	(car->backRight.y)+=diffOrdonnee;
	
	(car->backLeft.x)+=diffAbcisse;
	(car->backLeft.y)+=diffOrdonnee;

	printCar(car);
}

Point * getFrontLeft(Car * car)
{
	assert(car != NULL);
	return(&(car->frontLeft));
}
void setFrontLeft(Car * car, Point * newPoint)
{
	assert(car != NULL);
	car->frontLeft = *newPoint;
}

Point  * getFrontRight(Car * car)
{
	assert(car != NULL);
	return(&(car->frontRight));
}
void setFrontRight(Car * car, Point * newPoint)
{
	assert(car != NULL);
	car->frontRight = *newPoint;
}

Point  * getCenter(Car * car)
{
	assert(car != NULL);
	return(&(car->center));
}
void setCenter(Car * car, Point * newPoint)
{
	assert(car != NULL);
	car->center = *newPoint;
}

Point * getBackLeft(Car * car)
{
	assert(car != NULL);
	return(&(car->backLeft));
}
void setBackLeft(Car * car, Point * newPoint)
{
	assert(car != NULL);
	car->backLeft = *newPoint;
}

Point * getBackRight(Car * car)
{
	assert(car != NULL);
	return(&(car->backRight));
}
void setBackRight(Car * car, Point * newPoint)
{
	assert(car != NULL);
	car->backRight = *newPoint;
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