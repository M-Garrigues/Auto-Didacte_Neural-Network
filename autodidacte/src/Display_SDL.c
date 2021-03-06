
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
	loadImg(&img, file);
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
	dist.x = getX(p) - imageM->w /2;
	dist.y = getY(p) - imageM->h /2;
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
	for(i =1 ; i< track->nbPoints;i++)
		drawLine(track->trackIn[i-1],track->trackIn[i],renderer);
	for(i =1 ; i< track->nbPoints;i++)
		drawLine(track->trackOut[i-1],track->trackOut[i],renderer);
	drawLine(track->trackIn[0],track->trackIn[track->nbPoints-1],renderer);
	drawLine(track->trackOut[0],track->trackOut[track->nbPoints-1],renderer);
}
void displaySim(Simulation * sim, SDL_Surface * imgCar, SDL_Renderer * renderer)
{
	float const PI = 3.14159265359;
	float tailleSensor = 60;
	Point * beginSensor1 = middle(getBackLeft(sim->car),getFrontLeft(sim->car));
	Point * beginSensor2 = getFrontLeft(sim->car);
	Point * beginSensor3 = middle(getFrontLeft(sim->car),getFrontRight(sim->car));
	Point * beginSensor4 = getFrontRight(sim->car);
	Point * beginSensor5 = middle(getBackRight(sim->car), getFrontRight(sim->car));
	Point * endSensor1 = newPoint(getX(beginSensor1)+cos(-(PI/2) + getOrientation(getCar(sim)))*tailleSensor,getY(beginSensor1)+sin((-PI/2)+getOrientation(getCar(sim)))*tailleSensor);; /* flanc gauche */
	Point * endSensor2 = newPoint(getX(beginSensor2)+cos((-PI/4) + getOrientation(getCar(sim)))*tailleSensor,getY(beginSensor2)+sin((-PI/4)+getOrientation(getCar(sim)))*tailleSensor); /* coin avant gauche */
	Point * endSensor3 = newPoint(getX(beginSensor3)+cos(getOrientation(getCar(sim)))*tailleSensor,getY(beginSensor3)+sin(getOrientation(getCar(sim)))*tailleSensor); /* centre avant */
	Point * endSensor4 = newPoint(getX(beginSensor4)+cos((PI/4) + getOrientation(getCar(sim)))*tailleSensor,getY(beginSensor4)+sin((PI/4)+getOrientation(getCar(sim)))*tailleSensor); /* coin avant droit */
	Point * endSensor5 = newPoint(getX(beginSensor5)+cos((PI/2) + getOrientation(getCar(sim)))*tailleSensor,getY(beginSensor5)+sin((PI/2)+getOrientation(getCar(sim)))*tailleSensor); /* flanc droit */
	Point * cPout;
	Point * cPin;
	if(getSector(sim) == getNbPoints(getTrack(sim))-1)
	{	
		cPin = getTrackOut(getTrack(sim), 0);
		cPout = getTrackIn(getTrack(sim), 0);
	}
	else
	{
		cPin = getTrackIn(getTrack(sim), getSector(sim)+1);
		cPout = getTrackOut(getTrack(sim), getSector(sim)+1);
	}
	

	displayCar(getCar(sim),imgCar,renderer);
	drawTrack(getTrack(sim), renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0,255);
	drawLine(cPin,cPout,renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 255,255);
	drawLine(beginSensor1,endSensor1,renderer);
	drawLine(beginSensor2,endSensor2,renderer);
	drawLine(beginSensor3,endSensor3,renderer);
	drawLine(beginSensor4,endSensor4,renderer);
	drawLine(beginSensor5,endSensor5,renderer);
	deletePoint(endSensor1);
	deletePoint(endSensor2);
	deletePoint(endSensor3);
	deletePoint(endSensor4);
	deletePoint(endSensor5);
	deletePoint(beginSensor1);
	deletePoint(beginSensor3);
	deletePoint(beginSensor5);
	

}
void loadImg(SDL_Surface ** img, char * filename)
{
	*img = IMG_Load(filename);
	if(*img == NULL)
	{
		printf("L'image n'a pas pu être chargée! SDL_Error : %s\n", SDL_GetError());
	}
}
void cleanScreen(Display_SDL * display)
{
	SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
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
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0  )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return 0;
    }
    else if ( TTF_Init()!=0)
    {
    	printf("%s\n", TTF_GetError());
    	return 0;
    }
    else
    	return 1;
}
void displayButton(Display_SDL * display, int * mode)
{
	SDL_Surface * button1, * button2, * button3, *button4;
	Point * buttonPoint2 = newPoint(385,510);
	Point * buttonPoint1 = newPoint(115,510);
	Point * buttonPoint3 = newPoint(270,510);
	Point * buttonPoint4 = newPoint(540,510);
	if(mode[0])
		loadImg(&button1, "data/fastComp.png");
	else
		loadImg(&button1, "data/fastCompOn.png");
	if(mode[1])
		loadImg(&button2, "data/seeBest.png");
	else
		loadImg(&button2, "data/resume.png");
	loadImg(&button3, "data/reset.png");
	loadImg(&button4, "data/changeTrack.png");

	displayImage(buttonPoint1,0,button1,display->renderer);/* display the button */
	displayImage(buttonPoint2,0,button2,display->renderer);
	displayImage(buttonPoint3,0,button3,display->renderer);
	displayImage(buttonPoint4,0,button4,display->renderer);


	deletePoint(buttonPoint1);
	SDL_FreeSurface(button1);
	deletePoint(buttonPoint2);
	SDL_FreeSurface(button2);
	deletePoint(buttonPoint3);
	SDL_FreeSurface(button3);
	deletePoint(buttonPoint4);
	SDL_FreeSurface(button4);
}
void display(Display_SDL * display)
{
	displaySim(display->sim, display->imgCar, display->renderer);
	updateScreen(display);
}
#if 1
void displayManagement(int x, int y , int fps, char * file)
{
	if(initSDL())
    {
    	FILE * f = fopen("data/circle.track", "r");
		int tab[3] = {6, 5, 4};
		float initOrient = 0;
		srand(time(NULL));
		Generation * gen = newGenerationRandom(30, tab);
		Track * track = newTrack();
		Point * pInit;
		initTrackFile(track,f);
		fclose(f);
		pInit = intersectPoint (getTrackIn(track , 0) , getTrackOut(track ,1) , getTrackOut(track,0) , getTrackIn(track,1));
        SDL_Event event;
        Simulation * sim = newSimulation(1 ,getGenome(gen , 0), track, pInit, initOrient);
        Display_SDL * disp = newDisplay_SDL(sim,x,y,fps,file);
        int trackNb = 0;
        int ticks = SDL_GetTicks();
        int mode[2] = {1,1};
        int g = 1;
        int fitness = -1;
        int i = 0; /* indique le genome en cours de simulation */
        int go = 1;
        while(go)
        {
            while (SDL_PollEvent(&event))/* gestion des evenements */
            {
                switch(event.type)
                {
	                case SDL_QUIT:
	                    go = 0;
	                    break;
	                case SDL_MOUSEBUTTONDOWN:
	                	if(event.button.button == SDL_BUTTON_LEFT)
	                	{
	                		if(event.button.x >= 20 && event.button.x <=215 && event.button.y <= 535 && event.button.y >= 495)
	                		{
	                			mode[0] = (mode[0]+1)%2;
	                			displayButton(disp,mode);
	                			updateScreen(disp);
	                		}
	                		else if( event.button.x >= 330 && event.button.x <=440&& event.button.y <= 535 && event.button.y >= 495)
	                		{
	                			mode[1] = (mode[1] +1)%2;
	                			displayButton(disp, mode);
	                			sim = newSimulation(1, getGenome(gen, 0), track, pInit, initOrient);
                				endSimulation(getSimulation(disp));
                				setSimulation(disp, sim);
                				fitness = -1;
	                			updateScreen(disp);
	                		}
	                		else if(event.button.x >= 230 && event.button.x <=310 && event.button.y <= 535 && event.button.y >= 495)
	                		{
	                			deleteGeneration(gen);
	                			gen = newGenerationRandom(30,tab);
	                			i = 0;
	                			g = 1;
	                			endSimulation(getSimulation(disp)); /* recommencer la simulation*/
	                			sim = newSimulation(1, getGenome(gen, i), track, pInit, initOrient);
	                			setSimulation(disp, sim);
	                		}
	                		else if(event.button.x >= 465 && event.button.x <=620 && event.button.y <= 535 && event.button.y >= 495)
	                		{
	                			deleteTrack(track);
	                			track = newTrack();
	                			fitness = -1; /* empeche le blocage dans la boucle see best*/
	                			trackNb = (trackNb+1)%3;
	                			if(trackNb==1)
	                			{
	                				f = fopen("data/basic.track","r");
	                			}
	                			else if(trackNb == 0)
	                			{
	                				f = fopen("data/circle.track","r");
	                			}
	                			else
	                			{
	                				f = fopen("data/complex.track","r");
	                			}
	                			initTrackFile(track,f);
	                			deletePoint(pInit);
	                			pInit = intersectPoint(track->trackIn[0] , track->trackOut[1] , track->trackOut[0] , track->trackIn[1]);
	                			i = 0; /* on recommence toute la simulation car les fitness ne sont plus les memes*/
	                			endSimulation(getSimulation(disp));
	            	  			sim = newSimulation(1, getGenome(gen ,i), track, pInit, initOrient);
	                			setSimulation(disp, sim);
	                			cleanScreen(disp);
	                			displayButton(disp, mode);
	                			display(disp);
	                			fclose(f);
	                		}

	                	}
	                	break;
	                default:
                        break;
                }
            }
            if(mode[1] )
            {
              	if(fitness == -1)
            	{
            		
            			fitness = tickSimulation(disp->sim);
            			if(mode[0] == 1)
            			{
            				delay(&ticks, fps);
            	  			cleanScreen(disp);
            	  			displayInfo( getFitness(getGenome(gen ,0)),g, disp->renderer);
            	  			displayButton(disp,mode);
            	  			display(disp);
            	  		}
           		 }
            	else
            	{
            	    setFitness(getGenome(gen, i),fitness);
            	    i++;
            	    if(i == getNbSubject(gen))
            	    {
            	    	nextGeneration(gen);
            	    	cleanScreen(disp);
            	  		displayInfo( getFitness(getGenome(gen ,0)),g, disp->renderer);
            	  		displayButton(disp,mode);
            	  		display(disp);
            	    	g++;
            	        i = 1;
                	}
               		 else
                	{
                		sim = newSimulation(1, getGenome(gen, i), track, pInit, initOrient);
                    	endSimulation(getSimulation(disp));
                    	setSimulation(disp, sim);
                	    fitness = -1;
                	}
            	}
            }
            else
            {
            	delay(&ticks, fps);
            	if(fitness == -1)
            	{
            		
            			fitness = tickSimulation(disp->sim);
            	  		cleanScreen(disp);
            	  		displayInfo( getFitness(getGenome(gen ,0)),g, disp->renderer);
            	  		displayButton(disp,mode);
            	  		display(disp);
           		}
            }

        }
        deleteDisplay_SDL(disp);
        TTF_Quit();
        SDL_Quit();
        deleteGeneration(gen);
        deleteTrack(track);
        deletePoint(pInit);
    }

}


void drawHitboxCar(Car * car, SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 0,255);
	drawLine(getBackLeft(car),getBackRight(car),renderer);
	drawLine(getBackRight(car),getFrontRight(car),renderer);
	drawLine(getBackLeft(car),getFrontLeft(car),renderer);
	drawLine(getFrontLeft(car),getFrontRight(car), renderer);
}

void displayInfo(int fitness, int generation, SDL_Renderer * renderer)
{

	char sentence[100];
	TTF_Font * font;
	font=TTF_OpenFont("data/arial.ttf",15);
if(!font) {
printf("TTF_OpenFont: %s\n", TTF_GetError());
// handle error
}
    SDL_Color white = {255, 255, 255}; 
    Point *p = newPoint(330,80);
    sprintf(sentence, "Generation : %d  Fitness Max : %d", generation,fitness);
    SDL_Surface * text = TTF_RenderText_Blended(font, sentence, white);
    
    displayImage(p,0,text,renderer);
    SDL_FreeSurface(text);
    TTF_CloseFont(font);
    deletePoint(p);

}
#endif

