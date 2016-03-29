#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


	/*  Simulation.C   -----   LIF7 Auto-Didacte */


#include "Simulation.h"
#include "stdlib.h"
#include "assert.h"
#include "stdio.h"
#include "math.h"





Simulation * newSimulation(float speed, Genome * genome, Track * track, Point * initPosition, float initOrientation)
{
	assert(genome != NULL);
	assert(track != NULL);

	Simulation * sim = NULL;
	sim = malloc(sizeof(Simulation));
	assert(sim != NULL);
	printf("orientation %f\n",initOrientation);
	sim->car = NULL;
	sim->car = newCar();
	assert(sim->car != NULL);
	initCar(sim->car, genome, initPosition, initOrientation, 50 , 25);/* Le point initial ne pourrait pas etre dans track ? 
	a priori ca ne changera pas sur un circuit donné ?  meme chose pour init orientation Valentin*/
	sim->speed = speed;


	sim->track = track;
	sim->initPosition = initPosition;
	sim->initOrientation = initOrientation;

	sim->fitness = 0;

	sim->sector = 0;

	return sim;
}

/* Returns -1 if currently active, the fitness of the genome if it's finished */
int tickSimulation(Simulation * sim)
{
	assert(sim != NULL);
	assert(sim->fitness >= 0);

	float * tabSensors;
	int action;
	Network * net;
	Layer * out;

	sim->nbTicks++;
	updateSensors(sim, sim->sector);	
	tabSensors = getSensors(sim->car);
	net = getCarNetwork(sim->car);
	out = getLayer(net, OUTPUT);
	feedForward(net, tabSensors);

	action = selectHigherValue(out);
	if(getValue(getNeuron(out, action)) < 1) /*We check if the highest neuron is activated*/
		action = NONE;/*If not, no action will be done this tick*/


	switch (action) {

	case NONE :
		moveStraight(sim->car, 1); /* Try different values for moveStraight */
	 break;

	case RIGHT :
	 	turnRight(sim->car);
	 	moveStraight(sim->car, 0.75);
	 break;

	case LEFT :
		turnLeft(sim->car);
		moveStraight(sim->car, 0.75);
	 break;
}

	if(detectCheckPointCrossed(sim)) /*The car entered a new sector, fitness improves*/
	{
		printf("ici");
		sim->sector++;

		if (!(detectCollision(sim, sim->sector))&&!(detectCollision(sim, sim->sector-1)))
		{
			sim->fitness++;
			return -1;
		}
		else
			return sim->fitness;
	}
	else
	{
		if (!(detectCollision(sim, sim->sector)))
		{
			sim->fitness++;
			return -1;
		}
		else
			return sim->fitness;
	}

}


