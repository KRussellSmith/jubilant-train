//C++ is a language best used on crack (unfortanately, i only have coffee.)
//(however, if i ever have to write a line of javascript again, it'd be too soon.)
#include <stdio.h>
#include <math.h>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Game.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


int main(int argc, char *argv[])
{
	SDL_Window  *window = NULL;
	SDL_Surface *surface  = NULL;
	
	int tick;
	if(SDL_Init(SDL_INIT_VIDEO) <  0)
	{
		printf("SDL failed to initialize: %s\n", SDL_GetError());
		return 0;
	}
	window = SDL_CreateWindow(
		"Snake",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	
	if (window == NULL)
	{
		printf("Failed to create window: %s\n", SDL_GetError());
		return 0;
	}
	
	if (TTF_Init() < 0)
	{
		return 0;
	}
	
	auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_Event ev;
	bool run = true;
	Game game(30, 100);
			
	while (run)
	{
		auto start_t = std::chrono::steady_clock::now();
				
		if (tick > game.tick)
		{
			game.update();
			tick = 0;
		}
		
		SDL_SetRenderDrawColor(
			renderer,
			0x12, 0x12, 0x12, 0xFF);
		SDL_RenderClear(renderer);
				
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
				case SDL_QUIT:
					run = false;
					break;
				default:
					game.handle_input(&ev);
					break;
			}
		}
		game.draw(renderer);
		SDL_RenderPresent(renderer);
				
		auto end_t = std::chrono::steady_clock::now();
		tick += std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
	}
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}