#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


	/*  Simulation.C   -----   LIF7 Auto-Didacte */


#include "Simulation.h"
#include "stdlib.h"
#include "assert.h"
#include "stdio.h"
#include "math.h"

void printLayer(Layer * layer)
{
	int i,j;

	assert(layer != NULL);

	if(layer->type == INPUT || layer->type == HIDDEN)
	{
		if (layer->type == INPUT)
			printf("INPUT LAYER:\n\n");

		if (layer->type == HIDDEN)
			printf("HIDDEN LAYER:\n\n");

		for (i = 0; i < layer->nbNeurons; ++i)
		{
			printf("Neuron %d: %f  =====  ",i, layer->tabNeurons[i]->value);

			for (j = 0; j < layer->tabNeurons[0]->nbWeights; ++j)
			{
				printf("W%d: %f | ", j, layer->tabNeurons[i]->tabWeights[j]);
			}
			printf("\n");
			
		}

		printf("\n\n ********************************\n\n");
	}

	else
	{
		printf("OUTPUT LAYER:\n\n");

		for (i = 0; i < layer->nbNeurons; ++i)
		{
			printf("Neuron %d: %f     ",i, layer->tabNeurons[i]->value);
		}
		printf("\n\n ********************************\n\n");
	}
}


void printNetwork(Network * net)
{
	printLayer(net->tabLayers[INPUT]);
	printLayer(net->tabLayers[HIDDEN]);
	printLayer(net->tabLayers[OUTPUT]);
}




Simulation * newSimulation(float speed, Genome * genome, Track * track, Point * initPosition, float initOrientation)
{
	assert(genome != NULL);
	assert(track != NULL);

	Simulation * sim = NULL;
	sim = malloc(sizeof(Simulation));
	assert(sim != NULL);
	sim->car = NULL;
	sim->car = newCar();
	assert(sim->car != NULL);
	initCar(sim->car, genome, initPosition, initOrientation, 50 , 25);
	sim->speed = speed;


	sim->track = track;
	sim->initPosition = initPosition;
	sim->initOrientation = initOrientation;

	sim->fitness = 1;

	sim->sector = 0;

	return sim;
}

/* Returns -1 if currently active, the fitness of the genome if it's finished */
int tickSimulation(Simulation * sim)
{
	assert(sim != NULL);
	assert(sim->fitness >= 0);

	float * tabSensors;
	int actionTurn, actionSpeed;
	Network * net;
	Layer * out;

	sim->nbTicks++;
	updateSensors(sim);	

	
	tabSensors = getSensors(sim->car);
	net = getCarNetwork(sim->car);
	out = getLayer(net, OUTPUT);
	feedForward(net, tabSensors);
	/*printLayer(net->tabLayers[OUTPUT]);*/

printLayer(net->tabLayers[INPUT]);
printLayer(out);

	actionTurn = selectHigherValueAct(out);
	actionSpeed = selectHigherValueSpeed(out);

	if(getValue(getNeuron(out, actionTurn)) < 0.3) /*We check if the highest neuron is activated*/
		actionTurn = NONE;//If not, no action will be done this tick
		         

	if(getValue(getNeuron(out, actionSpeed)) < 0.3) /*We check if the highest neuron is activated*/
		actionSpeed = NONE;//If not, no action will be done this tick	                


printf("%d\n", sim->nbTicks);

switch (actionSpeed) {

	case NONE :
	 break;

	case ACCELERATION :
	 	accelerate(sim->car);
	 	break;

	case DECELERATION :
		decelerate(sim->car);
	 break;
}


switch (actionTurn) {

	case NONE :/*printf("NONE\n");*/ /* Try different values for moveStraight */
	 break;

	case RIGHT :
		if(getSpeed(sim->car) > 0.5)
	 		turnRight(sim->car);
	 break;

	case LEFT :
	if(getSpeed(sim->car) > 0.5)
		turnLeft(sim->car);
	 break;
}

	moveStraight(sim->car, 1); //the car does a step forward

	if(detectCheckPointCrossed(sim)) /*The car entered a new sector, fitness improves*/
	{
		if(sim->sector < getNbPoints(sim->track)-1)
		{
			sim->sector++;
		}
		else
		{
			sim->sector = 0;
			if (!(detectCollision(sim, sim->sector))&&!(detectCollision(sim, getNbPoints(sim->track)-1)))
			{
				sim->fitness++;
				sim->nbTicks = 0;
				return -1;
			}
			else
				return sim->fitness;
		}
			printf("%d\n",sim->sector);

		if (!(detectCollision(sim, sim->sector))&&!(detectCollision(sim, sim->sector-1)))
		{
			printf("tetstsettestsetsetsetsettsetestest\n");
			sim->fitness++;
			sim->nbTicks = 0;
			return -1;
		}
		else
			return sim->fitness;
	}
	else
	{
		if (!(detectCollision(sim, sim->sector)))
		{
			if(sim->nbTicks > 20 && getSpeed(sim->car) == 0)
				return sim->fitness;
			else if(sim->nbTicks > 50 && getSpeed(sim->car) < 0.3)
				return sim->fitness;
			else
				return -1;
		}	
		else
			return sim->fitness;		
	}

}