void updateSensors(Simulation * sim, int sector){
	assert (sim != NULL);
	float c1,c2,c3,c4,c5;
	float * newTabSensors;
	Car * carUpdate;
	Point * pLeft , * pRight , * pCenter;
	Point * pFLeft , * pFRight , * pFCenter ;
	Point * pInter , *pInter2 , *pInter3 , *pInter4;
	Point * TrInUp,* TrInDown, * TrOutUp, * TrOutDown, *TrInNext, *TrOutNext;

	newTabSensors = malloc ( 5*sizeof(float));

	carUpdate = getCar(sim);
	assert(getSensors(carUpdate)!=NULL);
	free (getSensors(carUpdate));
	pFLeft = getFrontLeft(carUpdate); /*Capteur 1 */
	pCenter = getCenter (carUpdate);
	pFRight = getFrontRight(carUpdate); /*Capteur 2*/
	pFCenter = middle(pFRight,pFLeft); /*Capteur 3 */
	pRight = middle(pFRight,getBackRight(carUpdate)); /*Capteur 4 */
	pLeft = middle(pFLeft,getBackLeft(carUpdate)); /*Capteur 5 */

	TrInUp = getTrackIn(sim->track, sim->sector+1);
	TrInDown = getTrackIn(sim->track, sim->sector);
	TrOutUp = getTrackOut(sim->track, sim->sector+1);
	TrOutDown = getTrackOut(sim->track, sim->sector);
	TrInNext = getTrackIn(sim->track, sim->sector+2);
	TrOutNext = getTrackOut(sim->track, sim->sector+2);

	pInter = intersectPoint (pFLeft , pCenter, TrInUp , TrInDown);
	pInter2 = intersectPoint (pFLeft , pCenter, TrOutUp , TrOutDown);
	pInter3 = intersectPoint (pFLeft , pCenter, TrOutUp , TrOutNext);
	pInter4 = intersectPoint (pFLeft , pCenter, TrInUp , TrInNext);

	c1 = distanceCheck(minimum(distance(pInter,pFLeft),distance(pInter2,pFLeft),distance(pInter3,pFLeft),distance(pInter4,pFLeft)));

	pInter = intersectPoint (pFLeft , pCenter, TrInUp , TrInDown);
	pInter2 = intersectPoint (pFLeft , pCenter, TrOutUp , TrOutDown);
	pInter3 = intersectPoint (pFLeft , pCenter, TrOutUp , TrOutNext);
	pInter4 = intersectPoint (pFLeft , pCenter, TrInUp , TrInNext);

	c2 = distanceCheck(minimum(distance(pInter,pFRight),distance(pInter2,pFRight),distance(pInter3,pFRight),distance(pInter4,pFRight)));

	pInter = intersectPoint (pFCenter , pCenter, TrInUp , TrInDown);
	pInter2 = intersectPoint (pFCenter , pCenter, TrOutUp , TrOutDown);
	pInter3 = intersectPoint (pFCenter , pCenter, TrOutUp , TrOutNext);
	pInter4 = intersectPoint (pFCenter , pCenter, TrInUp , TrInNext);

	c3 = distanceCheck(minimum(distance(pInter,pFCenter),distance(pInter2,pFCenter),distance(pInter3,pFCenter),distance(pInter4,pFCenter)));

	pInter = intersectPoint (pRight , pCenter, TrInUp , TrInDown);
	pInter2 = intersectPoint (pRight , pCenter, TrOutUp , TrOutDown);
	pInter3 = intersectPoint (pRight , pCenter, TrOutUp , TrOutNext);
	pInter4 = intersectPoint (pRight , pCenter, TrInUp , TrInNext);

	c4 = distanceCheck(minimum(distance(pInter,pRight),distance(pInter2,pRight),distance(pInter3,pRight),distance(pInter4,pRight)));

	pInter = intersectPoint (pLeft , pCenter, TrInUp , TrInDown);
	pInter2 = intersectPoint (pLeft , pCenter, TrOutUp , TrOutDown);
	pInter3 = intersectPoint (pLeft , pCenter, TrOutUp , TrOutNext);
	pInter4 = intersectPoint (pLeft , pCenter, TrInUp , TrInNext);

	c5 = distanceCheck(minimum(distance(pInter,pLeft),distance(pInter2,pLeft),distance(pInter3,pLeft),distance(pInter4,pLeft)));

	newTabSensors[0] = c1;
	newTabSensors[1] = c2;
	newTabSensors[2] = c3;
	newTabSensors[3] = c4;
	newTabSensors[4] = c5;
	/*printf ("%f\n",c1);
	printf ("%f\n",c2);
	printf ("%f\n",c3);
	printf ("%f\n",c4);
	printf ("%f\n\n",c5);*/
	setSensors(carUpdate , newTabSensors);
	free (pInter);
}

