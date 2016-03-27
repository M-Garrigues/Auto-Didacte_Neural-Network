#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


	/*  Display_SDL.C   -----   LIF7 Auto-Didacte */


#include "Display_SDL.h"
#include "stdlib.h"
#include <SDL2/SDL2_rotozoom.h>
#include <SDL2/SDL_image.h>
#include "assert.h"
#include "stdio.h"


Display_SDL * newDisplay_SDL(Simulation * sim, int x,int y,int fps,char * file)
{
	Display_SDL * pDisp = malloc(sizeof(Display_SDL));
	SDL_Window * pScreen = NULL;
	SDL_Surface * img = NULL;
	SDL_Renderer * pRen = NULL;
	loadCarImg(&img, file);
	assert(img);
	pScreen = SDL_CreateWindow("Auto-Didacte", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,x,y,SDL_WINDOW_SHOWN);
	assert(pScreen);
	pRen = SDL_CreateRenderer(pScreen, -1, SDL_RENDERER_ACCELERATED);
	assert(pRen);
	setSimulation(pDisp, sim);
	setDimx(pDisp, x);
	setDimy(pDisp, y);
	setFrameRate(pDisp, fps);
	setImgCar(pDisp, img);
	setRenderer(pDisp, pRen);
	setScreen(pDisp, pScreen);
	return pDisp;
}
void deleteDisplay_SDL(Display_SDL * disp)
{
	endSimulation(disp->sim);
	SDL_FreeSurface(disp->imgCar);
	SDL_DestroyRenderer(disp->renderer);
	SDL_DestroyWindow(disp->screen);
	free(disp);
}


/* getters and setters*/
Simulation * getSimulation(Display_SDL * display)
{
	return display->sim;
}
void setSimulation(Display_SDL * display, Simulation * newSim)
{
	display->sim = newSim;
}

SDL_Renderer * getRenderer(Display_SDL * display)
{
	return display->renderer;
}
void setRenderer(Display_SDL * display, SDL_Renderer * newRenderer)
{
	display->renderer = newRenderer;
}

int getDimx(Display_SDL * display)
{
	return display->dimx;
}
void setDimx(Display_SDL * display, int x)
{
	display->dimx = x;
}

int getDimy(Display_SDL * display)
{
	return display->dimy;
}
void setDimy(Display_SDL * display, int y)
{
	display->dimy = y;
}

SDL_Window * getScreen(Display_SDL * display)
{
	return display->screen;
}
void setScreen(Display_SDL * display, SDL_Window * newScreen)
{
	display->screen = newScreen;
}

int getFrameRate(Display_SDL * display)
{
	return display->frameRate;
}

void setFrameRate(Display_SDL * display, int newFrameRate)
{
	display->frameRate = newFrameRate;
}

SDL_Surface * getImgCar(Display_SDL * display)
{
	return display->imgCar;
}
void setImgCar(Display_SDL * display, SDL_Surface * newImg)
{
	display->imgCar = newImg;
}
void displayImage(const Point * p,float angle,SDL_Surface * image,SDL_Renderer * renderer)
{
	SDL_Texture * tex;
	SDL_Surface * imageM;
	SDL_Rect dist;
	imageM = rotozoomSurface(image, -angle, 1.0, 1);
	dist.h = imageM->h;
	dist.w = imageM->w;
	dist.x = p->x - imageM->w /2;
	dist.y = p->y - imageM->h /2;
	tex = SDL_CreateTextureFromSurface(renderer,imageM);	
	SDL_RenderCopy(renderer, tex, NULL, &dist);
    SDL_FreeSurface(imageM);
   	SDL_DestroyTexture(tex);
}

void displayCar(Car * car, SDL_Surface * image, SDL_Renderer * renderer)
{
	float angleDeg = car->orientation*180/3.14159265359; /* On devrait définir une constante PI*/
	Point p;
	p.x = getCenter(car)->x;
	p.y = getCenter(car)->y;
	displayImage(&p ,angleDeg,image,renderer);
}

void drawLine(Point * a, Point * b, SDL_Renderer * renderer)
{
	SDL_RenderDrawLine(renderer,a->x,a->y,b->x,b->y);
}
void drawTrack(Track * track,SDL_Renderer * renderer)
{
	int i;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
	for(i =1 ; i< track->nbPointIn;i++)
		drawLine(track->trackIn[i-1],track->trackIn[i],renderer);
	for(i =1 ; i< track->nbPointOut;i++)
		drawLine(track->trackOut[i-1],track->trackOut[i],renderer);
	drawLine(track->trackIn[0],track->trackIn[track->nbPointIn-1],renderer);
	drawLine(track->trackOut[0],track->trackOut[track->nbPointOut-1],renderer);
}
void displaySim(Simulation * sim, SDL_Surface * imgCar, SDL_Renderer * renderer)
{
	displayCar(sim->car,imgCar,renderer);
	drawTrack(sim->track, renderer);
}
void loadCarImg(SDL_Surface ** img, char * filename)
{
	*img = IMG_Load(filename);
	if(*img == NULL)
	{
		printf("L'image n'a pas pu être chargée! SDL_Error : %s\n", SDL_GetError());
	}
}
void cleanScreen(Display_SDL * display)
{
	SDL_SetRenderDrawColor(display->renderer, 50, 50, 50, 255);
   	SDL_RenderClear(display->renderer);
}

void delay(int * lastTime, int frameRate)
{	
	unsigned int actualTime = SDL_GetTicks();
	if(actualTime - *lastTime > 1000/frameRate)
	{
		*lastTime = actualTime;
	}
	else 
	{
		SDL_Delay(1000/frameRate - (actualTime - *lastTime));	
		delay(lastTime,frameRate);
	}
}
void updateScreen(Display_SDL * disp)
{
	SDL_RenderPresent(disp->renderer);
}
int initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return 0;
    }
    else
    {
    	return 1;
    }
}
void display(Display_SDL * display)
{
	displaySim(display->sim, display->imgCar, display->renderer);
	updateScreen(display);
}

void displayManagement(Simulation * sim, int x, int y , int fps, char * file)
{
	if(initSDL())
	{
		SDL_Event event;
		Display_SDL * disp = newDisplay_SDL(sim,x,y,fps,file);
		int ticks = SDL_GetTicks();
		int continuer = 1;
		while(continuer)
		{
			while (SDL_PollEvent(&event))/* gestion des evenements */
    		{
    		    switch(event.type)
    		    {
        	    case SDL_QUIT:
            	   continuer = 0;
            	   break;
            	default:
            		break;
            	}
        	}
        	delay(&ticks, fps);
        	/*oneStepSimulation(disp->sim);*/
        	cleanScreen(disp);
        	display(disp);
		}
		deleteDisplay_SDL(disp);
		SDL_Quit();
	}
}