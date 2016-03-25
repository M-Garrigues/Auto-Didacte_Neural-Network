#ifndef H_VG_DISPLAY_SDL
#define H_VG_DISPLAY_SDL


  /* Display_SDL.h    -----   LIF7 Auto-Didacte */


#include "Simulation.h"	

/* structure Display_SDL */

typedef struct {
	Simulation * sim;
	int dimx;
	int dimy;
} Display_SDL;


/* functions Display_SDL */

/* Constructors and destructor */
Display_SDL * newDisplay_SDL(Simulation * sim, int x,int y);


/* getters and setters*/


/*general functions */



#endif