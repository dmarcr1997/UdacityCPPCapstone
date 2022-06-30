#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include "Object.hpp"
#include "Utils.hpp"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("GAME v1.0", 1280, 720);
	//std::cout <<  "REFRESH: " << window.getRefreshRate() << std::endl;

	SDL_Texture* sunTexture = window.loadTexture("assets/SunTexture.png");
  	SDL_Texture* asteroidTexture = window.loadTexture("assets/AsteroidTexture.png");
  

	std::vector<Object> objectss = {
		Object(Vector2f(0, 0), sunTexture),
      	Object(Vector2f(30, 30), asteroidTexture)
    }
		

	bool gameRunning = true;

	SDL_Event event;
	
	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = Utils::hireTimeInSeconds();

	while (gameRunning)
	{
		int startTicks = SDL_GetTicks();
		float newTime = Utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;
		accumulator += frameTime;
		while(accumulator >= timeStep)
		{
			// Get our controls and events
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					gameRunning = false;
			}

			accumulator -= timeStep;
		}
		
		//const float alpha = accumulator / timeStep;

		window.clear();
		for(Object& platform: objects)
		{
			window.render(platform);
		}


		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;
		int minimum = 1000 / window.getRefreshRate();
		if(frameTicks < minimum)
			SDL_Delay(minimum - frameTicks);
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}