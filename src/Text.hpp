#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace Align
{
	enum
	{
		LEFT   = 1 << 0,
		RIGHT  = 1 << 1,
		TOP    = 1 << 2,
		BOTTOM = 1 << 3,
		CENTER = 1 << 4
	};
}
class Text
{
private:
	int align;
public:
	SDL_Texture *tex;
	SDL_Rect     rect;
	TTF_Font    *font;
	SDL_Color    color;
	
	Text();
	void set_align(int align);
	void set_font(const char *font_name, int size, SDL_Color color);
	void set_text(SDL_Renderer *renderer, const char *message, int x, int y);
	void render(SDL_Renderer *renderer);
	
	~Text();
};
#endif