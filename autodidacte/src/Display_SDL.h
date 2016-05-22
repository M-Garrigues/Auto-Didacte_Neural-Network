#ifndef H_VG_DISPLAY_SDL
#define H_VG_DISPLAY_SDL


  /* Display_SDL.h    -----   LIF7 Auto-Didacte */


#include "Simulation.h"	
#include "SDL2/SDL.h"


/* structure Display_SDL */

typedef struct {
	Simulation * sim;
	int dimx;
	int dimy;
	SDL_Window * screen;
	SDL_Renderer * renderer;
	int frameRate;
	SDL_Surface * imgCar;
} Display_SDL;


/* functions Display_SDL */

/* Constructors and destructor */
Display_SDL * newDisplay_SDL(Simulation * sim, int x,int y,int fps,char * file);
void deleteDisplay_SDL(Display_SDL * disp);


/* getters and setters*/
Simulation * getSimulation(Display_SDL * display);
void setSimulation(Display_SDL * display, Simulation * newSim);

int getDimx(Display_SDL * display);
void setDimx(Display_SDL * display, int x);

int getDimy(Display_SDL * display);
void setDimy(Display_SDL * display, int y);

SDL_Window * getScreen(Display_SDL * display);
void setScreen(Display_SDL * display, SDL_Window * newScreen);

SDL_Renderer * getRenderer(Display_SDL * display);
void setRenderer(Display_SDL * display, SDL_Renderer * renderer);

int getFrameRate(Display_SDL * display);
void setFrameRate(Display_SDL * display, int newFrameRate);

SDL_Surface * getImgCar(Display_SDL * display);
void setImgCar(Display_SDL * display, SDL_Surface * newImg);

/*general functions */
void displaySim(Simulation * sim,SDL_Surface * image, SDL_Renderer * renderer);
void displayCar(Car * car, SDL_Surface * imageCar, SDL_Renderer * renderer);
void drawLine(Point * a, Point * b, SDL_Renderer * renderer);
void drawTrack(Track * track ,SDL_Renderer * renderer);
void delay(int * lastTime, int frameRate);
void loadCarImg(SDL_Surface ** img, char * filename);
void displayImage(const Point * p,float angle,SDL_Surface * image,SDL_Renderer * renderer);
void display(Display_SDL * display);
void updateScreen(Display_SDL * disp);
void cleanScreen(Display_SDL * display);
int initSDL();
void displayManagement(int x, int y , int fps, char * file);
void drawHitboxCar(Car * car, SDL_Renderer * renderer);


#endif