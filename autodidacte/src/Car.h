#ifndef H_FB_MG_CAR
#define H_FB_MG_CAR


/* Car.h   ----- LIF7 Auto-Didacte */


#include <stdio.h>
#include "Point.h"
#include "Genome.h"




/* ----- Structure Car ----- */




/**
 * @struct Car
 * @brief The car is used for the simulation
 * 
 */
typedef struct
{
	Point * frontLeft;/** front left point adress */
	Point * frontRight;/** front right point adress */
	Point * center;/** center point adress */
	Point * backLeft;/** back left point adress */
	Point * backRight;/** back right point adress */
	float speed;/** speed of the car */
	float orientation;/** orientation of the car  */
	Network * net;/** network adress */
	float * tabSensors;/** Sensor values in an array */
}Car;


/* ----- Car constructor ----- */


/**
 * @brief      Create a new car
 *
 * @return     Car adresss
 */
Car * newCar ();

/**
 * @brief      Initialize a car with given values
 *
 * @param      car              Car adress
 * @param[in]  genome           Genome adress
 * @param[in]  init	      		Car center adress
 * @param[in]  initOrientation  Orientation of the car
 * @param[in]  lenght           Car's lenght
 * @param[in]  width            Car's width
 */
void initCar (Car * car, const Genome * genome, const Point * init, float initOrientation , float lenght, float width);


/* ----- Car getter/setter ----- */




/**
 * @brief      Get the front left.
 *
 * @param[in]  car   Car adress
 *
 * @return     Point adress
 */
Point * getFrontLeft(const Car * car);


/**
 * @brief      Set the front left.
 *
 * @param      car       Car adress
 * @param      newPoint  New point adress
 */
void setFrontLeft(Car * car, Point * newPoint);

/**
 * @brief      Get the front right.
 *
 * @param[in]  car   Car adress
 *
 * @return     Point adress
 */
Point * getFrontRight(const Car * car);


/**
 * @brief      Set the front right.
 *
 * @param      car       Car adress
 * @param      newPoint  New point adress
 */
void setFrontRight(Car * car, Point * newPoint);

/**
 * @brief      Get the center.
 *
 * @param[in] car   Car adress
 *
 * @return     Point adress
 */
Point  * getCenter(const Car * car);

/**
 * @brief      Set the center.
 *
 * @param      car       Car adress
 * @param      newPoint  New point adress
 */
void setCenter(Car * car, Point * newPoint);

/**
 * @brief      Get the back left.
 *
 * @param[in]  car   Car adress
 *
 * @return     Point adress
 */
Point * getBackLeft(const Car * car);

/**
 * @brief      Set the back left.
 *
 * @param      car       Car adress
 * @param      newPoint  New point adress
 */
void setBackLeft(Car * car, Point * newPoint);

/**
 * @brief      Get the back right.
 *
 * @param[in]  car   Car adress
 *
 * @return     Point adress
 */
Point * getBackRight(const Car * car);

/**
 * @brief      Set the back right.
 *
 * @param      car       Car adress
 * @param      newPoint  New point adress
 */
void setBackRight(Car * car,Point * newPoint);



/**
 * @brief      Get the speed.
 *
 * @param[in]  car   Car adress
 *
 * @return     Car's speed
 */
float getSpeed(const Car * car);

/**
 * @brief      Set the speed.
 *
 * @param      car       Car adress
 * @param[in]  newSpeed  New car's speed
 */
void setSpeed(Car * car, float newSpeed);

/**
 * @brief      Get the orientation.
 *
 * @param[in]  car   Car adress
 *
 * @return     Car's  orientation
 */
float getOrientation(const Car * car);


/**
 * @brief      Set the orientation.
 *
 * @param      car             Car adress
 * @param[in]  newOrientation  New car's orientation
 */
void setOrientation(Car * car, float newOrientation);

/**
 * @brief      Get the car network.
 *
 * @param[in]  car   Car adress
 *
 * @return     Car's network adress
 */
Network * getCarNetwork(const Car * car);

/**
 * @brief      Set the car network.
 *
 * @param[in]  car         Car adress
 * @param      newNetwork  Car's network adress
 */
void setCarNetwork(Car * car, Network * newNetwork);

/**
 * @brief      Get the sensors.
 *
 * @param[in]  car   Car adress
 *
 * @return     Return a float adress
 */
float * getSensors(const Car * car);


/**
 * @brief      Set the sensors.
 *
 * @param      car            Car adress
 * @param      newTabSensors  New sensor values
 */
void setSensors(Car * car, float * newTabSensors);





/* ----- Car functions ----- */




/**
 * @brief      Print the car values
 *
 * @param[in]  car   Car adress
 */
void printCar (const Car * car);



/**
 * @brief      Change the orientation and apply a rotation to all points
 *
 * @param      car    Car adress
 * @param[in]  angle  New car's orientation
 */
void changeOrientation (Car * car , float angle);



/**
 * @brief      Change the car's orientation to turn left
 *
 * @param      car   Car adress
 */
void turnLeft (Car * car);


/**
 * @brief      Change the car's orientation to turn right
 *
 * @param      car   Car adress
 */
void turnRight (Car * car);




/**
 * @brief      Move the car following his orientation
 *
 * @param      car   Car adress
 * @param[in]  time  Time to move
 */
void moveStraight (Car * car, float time);



/**
 * @brief      Increase the car's speed
 *
 * @param      car   Car adress
 */
void accelerate (Car * car);



/**
 * @brief      Decrease the car's speed
 *
 * @param      car   Car adress
 */
void decelerate (Car * car);


/* ----- Car destructor ----- */


/**
 * @brief      Delete a car
 *
 * @param      car   Car adress
 */
void deleteCar(Car * car);

#endif