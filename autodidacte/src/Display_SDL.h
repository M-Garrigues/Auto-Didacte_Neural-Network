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
/**
 * @brief      Initialise a display_SDL object
 *
 * @param      sim   The simulation 
 * @param[in]  x     the x size of the window
 * @param[in]  y     the y size of the window
 * @param[in]  fps   The frame rate
 * @param      file  The file of the car image
 *
 * @return     the display_SDL initialised
 */
Display_SDL * newDisplay_SDL(Simulation * sim, int x,int y,int fps,char * file);
/**
 * @brief      delete a display_SDL object
 *
 * @param      disp  The dispay to delete
 */
void deleteDisplay_SDL(Display_SDL * disp);


/* getters and setters*/
/**
 * @brief      Gets the simulation.
 *
 * @param      display  The display you want to get the simulation
 *
 * @return     The simulation.
 */
Simulation * getSimulation(Display_SDL * display);
/**
 * @brief      Sets the simulation.
 *
 * @param      display  The display you want to change the simulation
 * @param      newSim   The new simulation
 */
void setSimulation(Display_SDL * display, Simulation * newSim);
/**
 * @brief      Gets the dimx.
 *
 * @param      display  The display you want to get the dimx
 *
 * @return     The dimx.
 */
int getDimx(Display_SDL * display);
/**
 * @brief      Sets the dimx.
 *
 * @param      display  The display you want to change the dimx
 * @param[in]  x        the new dimx
 */
void setDimx(Display_SDL * display, int x);
/**
 * @brief      Gets the dimy.
 *
 * @param      display  The display you want the dimy
 *
 * @return     The dimy.
 */
int getDimy(Display_SDL * display);
/**
 * @brief      Sets the dimy.
 *
 * @param      display  The display you want to change the dimy
 * @param[in]  y        the new dimy
 */
void setDimy(Display_SDL * display, int y);
/**
 * @brief      Gets the screen.
 *
 * @param      display  The display you want the screen
 *
 * @return     The screen.
 */
SDL_Window * getScreen(Display_SDL * display);
/**
 * @brief      Sets the screen.
 *
 * @param      display    The display you want to change the screen
 * @param      newScreen  The new screen
 */
void setScreen(Display_SDL * display, SDL_Window * newScreen);
/**
 * @brief      Gets the renderer.
 *
 * @param      display  The display you want to get the renderer
 *
 * @return     The renderer.
 */
SDL_Renderer * getRenderer(Display_SDL * display);
/**
 * @brief      Sets the renderer.
 *
 * @param      display   The display you want to change the renderer
 * @param      renderer  The renderer
 */
void setRenderer(Display_SDL * display, SDL_Renderer * renderer);
/**
 * @brief      Gets the frame rate.
 *
 * @param      display  The display you want the frame rate
 *
 * @return     The frame rate.
 */
int getFrameRate(Display_SDL * display);
/**
 * @brief      Sets the frame rate.
 *
 * @param      display       The display you want to change the framerate
 * @param[in]  newFrameRate  The new frame rate
 */
void setFrameRate(Display_SDL * display, int newFrameRate);
/**
 * @brief      Gets the image car.
 *
 * @param      display  The display you want the image of the car
 *
 * @return     The image of the car.
 */
SDL_Surface * getImgCar(Display_SDL * display);
/**
 * @brief      Sets the car image.
 *
 * @param      display  The display you want to change the car image
 * @param      newImg   The new image
 */
void setImgCar(Display_SDL * display, SDL_Surface * newImg);

/*general functions */
/**
 * @brief      display the content of a simulation on a renderer with an image for the car
 *
 * @param[in]      sim       The simulation
 * @param[in]     image     The image of the car
 * @param[in,out]     renderer  The renderer
 */
void displaySim(Simulation * sim,SDL_Surface * image, SDL_Renderer * renderer);
/**
 * @brief      display a car on a renderer with an image for the car
 *
 * @param      car       The car
 * @param      imageCar  The car image
 * @param      renderer  The renderer
 */
void displayCar(Car * car, SDL_Surface * imageCar, SDL_Renderer * renderer);
/**
 * @brief      draws a line between 2 points on a renderer
 *
 * @param      a         the first point
 * @param      b         the second point
 * @param      renderer  The renderer
 */
void drawLine(Point * a, Point * b, SDL_Renderer * renderer);
/**
 * @brief      draws a track on a renderer
 *
 * @param      track     The track
 * @param      renderer  The renderer
 */
void drawTrack(Track * track ,SDL_Renderer * renderer);
/**
 * @brief      delays the time to keep a stable frame rate
 *
 * @param      lastTime   The last number of ticks
 * @param[in]  frameRate  The frame rate
 */
void delay(int * lastTime, int frameRate);
/**
 * @brief      Loads an image in a surface.
 *
 * @param      img       The surface where the image is stored
 * @param      filename  The filenameof the image you want to load
 */
void loadImg(SDL_Surface ** img, char * filename);
/**
 * @brief      display an image with a rotation on a renderer
 *
 * @param[in]  p         the point to center the image on
 * @param[in]  angle     The angle of rotation
 * @param      image     The image
 * @param      renderer  The renderer
 */
void displayImage(const Point * p,float angle,SDL_Surface * image,SDL_Renderer * renderer);
/**
 * @brief      display all the content of the display
 *
 * @param      display  The display
 */
void display(Display_SDL * display);
/**
 * @brief      refresh the screen of a display
 *
 * @param      disp  The display
 */
void updateScreen(Display_SDL * disp);
/**
 * @brief      clean the screen of a display with black
 *
 * @param      display  The display
 */
void cleanScreen(Display_SDL * display);
/**
 * @brief      initialise all the component of SDL2 needed for the application
 *
 * @return     1 if all is loaded correctly 0 if not
 */
int initSDL();
/**
 * @brief      manage the whole display and link the modules together
 *
 * @param[in]  x     the width of the window
 * @param[in]  y     the height of the window
 * @param[in]  fps   The frame rate
 * @param      file  The filename of the car image
 */
void displayManagement(int x, int y , int fps, char * file);
/**
 * @brief      draws the hitbox of the car on a renderer
 *
 * @param      car       The car
 * @param      renderer  The renderer
 */
void drawHitboxCar(Car * car, SDL_Renderer * renderer);


#endif