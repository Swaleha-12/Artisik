#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif

#include <ctime>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>

#include "Rect.hpp"
#include "Line.hpp"
#include "LinkedList.hpp"
#include "Point.hpp"
#include "Shape.hpp"
#include "Color.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int randomNumber() //to generate random numbers
{
	return rand() % (255);
}

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture *loadTexture(std::string path);

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The window renderer
SDL_Renderer *gRenderer = NULL;

bool init()
{
	//Initialization mouseClicked
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia()
{
	//Loading success mouseClicked
	bool success = true;

	//Nothing to load
	return success;
}

void close()
{
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture *loadTexture(std::string path)
{
	//The final texture
	SDL_Texture *newTexture = NULL;

	//Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

int main(int argc, char *args[])
{
	srand(time(NULL));
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{

		if (!loadMedia()) //Load media
		{
			printf("Failed to load media!\n");
		}

		else
		{
			std::cout << "Welcome to your drawing program!\n\n"
					  << "Click on the screen and drag to draw shapes.\n"
						 "Please press one of the following keys:\n"
					  << "M --- to draw rectangles (set by default)\n"
					  << "L --- to draw lines\n"
					  << "D --- to delete the last shape you drew\n"
					  << "S --- to switch the order of shapes.\n"
					  << "By default, the shape drawn latest will appear on top, occluding any previously drawn shapes in the same region";

			bool quit = false; //Main loop controller

			SDL_Event e; //Event handler that takes care of all events

			const Uint8 *state = SDL_GetKeyboardState(NULL); // to check which key is pressed

			char keyboardInput = 'M';
			bool switchOrder = false;
			bool mouseClicked = false;
			bool mouseMoved = false;

			SDL_Rect fillRect;
			Point startPoint;
			Point endPoint;

			Shape *shape = nullptr;
			LinkedList shapeList;
			Color m_color;
			int c = 0; //To keep index/count of shapes in list

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					if (e.type == SDL_KEYDOWN) //if a key is pressed
					{
						if (state[SDL_SCANCODE_L]) //If user presses L, activate Line mode
							keyboardInput = 'L';

						else if (state[SDL_SCANCODE_M]) //If user presses M, activate rectangle mode
							keyboardInput = 'M';

						else if (state[SDL_SCANCODE_S]) //If user presses S, Switch mode
						{
							if (switchOrder)
								switchOrder = false;
							else
								switchOrder = true;
						}

						else if (state[SDL_SCANCODE_D]) //If user presses D, Delete last rendered shape
						{
							if (shapeList.getSize() > 0)
							{
								shapeList.Remove();
								c--; //decrement shape count
							}
						}
					}

					if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
					{
						//Get mouse position
						SDL_GetMouseState(&endPoint.m_x, &endPoint.m_y);

						if (e.type == SDL_MOUSEMOTION)
						{
							if (mouseClicked == true)
							{
								mouseMoved = true;
								if (keyboardInput == 'M')
									fillRect = {startPoint.m_x, startPoint.m_y, endPoint.m_x - startPoint.m_x, endPoint.m_y - startPoint.m_y};
							}
						}

						if (e.type == SDL_MOUSEBUTTONDOWN)
						{
							if (mouseClicked == false)
							{
								mouseClicked = true;
								startPoint.m_x = endPoint.m_x;
								startPoint.m_y = endPoint.m_y;
							}
						}

						if (e.type == SDL_MOUSEBUTTONUP)
						{
							mouseClicked = false;
							m_color = Color(randomNumber(), randomNumber(), randomNumber()); //assign random color
							if (mouseMoved)
							{
								if (keyboardInput == 'M') //rectangle mode
									shape = new Rect(fillRect, m_color);
								else if (keyboardInput == 'L') //line mode
									shape = new Line(startPoint, endPoint, m_color);
								shapeList.append(shape);
								c++;
								mouseMoved = false;
							}
						}
					}
				}
				//Clear screen

				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				if (!shapeList.isEmpty())
				{
					if (!switchOrder)
					{
						for (int i = 0; i < c; i++)
							shapeList[i]->draw(gRenderer);
					}
					else
					{
						for (int i = c - 1; i >= 0; i--)
							shapeList[i]->draw(gRenderer);
					}
				}

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
			delete &shapeList;
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}