void updateSensors(Simulation * sim)
{
	assert(sim != NULL);
	float const PI = 3.14159265359;
	float * tabSensors = malloc(6*sizeof(float));
	float tailleSensor = 12000;
	float a,b,c,d,e,f;
	Point * tOut1;
	Point * tIn1;
	Point * tIn2 = getTrackIn(sim->track, sim->sector);
	Point * tOut2 = getTrackOut(sim->track, sim->sector);
	Point * tIn3;
	Point * tOut3;

	Point * tIn4;
	Point * tOut4;

	tabSensors[5] = (getSpeed(sim->car))/5;


	if(sim->sector == 0)
	{
		tIn1 = getTrackIn(sim->track, sim->track->nbPoints-1);
		tOut1 = getTrackOut(sim->track, sim->track->nbPoints-1);
		tOut3 = getTrackOut(sim->track, sim->sector+1);
		tIn3 = getTrackIn(sim->track, sim->sector+1);
		tOut4 = getTrackOut(sim->track, sim->sector+2);
		tIn4 = getTrackIn(sim->track, sim->sector+2);
	}
	else if(sim->sector == getNbPoints(sim->track)-1)
	{
		tIn1 = getTrackIn(sim->track, sim->sector-1);
		tOut1 = getTrackOut(sim->track, sim->sector-1);	
		tIn3 = getTrackIn(sim->track, 0);
		tOut3 = getTrackOut(sim->track, 0);
		tIn4 = getTrackIn(sim->track, 1);
		tOut4 = getTrackOut(sim->track, 1);
	}
	else if(sim->sector == getNbPoints(sim->track)-2)
	{
		tIn1 = getTrackIn(sim->track, sim->sector-1);
		tOut1 = getTrackOut(sim->track, sim->sector-1);	
		tIn3 = getTrackIn(sim->track, getNbPoints(sim->track)-1);
		tOut3 = getTrackOut(sim->track, getNbPoints(sim->track)-1);
		tIn4 = getTrackIn(sim->track, 0);
		tOut4 = getTrackOut(sim->track, 0);	
	}
	else
	{
		tIn1 = getTrackIn(sim->track, sim->sector-1);
		tOut1 = getTrackOut(sim->track, sim->sector-1);
		tOut3 = getTrackOut(sim->track, sim->sector+1);
		tIn3 = getTrackIn(sim->track, sim->sector+1);
		tOut4 = getTrackOut(sim->track, sim->sector+2);
		tIn4 = getTrackIn(sim->track, sim->sector+2);
	}

	Point * beginSensor1 = middle(getBackLeft(sim->car),getFrontLeft(sim->car));
	Point * beginSensor2 = getFrontLeft(sim->car);
	Point * beginSensor3 = middle(getFrontLeft(sim->car),getFrontRight(sim->car));
	Point * beginSensor4 = getFrontRight(sim->car);
	Point * beginSensor5 = middle(getBackRight(sim->car), getFrontRight(sim->car));
	Point * endSensor1 = newPoint(getX(beginSensor1)+cos(-(PI/2) + getOrientation(getCar(sim)))*tailleSensor,getY(beginSensor1)+sin((-PI/2)+getOrientation(getCar(sim)))*tailleSensor);; /* flanc gauche */
	Point * endSensor2 = newPoint(getX(beginSensor2)+cos((-PI/4) + getOrientation(getCar(sim)))*tailleSensor,getY(beginSensor2)+sin((-PI/4)+getOrientation(getCar(sim)))*tailleSensor); /* coin avant gauche */
	Point * endSensor3 = newPoint(getX(beginSensor3)+cos(getOrientation(getCar(sim)))*tailleSensor*100,getY(beginSensor3)+sin(getOrientation(getCar(sim)))*tailleSensor*100); /* centre avant */
	Point * endSensor4 = newPoint(getX(beginSensor4)+cos((PI/4) + getOrientation(getCar(sim)))*tailleSensor,getY(beginSensor4)+sin((PI/4)+getOrientation(getCar(sim)))*tailleSensor); /* coin avant droit */
	Point * endSensor5 = newPoint(getX(beginSensor5)+cos((PI/2) + getOrientation(getCar(sim)))*tailleSensor,getY(beginSensor5)+sin((PI/2)+getOrientation(getCar(sim)))*tailleSensor); /* flanc droit */
	free(getSensors(sim->car));


	/*Capteur 1 flanc gauche */
		if(intersect(tIn1,tIn2,beginSensor1,endSensor1))
			a = distance(beginSensor1,intersectPoint(tIn1,tIn2,beginSensor1,endSensor1));
		else
			a = tailleSensor; /* si a = tailleSensor ==> 1 - a/tailleSensor ==  0*/

		if(intersect(tIn2,tIn3,beginSensor1,endSensor1))
			b = distance(beginSensor1,intersectPoint(tIn2,tIn3,beginSensor1,endSensor1));
		else
			b = tailleSensor;

		if(intersect(tOut1,tOut2,beginSensor1,endSensor1))
			c = distance(beginSensor1,intersectPoint(tOut1,tOut2,beginSensor1,endSensor1));
		else
			c = tailleSensor;

		if(intersect(tOut2,tOut3,beginSensor1,endSensor1))
			d = distance(beginSensor1,intersectPoint(tOut2,tOut3,beginSensor1,endSensor1));
		else
			d = tailleSensor;

		if(intersect(beginSensor1, endSensor1, tIn3, tIn4))
		{
			e = distance(beginSensor1, intersectPoint(tIn3, tIn4,beginSensor1, endSensor1));
		}
		else
			e = tailleSensor;

		if(intersect(beginSensor1, endSensor1, tOut3, tOut4))
		{
			f = distance(beginSensor1, intersectPoint(tOut3, tOut4,beginSensor1, endSensor1));
		}
		else
			f = tailleSensor;

		d = minimum(tailleSensor,d,e,f);
		tabSensors[0] = 1 - minimum(a,b,c,d)/tailleSensor;

		/*Capteur 2 coin avant gauche*/
		if(intersect(tIn1,tIn2,beginSensor2,endSensor2))
			a = distance(beginSensor2,intersectPoint(tIn1,tIn2,beginSensor2,endSensor2));
		else
			a = tailleSensor; /* si a = tailleSensor ==> 1 - a/tailleSensor ==  0*/

		if(intersect(tIn2,tIn3,beginSensor2,endSensor2))
			b = distance(beginSensor2,intersectPoint(tIn2,tIn3,beginSensor2,endSensor2));
		else
			b = tailleSensor;

		if(intersect(tOut1,tOut2,beginSensor2,endSensor2))
			c = distance(beginSensor2,intersectPoint(tOut1,tOut2,beginSensor2,endSensor2));
		else
			c = tailleSensor;

		if(intersect(tOut2,tOut3,beginSensor2,endSensor2))
			d = distance(beginSensor2,intersectPoint(tOut2,tOut3,beginSensor2,endSensor2));
		else
			d = tailleSensor;

		if(intersect(beginSensor2, endSensor2, tIn3, tIn4))
		{
			e = distance(beginSensor2, intersectPoint(tIn3, tIn4,beginSensor2, endSensor2));
		}
		else
			e = tailleSensor;

		if(intersect(beginSensor2, endSensor2, tOut3, tOut4))
		{
			f = distance(beginSensor2, intersectPoint(tOut3, tOut4,beginSensor2, endSensor2));
		}
		else
			f = tailleSensor;

		d = minimum(tailleSensor,d,e,f);
		tabSensors[1] = 1 - minimum(a,b,c,d)/tailleSensor;
		

	/*Capteur 3 milieu avant*/
		if(intersect(tIn1,tIn2,beginSensor3,endSensor3))
			a = distance(beginSensor3,intersectPoint(tIn1,tIn2,beginSensor3,endSensor3));
		else
			a = tailleSensor; /* si a = tailleSensor ==> 1 - a/tailleSensor ==  0*/

		if(intersect(tIn2,tIn3,beginSensor3,endSensor3))
			b = distance(beginSensor3,intersectPoint(tIn2,tIn3,beginSensor3,endSensor3));
		else
			b = tailleSensor;

		if(intersect(tOut1,tOut2,beginSensor3,endSensor3))
			c = distance(beginSensor3,intersectPoint(tOut1,tOut2,beginSensor3,endSensor3));
		else
			c = tailleSensor;

		if(intersect(tOut2,tOut3,beginSensor3,endSensor3))
			d = distance(beginSensor3,intersectPoint(tOut2,tOut3,beginSensor3,endSensor3));
		else
			d = tailleSensor;

				if(intersect(beginSensor3, endSensor3, tIn3, tIn4))
		{
			e = distance(beginSensor3, intersectPoint(tIn3, tIn4,beginSensor3, endSensor3));
		}
		else
			e = tailleSensor;

		if(intersect(beginSensor3, endSensor3, tOut3, tOut4))
		{
			f = distance(beginSensor1, intersectPoint(tOut3, tOut4,beginSensor3, endSensor3));
		}
		else
			f = tailleSensor;

		d = minimum(tailleSensor,d,e,f);
		tabSensors[2] =  1 - minimum(a,b,c,d)/tailleSensor;

	/*Cpateur 4 coin avant droit */
		if(intersect(tIn1,tIn2,beginSensor4,endSensor4))
			a = distance(beginSensor4,intersectPoint(tIn1,tIn2,beginSensor4,endSensor4));
		else
			a = tailleSensor; /* si a = tailleSensor ==> 1 - a/tailleSensor ==  0*/

		if(intersect(tIn2,tIn3,beginSensor4,endSensor4))
			b = distance(beginSensor4,intersectPoint(tIn2,tIn3,beginSensor4,endSensor4));
		else
			b = tailleSensor;

		if(intersect(tOut1,tOut2,beginSensor4,endSensor4))
			c = distance(beginSensor4,intersectPoint(tOut1,tOut2,beginSensor4,endSensor4));
		else
			c = tailleSensor;

		if(intersect(tOut2,tOut3,beginSensor4,endSensor4))
			d = distance(beginSensor4,intersectPoint(tOut2,tOut3,beginSensor4,endSensor4));
		else
			d = tailleSensor;
			if(intersect(beginSensor4, endSensor4, tIn3, tIn4))
		{
			e = distance(beginSensor1, intersectPoint(tIn3, tIn4,beginSensor4, endSensor4));
		}
		else
			e = tailleSensor;

		if(intersect(beginSensor4, endSensor4, tOut3, tOut4))
		{
			f = distance(beginSensor4, intersectPoint(tOut3, tOut4,beginSensor4, endSensor4));
		}
		else
			f = tailleSensor;

		d = minimum(tailleSensor,d,e,f);
		tabSensors[3] = 1 - minimum(a,b,c,d)/tailleSensor;

	/*Capteur 5 flanc droit */
		if(intersect(tIn1,tIn2,beginSensor5,endSensor5))
			a = distance(beginSensor5,intersectPoint(tIn1,tIn2,beginSensor5,endSensor5));
		else
			a = tailleSensor; /* si a = tailleSensor ==> 1 - a/tailleSensor ==  0*/

		if(intersect(tIn2,tIn3,beginSensor5,endSensor5))
			b = distance(beginSensor5,intersectPoint(tIn2,tIn3,beginSensor5,endSensor5));
		else
			b = tailleSensor;

		if(intersect(tOut1,tOut2,beginSensor5,endSensor5))
			c = distance(beginSensor5,intersectPoint(tOut1,tOut2,beginSensor5,endSensor5));
		else
			c = tailleSensor;

		if(intersect(tOut2,tOut3,beginSensor5,endSensor5))
			d = distance(beginSensor5,intersectPoint(tOut2,tOut3,beginSensor5,endSensor5));
		else
			d = tailleSensor;
		if(intersect(beginSensor5,endSensor5, tIn3, tIn4))
		{
			e = distance(beginSensor5, intersectPoint(tIn3, tIn4,beginSensor5, endSensor5));
		}
		else
			e = tailleSensor;

		if(intersect(beginSensor5, endSensor5, tOut3, tOut4))
		{
			f = distance(beginSensor5, intersectPoint(tOut3, tOut4,beginSensor5, endSensor5));
		}
		else
			f = tailleSensor;

		d = minimum(tailleSensor,d,e,f);
		tabSensors[4] = 1 - minimum(a,b,c,d)/tailleSensor;


	/*printf("%f %f %f %f %f\n",tabSensors[0],tabSensors[1],tabSensors[2],tabSensors[3],tabSensors[4]);*/
	setSensors(sim->car, tabSensors);
	deletePoint(endSensor1);
	deletePoint(endSensor2);
	deletePoint(endSensor3);
	deletePoint(endSensor4);
	deletePoint(endSensor5);
	deletePoint(beginSensor1);
	deletePoint(beginSensor3);
	deletePoint(beginSensor5);
 }

