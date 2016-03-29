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
	if(getValue(getNeuron(out, action)) < 0.3) /*We check if the highest neuron is activated*/
		{action = NONE;}//If not, no action will be done this tick

	switch (action) {

	case NONE :
		/*printf("NONE");*/
		moveStraight(sim->car, 1); /* Try different values for moveStraight */
	 break;

	case RIGHT :
		/*printf("RIGHT");*/
	 	turnRight(sim->car);
	 	moveStraight(sim->car, 0.75);
	 break;

	case LEFT :
		/*printf("LEFT");*/
		turnLeft(sim->car);
		moveStraight(sim->car, 0.75);
	 break;
}

	if(detectCheckPointCrossed(sim)) /*The car entered a new sector, fitness improves*/
	{
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
			return -1;
		}
		else
			return sim->fitness;
	}

}


void updateSensors(Simulation * sim, int sector)
{
	assert(sim != NULL);
	float const PI = 3.14159265359;
	float * tabSensors = malloc(5*sizeof(float));
	float tailleSensor = 60;
	float a,b,c,d;
	Point * tOut1;
	Point * tIn1;
	Point * tIn2 = getTrackIn(sim->track, sim->sector);
	Point * tIn3 = getTrackIn(sim->track, sim->sector+1);

	Point * tOut2 = getTrackOut(sim->track, sim->sector);
	Point * tOut3 = getTrackOut(sim->track, sim->sector+1);

	if(sim->sector == 0)
	{
		tIn1 = getTrackIn(sim->track, sim->track->nbPoints-1);
		tOut1 = getTrackOut(sim->track, sim->track->nbPoints-1);
	}
	else
	{
		tIn1 = getTrackIn(sim->track, sim->sector-1);
		tOut1 = getTrackOut(sim->track, sim->sector-1);		
	}
	
	Point * endSensor1 = newPoint(getX(getCenter(getCar(sim)))+cos(-(PI/2) + getOrientation(getCar(sim)))*tailleSensor,getY(getCenter(getCar(sim)))+sin((-PI/2)+getOrientation(getCar(sim)))*tailleSensor);; /* flanc gauche */
	Point * endSensor2 = newPoint(getX(getCenter(getCar(sim)))+cos((-PI/4) + getOrientation(getCar(sim)))*tailleSensor,getY(getCenter(getCar(sim)))+sin((-PI/4)+getOrientation(getCar(sim)))*tailleSensor); /* coin avant gauche */
	Point * endSensor3 = newPoint(getX(getCenter(getCar(sim)))+cos(getOrientation(getCar(sim)))*tailleSensor,getY(getCenter(getCar(sim)))+sin(getOrientation(getCar(sim)))*tailleSensor); /* centre avant */
	Point * endSensor4 = newPoint(getX(getCenter(getCar(sim)))+cos((PI/4) + getOrientation(getCar(sim)))*tailleSensor,getY(getCenter(getCar(sim)))+sin((PI/4)+getOrientation(getCar(sim)))*tailleSensor); /* coin avant droit */
	Point * endSensor5 = newPoint(getX(getCenter(getCar(sim)))+cos((PI/2) + getOrientation(getCar(sim)))*tailleSensor,getY(getCenter(getCar(sim)))+sin((PI/2)+getOrientation(getCar(sim)))*tailleSensor); /* flanc droit */
	free(getSensors(sim->car));

	if(intersect(tIn1,tIn2,getCenter(sim->car),endSensor1)||intersect(tIn2,tIn3,getCenter(sim->car),endSensor1)||intersect(tOut1,tOut2,getCenter(sim->car),endSensor1)||intersect(tOut2,tOut3,getCenter(sim->car),endSensor1))
	{
		/*Si il ya une valeur non nulle a retourner */
		a = distance(getCenter(sim->car),intersectPoint(tIn1,tIn2,getCenter(sim->car),endSensor1));
		b = distance(getCenter(sim->car),intersectPoint(tIn2,tIn3,getCenter(sim->car),endSensor1));
		c = distance(getCenter(sim->car),intersectPoint(tOut1,tOut2,getCenter(sim->car),endSensor1));
		d = distance(getCenter(sim->car),intersectPoint(tOut2,tOut3,getCenter(sim->car),endSensor1));
		tabSensors[0] = 1 - minimum(a,b,c,d)/tailleSensor;
	}
	else
	{
		tabSensors[0] = 0;
	}
	if(intersect(tIn1,tIn2,getCenter(sim->car),endSensor2)||intersect(tIn2,tIn3,getCenter(sim->car),endSensor2)||intersect(tOut1,tOut2,getCenter(sim->car),endSensor2)||intersect(tOut2,tOut3,getCenter(sim->car),endSensor2))
	{
		/*Si il ya une valeur non nulle a retourner */
		a = distance(getCenter(sim->car),intersectPoint(tIn1,tIn2,getCenter(sim->car),endSensor2));
		b = distance(getCenter(sim->car),intersectPoint(tIn2,tIn3,getCenter(sim->car),endSensor2));
		c = distance(getCenter(sim->car),intersectPoint(tOut1,tOut2,getCenter(sim->car),endSensor2));
		d = distance(getCenter(sim->car),intersectPoint(tOut2,tOut3,getCenter(sim->car),endSensor2));
		tabSensors[1] = 1 - minimum(a,b,c,d)/tailleSensor;
	}
	else
	{
		tabSensors[1] = 0;
	}
	if(intersect(tIn1,tIn2,getCenter(sim->car),endSensor3)||intersect(tIn2,tIn3,getCenter(sim->car),endSensor3)||intersect(tOut1,tOut2,getCenter(sim->car),endSensor3)||intersect(tOut2,tOut3,getCenter(sim->car),endSensor3))
	{
		/*Si il ya une valeur non nulle a retourner */
		a = distance(getCenter(sim->car),intersectPoint(tIn1,tIn2,getCenter(sim->car),endSensor3));
		b = distance(getCenter(sim->car),intersectPoint(tIn2,tIn3,getCenter(sim->car),endSensor3));
		c = distance(getCenter(sim->car),intersectPoint(tOut1,tOut2,getCenter(sim->car),endSensor3));
		d = distance(getCenter(sim->car),intersectPoint(tOut2,tOut3,getCenter(sim->car),endSensor3));
		tabSensors[2] = 1 - minimum(a,b,c,d)/tailleSensor;
	}
	else
	{
		tabSensors[2] = 0;
	}
	if(intersect(tIn1,tIn2,getCenter(sim->car),endSensor4)||intersect(tIn2,tIn3,getCenter(sim->car),endSensor4)||intersect(tOut1,tOut2,getCenter(sim->car),endSensor4)||intersect(tOut2,tOut3,getCenter(sim->car),endSensor4))
	{
		/*Si il ya une valeur non nulle a retourner */
		a = distance(getCenter(sim->car),intersectPoint(tIn1,tIn2,getCenter(sim->car),endSensor4));
		b = distance(getCenter(sim->car),intersectPoint(tIn2,tIn3,getCenter(sim->car),endSensor4));
		c = distance(getCenter(sim->car),intersectPoint(tOut1,tOut2,getCenter(sim->car),endSensor4));
		d = distance(getCenter(sim->car),intersectPoint(tOut2,tOut3,getCenter(sim->car),endSensor4));
		tabSensors[3] = 1 - minimum(a,b,c,d)/tailleSensor;
	}
	else
	{
		tabSensors[3] = 0;
	}
	if(intersect(tIn1,tIn2,getCenter(sim->car),endSensor5)||intersect(tIn2,tIn3,getCenter(sim->car),endSensor5)||intersect(tOut1,tOut2,getCenter(sim->car),endSensor5)||intersect(tOut2,tOut3,getCenter(sim->car),endSensor5))
	{
		/*Si il ya une valeur non nulle a retourner */
		a = distance(getCenter(sim->car),intersectPoint(tIn1,tIn2,getCenter(sim->car),endSensor5));
		b = distance(getCenter(sim->car),intersectPoint(tIn2,tIn3,getCenter(sim->car),endSensor5));
		c = distance(getCenter(sim->car),intersectPoint(tOut1,tOut2,getCenter(sim->car),endSensor5));
		d = distance(getCenter(sim->car),intersectPoint(tOut2,tOut3,getCenter(sim->car),endSensor5));
		tabSensors[4] = 1 - minimum(a,b,c,d)/tailleSensor;
	}
	else
	{
		tabSensors[4] = 0;
	}
	printf("%f\n",tabSensors[0]);
	printf("%f\n",tabSensors[1]);
	printf("%f\n",tabSensors[2]);
	printf("%f\n",tabSensors[3]);
	printf("%f\n\n",tabSensors[4]);
	setSensors(sim->car, tabSensors);
	deletePoint(endSensor1);
	deletePoint(endSensor2);
	deletePoint(endSensor3);
	deletePoint(endSensor4);
	deletePoint(endSensor5);
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
	sim->fitness = 0;

	free(sim);
}
