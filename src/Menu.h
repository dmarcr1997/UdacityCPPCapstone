#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "game.h"
#include "renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Menu {
  public:
  	Menu(Game* game, Renderer* renderer);
  	void drawMenu();
  private:
  	Game *game;
  	Renderer *renderer;
  	void drawButton(SDL_Rect* rect, const char* text, char option);
    void startGame();
  	void error(const char* message);
  	void teardown();
  	SDL_Surface* getTextSurface(const char* text, const char* font, int size);
};

#endif