int detectCheckPointCrossed(Simulation * sim)
{
	assert(sim != NULL);

	Point * cPin,* cPout;
	Point * carFL,  * carFR, * carBR, * carBL;
	if(sim->sector == getNbPoints(sim->track)-1)
	{
		cPin = getTrackOut(sim->track, 0);
		cPout = getTrackIn(sim->track, 0);
	}
	else
	{
		cPin = getTrackIn(sim->track, sim->sector+1);
		cPout = getTrackOut(sim->track, sim->sector+1);
	}

	carFL = getFrontLeft(sim->car);
	carFR = getFrontRight(sim->car);
	carBR = getBackRight(sim->car);
	carBL = getBackLeft(sim->car);
	/*printf("sector : %d\n CarBL : %f ,%f\n CarFL : %f,%f\n Check :%f,%f\n%f,%f\n\n",sim->sector,carBL->x,carBL->y,carFL->x,carFL->y,CPin->x,CPin->y,CPout->x,CPout->y);
	printf("\n Interesct : %d \n",intersect(CPin,CPout,carFL,carBL));*/
	if(intersect(cPin, cPout, carFR, carBR)||intersect(cPin, cPout,carFL,carBL))
		return 1;
	else
		return 0;
}

int detectCollision(Simulation * sim, int sector)/* Here we consider the Inside of the track is always on the car's right*/
{
	assert(sim != NULL);

	Point * trInUp,* trInDown, * trOutUp, * trOutDown, * tIn1, * tOut1;
	Point * carFL,  * carFR, * carBL, * carBR;

	
	trInDown = getTrackIn(sim->track, sector);
	
	trOutDown = getTrackOut(sim->track, sector);

	if(sector == 0)
	{
		tIn1 = getTrackIn(sim->track, sim->track->nbPoints-1);
		tOut1 = getTrackOut(sim->track, sim->track->nbPoints-1);
		trOutUp = getTrackOut(sim->track, sector+1);
		trInUp = getTrackIn(sim->track, sector+1);
	}
	else if(sector == getNbPoints(sim->track)-1)
	{
		tIn1 = getTrackIn(sim->track, sector-1);
		tOut1 = getTrackOut(sim->track, sector-1);	
		trInUp = getTrackIn(sim->track, 0);
		trOutUp = getTrackOut(sim->track, 0);		
	}
	else
	{
		tIn1 = getTrackIn(sim->track, sector-1);
		tOut1 = getTrackOut(sim->track, sector-1);	
		trOutUp = getTrackOut(sim->track, sector+1);
		trInUp = getTrackIn(sim->track, sector+1);
	}

	carFL = getFrontLeft(sim->car);
	carFR = getFrontRight(sim->car);
	carBL = getBackLeft(sim->car);
	carBR = getBackLeft(sim->car);

	if(intersect(tIn1, trInDown, carBR, carFR) || intersect(tOut1, trOutDown, carBR, carFR) || intersect(tIn1, trInDown, carBL, carFL) || intersect(tOut1, trOutDown, carBL, carFL)|| intersect(trInDown, trInUp, carBR, carFR) || intersect(trOutDown, trOutUp, carBR, carFR) || intersect(trInDown, trInUp, carBL, carFL) || intersect(trOutDown, trOutUp, carBL, carFL))
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
	sim->fitness = 0;

	free(sim);
}
