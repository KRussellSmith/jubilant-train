#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SDL2/SDL.h>

class SNode
{
public:
	int x;
	int y;
	SNode *next;
	SNode(int x, int y);
	~SNode();
};

class Snake
{
public:
	SNode *head;
	int   dir;
	int   len;
	
	Snake();
	
	void init(int x, int y);
	void grow();
	void move();
	void turn(int new_dir);
	void draw(SDL_Renderer *renderer, SDL_Rect *bounds, int size);
	bool bad_move(int size);
	
	~Snake();
};
#endif