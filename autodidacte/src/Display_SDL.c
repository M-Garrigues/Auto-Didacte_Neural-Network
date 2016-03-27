#ifdef __cplusplus
#error This source file is not C++ but rather C. Please use a C-compiler
#endif


	/*  Display_SDL.C   -----   LIF7 Auto-Didacte */


#include "Display_SDL.h"
#include "stdlib.h"
#include "assert.h"
#include "stdio.h"

#if 0
void displayImage(int x,int y,float angle,SDL_Surface * image,SDL_Renderer * renderer)
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

void displayCar(Car * car, SDL_Surface * image, SDL_Renderer * renderer)
{
	float angleDeg = car->orientation*180/3.14159265359; /* On devrait définir une constante PI*/
	float x,y;
	x = (car->center).x; /* a changer avec les getters*/
	y = (car->center).y;
	displayImage(x,y,angleDeg,image,renderer);
}

void drawLine(Point a, Point b, SDL_Renderer * renderer)
{
	SDL_RenderDrawLine(renderer,a.x,a.y,b.x,b.y);
}
void drawTrack(int nbPoint, Point * pA, Point * pB ,SDL_Renderer * renderer)
{
	int i;
	for(i =1 ; i< nbPoint;i++)
		drawLine(pA[i-1],pA[i],renderer);
	for(i =1 ; i< nbPoint;i++)
		drawLine(pB[i-1],pB[i],renderer);
	drawLine(pA[0],pA[nbPoint-1],renderer);
	drawLine(pB[0],pB[nbPoint-1],renderer);
}
void displaySim(Simulation * sim,SDL_Renderer * renderer)
{
	

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
	SDL_SetRenderDrawColor(renderer, 50, 50, 255, 255);
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
#endif