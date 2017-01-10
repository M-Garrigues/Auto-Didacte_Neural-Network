#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


	/*  main.C   -----   LIF7 Auto-Didacte  TEST ANN */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Display_SDL.h"

/*

Project coded by Valentin GRANDJEAN, Florian BEGONIN and Mathieu GARRIGUES (2016).

*/



int main()
{
	displayManagement(641, 540 , 60, "data/car.png");
	return 0;
}