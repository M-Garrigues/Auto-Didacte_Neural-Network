#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


	/*  Display_SDL.C   -----   LIF7 Auto-Didacte */


#include "Display_SDL.h"
#include "stdlib.h"
#include "assert.h"
#include "stdio.h"


Display_SDL * newDisplay_SDL(Simulation * sim, int x,int y,int fps,char * file)
{
	Display_SDL * pDisp = malloc(sizeof(Display_SDL));
	SDL_Window * pScreen;
	SDL_Surface * img;
	SDL_Renderer * pRen;
	loadCarImg(&img, file);
	pScreen = SDL_CreateWindow("Auto-Didacte", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,x,y,SDL_WINDOW_SHOWN);
	pRen = SDL_CreateRenderer(pScreen, -1, SDL_RENDERER_ACCELERATED);
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
	deleteSimulation(disp->sim);
	SDL_FreeSurface(imgCar);
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
	dist.x = x - imageM->w /2;
	dist.y = y - imageM->h /2;
	tex = SDL_CreateTextureFromSurface(renderer,imageM);	
	SDL_RenderCopy(renderer, tex, NULL, &dist);
    SDL_FreeSurface(imageM);
   	SDL_DestroyTexture(tex);
}

void displayCar(const Car * car, SDL_Surface * image, SDL_Renderer * renderer)
{
	float angleDeg = car->orientation*180/3.14159265359; /* On devrait définir une constante PI*/
	Point p;
	p.x = getCenter(car)->x; /* a changer avec les getters*/
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
	for(i =1 ; i< track->nbIn;i++)
		drawLine(track->trackIn[i-1],track->trackIn[i],renderer);
	for(i =1 ; i< track->nbOut;i++)
		drawLine(track->trackOut[i-1],track->trackOut[i],renderer);
	drawLine(track->trackIn[0],track->trackIn[track->nbIn-1],renderer);
	drawLine(track->trackOut[0],track->trackOut[track->nbOut-1],renderer);
}
void displaySim(Simulation * sim, SDL_Surface imgCar, SDL_Renderer * renderer)
{
	cleanScreen(renderer);
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
void cleanScreen(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
   	SDL_RenderClear(renderer);
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
void updateScreen(SDL_Display * disp)
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
