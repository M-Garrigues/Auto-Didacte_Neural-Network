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
	imageM = rotozoomSurface(image, angle, 1.0, 1);
	dist.h = imageM->h;
	dist.w = imageM->w;
	dist.x = x - imageM->w /2;
	dist.y = y - imageM->h /2;
	tex = SDL_CreateTextureFromSurface(renderer,imageM);	
	SDL_RenderCopy(renderer, tex, NULL, &dist);
 	SDL_RenderPresent(renderer);
    SDL_FreeSurface(imageM);
   	SDL_DestroyTexture(tex);
}

void displayCar(Car * car, SDL_Surface * image, SDL_Renderer * renderer)
{
	float angleDeg = car->orientation*180/3.14159265359; /* On devrait définir une constante PI*/
	int x,y;
	x = (int) 5*(car->center).x; /* a changer avec les getters*/
	y = (int) 5*(car->center).y;
	displayImage(x,y,angleDeg,image,renderer);
}
#endif