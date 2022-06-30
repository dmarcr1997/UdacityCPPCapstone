#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Math.hpp>

Object::Object(Vector2f p_pos, SDL_Texture* p_tex) :pos(p_pos), texture(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}

SDL_Texture* Object::getTex()
{
	return texture;
}

SDL_Rect Object::getCurrentFrame()
{
	return currentFrame;
}
