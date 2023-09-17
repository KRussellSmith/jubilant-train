#include "Game.hpp"
#include "Dir.hpp"
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <fstream>

#define SCORE_FILE "score.dat"

Game::Game(int size, int tick)
{
	std::ifstream score_f(SCORE_FILE, std::ios::out | std::ios::binary);
	if (score_f)
	{
		score_f.read((char *)&high_score, sizeof(high_score));
	}
	score_f.close();
	this->size = size;
	this->tick = tick;
	init();
}
void Game::set_cell_size()
{
	static SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	cell_size = (int)fmin(DM.w, DM.h) / size;
	score = 0;
}
void Game::init()
{
	run = false;
	over = false;
	snake.init(0, 0);
	next_dir = snake.dir;
	spawn_fish();
	set_cell_size();
	score_txt.set_font(
		"Roboto-Regular.ttf", cell_size,
		{ 0xAA, 0xEB, 0xA4, 0xFF });
	start_txt.set_font(
		"Roboto-Regular.ttf", cell_size * 2,
		{  0xE3, 0x78, 0x76, 0xFF });
	over_txt.set_font(
		"Roboto-Regular.ttf", cell_size * 2,
		{  0xE3, 0x78, 0x76, 0xFF });
}
void Game::update()
{
	if (over || !run)
	{
		return;
	}
	snake.turn(next_dir);
	if (snake.head->x == fish.x && snake.head->y == fish.y)
	{
		snake.grow();
		spawn_fish();
		++score;
		if (score > high_score)
		{
			high_score = score;
			save_score();
		}
	}
	else
	{
		snake.move();
	}
	
	if (snake.bad_move(size))
	{
		over = true;
	}
}
void Game::save_score()
{
	std::ofstream score_f(SCORE_FILE, std::ios::out | std::ios::binary);
	score_f.write((char*)&high_score, sizeof(high_score));
	score_f.close();
}
void Game::draw(SDL_Renderer *renderer)
{
	static SDL_Rect bounds;
	static SDL_Rect fish_r;
	static SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
		
	fish_r.w = cell_size;
	fish_r.h = cell_size;
		
	bounds.w = cell_size * size;
	bounds.h = cell_size * size;
	bounds.x = DM.w / 2 - bounds.w / 2;
	bounds.y = DM.h / 2 - bounds.h / 2;
		
	SDL_SetRenderDrawColor(
		renderer,
		0xAA, 0xEB, 0xA4, 0xFF);
	fish_r.x = bounds.x + fish.x * cell_size;
	fish_r.y = bounds.y + fish.y * cell_size;
	SDL_RenderFillRect(
		renderer, &fish_r);
		
	snake.draw(renderer, &bounds, cell_size);
		
	SDL_SetRenderDrawColor(
		renderer,
		0xE3, 0x78, 0x76, 0xFF);
	
	int b_stroke = cell_size / 10;
	for (int i = 0; i < b_stroke; ++i)
	{
		SDL_RenderDrawRect(
			renderer, &bounds);
		bounds.x += 1;
		bounds.y += 1;
		bounds.w -= 1;
		bounds.h -= 1;
	}
		
	std::string text = "score: " + std::to_string(score);
	score_txt.set_text(
	renderer, text.c_str(),
		cell_size / 2, cell_size / 2);
	score_txt.render(renderer);
	text = "high: " + std::to_string(high_score);
	score_txt.set_text(
		renderer, text.c_str(),
		cell_size / 2, cell_size * 1.5);
	score_txt.render(renderer);
		
	if (over)
	{
		over_txt.set_align(Align::CENTER);
		over_txt.set_text(
			renderer, "Game Over",
			DM.w / 2, DM.h / 2);
		over_txt.render(renderer);
	}
	if (!run)
	{
		start_txt.set_align(Align::CENTER);
		start_txt.set_text(
			renderer, "tap to start",
			DM.w / 2, DM.h / 2);
		start_txt.render(renderer);
	}
}
void Game::spawn_fish()
{
	if (snake.len >= size * size) return;
		
	int x, y, check;
	do
	{
		check = false;
		x = rand() % size;
		y = rand() % size;
		for (auto node = snake.head; node; node = node->next)
		{
			if (x == node->x && y == node->y)
			{
				 check = true;
				 break;
			}
		}
	} while(check);
	
	fish.x = x;
	fish.y = y;
}
void Game::handle_input(SDL_Event *ev)
{
	static Touch finger;
	switch (ev->type)
	{
		case SDL_FINGERDOWN:
			finger.init(
				ev->tfinger.x,
				ev->tfinger.y);
			break;
		case SDL_FINGERMOTION:
		{
			finger.move(
				ev->tfinger.x,
				ev->tfinger.y);
			auto swipe = finger.reg_swipe();
			if (swipe != -1)
			{
				next_dir = swipe;
				if (!run)
				{
					run = true;
				}
				if (over)
				{
					init();
				}
			}
			break;
		}
		case SDL_FINGERUP:
			finger.move(
				ev->tfinger.x,
				ev->tfinger.y);
			if (finger.reg_touch())
			{
				if (!run)
				{
					run = true;
				}
				if (over)
				{
					init();
				}
			}
			break;
	}
}