#ifndef GAME_HPP
#define GAME_HPP

#include "Dir.hpp"
#include "Touch.hpp"
#include "Text.hpp"
#include "Snake.hpp"
#include <SDL2/SDL.h>

class Game
{
private:
	Snake snake;
	Coord fish;
	bool over;
	bool run;
	int score, high_score;
	Text score_txt;
	Text start_txt;
	Text over_txt;
	int next_dir;
	int cell_size;
	
	void set_cell_size();
public:
	int size, tick;
	Game(int size, int tick);
	void init();
	void update();
	void save_score();
	void draw(SDL_Renderer *renderer);
	void spawn_fish();
	void handle_input(SDL_Event *ev);
};
#endif