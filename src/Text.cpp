#include "Text.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

Text::Text()
{
	tex = NULL;
	align = Align::TOP | Align::LEFT;
}
void Text::set_align(int align)
{
	this->align = align;
}
void Text::set_font(const char *font_name, int size, SDL_Color color)
{
	if (font)
	{
		TTF_CloseFont(font);
	}
	font = TTF_OpenFont(font_name, size);
	this->color = color;
}
void Text::set_text(SDL_Renderer *renderer, const char *message, int x, int y)
{
	if (!font) return;
	if (tex)
		SDL_DestroyTexture(tex);
	auto surface = TTF_RenderText_Solid(font, message, color);
	tex = SDL_CreateTextureFromSurface(renderer, surface);
	
	rect.w = surface->w;
	rect.h = surface->h;
	
	if (align & Align::CENTER)
	{
		rect.x = x - rect.w * 0.5;
		rect.y = y - rect.h * 0.5;
	}
	if (align & Align::LEFT)
	{
		rect.x = x;
	}
	if (align & Align::RIGHT)
	{
		rect.x = x - rect.w;
	}
	if (align & Align::TOP)
	{
		rect.y = y;
	}
	if (align & Align::BOTTOM)
	{
		rect.y = y - rect.w;
	}
	
	SDL_FreeSurface(surface);
}
void Text::render(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, tex, NULL, &rect);
}
Text::~Text()
{
	if (font)
		TTF_CloseFont(font);
	SDL_DestroyTexture(tex);
}