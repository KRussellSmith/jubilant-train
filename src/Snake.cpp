#include "Snake.hpp"
#include "Dir.hpp"
#include <SDL2/SDL.h>

SNode::SNode(int x, int y)
{
	this->x = x;
	this->y = y;
	this->next = NULL;
}
SNode::~SNode()
{
	delete this->next;
}

Snake::Snake()
{
	head = NULL;
}
void Snake::init(int x, int y)
{
	if (head) delete head;

	this->head = new SNode(x, y);
	this->dir = Dir::RIGHT;
	len = 1;
}
void Snake::grow()
{
	auto node = new SNode(
		head->x + DIR[dir].x,
		head->y + DIR[dir].y);
	node->next = head;
	head = node;
	++len;
}
void Snake::move()
{
	auto curr   = head;
	auto prev_x = curr->x;
	auto prev_y = curr->y;
	curr = curr->next;
	while (curr != NULL)
	{
		auto temp_x = curr->x;
		auto temp_y = curr->y;
		curr->x = prev_x;
		curr->y = prev_y;
		prev_x = temp_x;
		prev_y = temp_y;
		curr = curr->next;
	}
	head->x += DIR[dir].x;
	head->y += DIR[dir].y;
}
void Snake::turn(int new_dir)
{
	if (len > 1 && new_dir == Dir::inv(dir))
	{
		return;
	}
	dir = new_dir;
}
void Snake::draw(SDL_Renderer *renderer, SDL_Rect *bounds, int size)
{
	static SDL_Rect rect;
	rect.w = size;
	rect.h = size;
	auto curr = head;
	SDL_SetRenderDrawColor(
		renderer,
		0x76, 0xB5, 0xE3, 0xFF);
	while (curr)
	{
		rect.x = bounds->x + curr->x * rect.w;
		rect.y = bounds->y + curr->y * rect.h;
		SDL_RenderFillRect(
			renderer, &rect);
		curr = curr->next;
	}
}
bool Snake::bad_move(int size)
{
	for (auto node = head->next; node; node = node->next)
	{
		if (head->x == node->x && head->y == node->y)
		{
			return true;
		}
	}
	if (
		head->x < 0 || head->x >= size ||
		head->y < 0 || head->y >= size)
	{
		return true;
	}
	return false;
}
Snake::~Snake()
{
	delete head;
}