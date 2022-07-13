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
  	void resetSelected(int i, TTF_Font *font);
  	SDL_Color textColor = { 45, 207, 255, 0xFF };
  	SDL_Color textColorActivated = { 0x00, 0xFF, 0x00, 0xFF};
    SDL_Color textBackgroundColor = { 0x00, 0x00, 0x00, 0xFF };
  	
  	std::vector<bool> selected = {0,0,0,0};
  	std::vector<SDL_Texture*> texts = {NULL, NULL, NULL, NULL};
   	SDL_Rect textRect;
  	SDL_Rect textRect_2;
    SDL_Rect textRect_3;
    SDL_Rect textRect_4;
  
  	std::vector<SDL_Rect> textRects = { textRect, textRect_2, textRect_3, textRect_4 };
  	std::vector<const char*> menuItems = {"Easy", "Medium", "Hard", "Start"};
};

#endif