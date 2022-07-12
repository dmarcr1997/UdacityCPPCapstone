#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "game.h"
#include "renderer.h"
#include <SDL.h>
#include <SDL_ttf.h>

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define FONT_PATH   "assets/TitanOne-Regular.ttf"
class Menu {
  public:
  	Menu(Game* game, Renderer* renderer);
  	bool drawMenu();
  private:
  	Game *game;
  	Renderer *renderer;
    void startGame();
  	void teardown();
};

#endif