int detectCheckPointCrossed(Simulation * sim)
{
	assert(sim != NULL);

	Point * CPin,* CPout;
	Point * carFL,  * carFR, * carBR, * carBL;

	CPin = getTrackIn(sim->track, sim->sector+1);
	CPout = getTrackOut(sim->track, sim->sector+1);

	carFL = getFrontLeft(sim->car);
	carFR = getFrontRight(sim->car);
	carBR = getBackRight(sim->car);
	carBL = getBackLeft(sim->car);
	/*printf("sector : %d\n CarBL : %f ,%f\n CarFL : %f,%f\n Check :%f,%f\n%f,%f\n\n",sim->sector,carBL->x,carBL->y,carFL->x,carFL->y,CPin->x,CPin->y,CPout->x,CPout->y);
	printf("\n Interesct : %d \n",intersect(CPin,CPout,carFL,carBL));*/
	if(intersect(CPin, CPout, carFR, carBR)||intersect(CPin, CPout,carFL,carBL))
		return 1;
	else
		return 0;
}

int detectCollision(Simulation * sim, int sector)/* Here we consider the Inside of the track is always on the car's right*/
{
	assert(sim != NULL);

	Point * TrInUp,* TrInDown, * TrOutUp, * TrOutDown;
	Point * carFL,  * carFR, * carBL, * carBR;

	TrInUp = getTrackIn(sim->track, sim->sector+1);
	TrInDown = getTrackIn(sim->track, sim->sector);
	TrOutUp = getTrackOut(sim->track, sim->sector+1);
	TrOutDown = getTrackOut(sim->track, sim->sector);

	carFL = getFrontLeft(sim->car);
	carFR = getFrontRight(sim->car);
	carBL = getBackLeft(sim->car);
	carBR = getBackLeft(sim->car);

	if(intersect(TrInUp, TrInDown, carBR, carFR) || intersect(TrOutUp, TrOutDown, carFL, carBL))
		return 1;
	else
		return 0;
}









float getSimSpeed(Simulation * sim)
{
	assert(sim != NULL);
	return sim->speed;
}
void setSimSpeed(Simulation * sim, float newSpeed)
{
	assert(sim != NULL);
	sim->speed = newSpeed;
}

Car * getCar(Simulation * sim)
{
	assert(sim != NULL);
	return sim->car;
}
void setCar(Simulation * sim, Car * car)
{
	assert(sim != NULL);
	sim->car = car;
}

Point * getInitPosition(Simulation * sim)
{
	assert(sim != NULL);
	return sim->initPosition;
}
void setInitPosition(Simulation * sim, Point * newInitPos)
{
	assert(sim != NULL);
	sim->initPosition = newInitPos;
}

float getInitOrientation(Simulation * sim)
{
	assert(sim != NULL);
	return sim->initOrientation;
}
void setInitOrientation(Simulation * sim, float newOrientation)
{
	assert(sim != NULL);
	sim->initOrientation = newOrientation;
}


int getNbTicks(Simulation * sim)
{
	assert(sim != NULL);
	return sim->nbTicks;
}
void setNbTicks(Simulation * sim, int newNb)
{
	assert(sim != NULL);
	sim->nbTicks = newNb;
}

Track * getTrack(Simulation * sim)
{
	assert(sim != NULL);
	return sim->track;
}
void setTrack(Simulation * sim, Track * track)
{
	assert(sim != NULL);
	sim->track = track;
}

int getSimFitness(Simulation * sim)
{
	assert(sim != NULL);
	return sim->fitness;
}
void setimFitness(Simulation * sim, int newFitness)
{
	assert(sim != NULL);
	sim->fitness = newFitness;
}

int getSector(Simulation * sim)
{
	assert(sim != NULL);
	return sim->sector;
}
void setSector(Simulation * sim, int newSector)
{
	assert(sim != NULL);
	sim->sector = newSector;
}


void endSimulation(Simulation * sim)
{
	assert(sim != NULL);

	sim->speed = 0;
	deleteCar(sim->car);
	sim->track = NULL; // A CHANGER PEUT ETRE, EN FONCTION DE TRACK.
	sim->initPosition = NULL; // DE MEME
	sim->initOrientation = 0;

	free(sim);
}
