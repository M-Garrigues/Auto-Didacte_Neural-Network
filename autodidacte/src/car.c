#include "car.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

const float PI = 3.14159265359;

Car * newCar () {
	Car * nCar = malloc(sizeof(Car));
	
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
	free(car);
}

Point rotation (Point pointInit, Point centre ,float angle){
	Point pointFinal;

	pointFinal.x = (pointInit.x-centre.x)*cos(angle) - (pointInit.y-centre.y)*sin(angle) + centre.x;
	pointFinal.y = (pointInit.y-centre.y)*cos(angle) + (pointInit.x-centre.x)*sin(angle) + centre.y;

	return pointFinal;	
}

void changeOrientation (Car * car , float angle) {
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
	changeOrientation(car, PI/16);
	printCar(car);

}

void turnRight (Car * car) {	
	changeOrientation(car, -PI/16);
	printCar(car);
}

void moveStraight (Car * car, float timeM) {
	float distance;
	float diffAbcisse;
	float diffOrdonnee ;

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