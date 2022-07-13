#include "Menu.h"

Menu::Menu(Game* g, Renderer* r): game(g), renderer(r){}

bool Menu::drawMenu() {
   	TTF_Init();

    SDL_Rect squareRect;
    // Square dimensions: Half of the min(SCREEN_WIDTH, SCREEN_HEIGHT)
    squareRect.w = MIN(SCREEN_WIDTH, SCREEN_HEIGHT) / 2;
    squareRect.h = MIN(SCREEN_WIDTH, SCREEN_HEIGHT) / 2;

    // Square position: In the middle of the screen
    squareRect.x = SCREEN_WIDTH / 2 - squareRect.w / 2;
    squareRect.y = SCREEN_HEIGHT / 2 - squareRect.h / 2;
  	TTF_Font *font = TTF_OpenFont(FONT_PATH, 60);
    if(!font) {
      printf("Unable to load font: '%s'!\n"
             "SDL2_ttf Error: %s\n", FONT_PATH, TTF_GetError());
 	  return true;
    }
  
    SDL_Surface *textSurface = TTF_RenderText_Shaded(font, menuItems[0], textColor, textBackgroundColor);
	SDL_Surface *textSurface_2 = TTF_RenderText_Shaded(font, menuItems[1], textColor, textBackgroundColor);
	SDL_Surface *textSurface_3 = TTF_RenderText_Shaded(font, menuItems[2], textColor, textBackgroundColor);
	SDL_Surface *textSurface_4 = TTF_RenderText_Shaded(font, menuItems[3], textColor, textBackgroundColor);

  	std::vector<SDL_Surface*> surfaces = { textSurface, textSurface_2, textSurface_3, textSurface_4 };
    if(!textSurface || !textSurface_2 || !textSurface_3 || !textSurface_4 ) {
      printf("Unable to render text surface!\n"
             "SDL2_ttf Error: %s\n", TTF_GetError());
      return true;
    } else {
      // Create texture from surface pixels
      for(int i = 0; i < texts.size(); i++){
        texts[i] = SDL_CreateTextureFromSurface(renderer->sdl_renderer, surfaces[i]);

        if(!texts[i]) {
          printf("Unable to create texture from rendered text!\n"
                 "SDL2 Error: %s\n", SDL_GetError());
          return true;
        }
      }
	  
       // Get text dimensions
      for(int k = 0; k < textRects.size(); k++){
        textRects[k].w = surfaces[k]->w;
        textRects[k].h = surfaces[k]->h;
        SDL_FreeSurface(surfaces[k]);
      }
    }

    textRects[0].x = ((SCREEN_WIDTH - textRects[0].w) / 2) - 80;
    textRects[0].y = squareRect.y - textRects[0].h - 10;
  	textRects[1].x = ((SCREEN_WIDTH - textRects[1].w) / 2) - 80;
    textRects[1].y = squareRect.y - textRects[1].h + 60;
  	textRects[2].x = ((SCREEN_WIDTH - textRects[2].w) / 2) - 80;
    textRects[2].y = squareRect.y - textRects[2].h + 130;
  	textRects[3].x = ((SCREEN_WIDTH - textRects[3].w) / 2) - 80;
    textRects[3].y = squareRect.y - textRects[3].h + 300;
	// Event loop exit flag
    bool quit = false;

    // Event loop
    while(!quit)
    {
      SDL_Event e;

      // Wait indefinitely for the next available event
      SDL_WaitEvent(&e);

      // User requests quit
      if(e.type == SDL_QUIT)
      {
        quit = true;
        SDL_DestroyRenderer(renderer->sdl_renderer);
        SDL_DestroyWindow(renderer->sdl_window);
        // Quit SDL2_ttf
    	TTF_Quit();

        // Quit SDL
        SDL_Quit();
        return true;
      } 
      if (e.type == SDL_MOUSEBUTTONDOWN) {
      	int mouseX, mouseY;
        SDL_GetMouseState( &mouseX, &mouseY );
		for(int j = 0; j < textRects.size(); j++){
          if(textRects[j].x < mouseX && textRects[j].x+textRects[j].w > mouseX &&
          textRects[j].y < mouseY && textRects[j].y+textRects[j].h > mouseY){
              SDL_Surface *newSurface;
              if(selected[j])
              {
                selected[j] = false;
                newSurface = TTF_RenderText_Shaded(font, menuItems[j], textColor, textBackgroundColor);
				game->setLevelEasy();
              }
              else
              {
                resetSelected(j, font);
                selected[j] = true;
                newSurface = TTF_RenderText_Shaded(font, menuItems[j], textColorActivated, textBackgroundColor);
                if(j == 1) game->setLevelMedium();
                else if(j == 2) game->setLevelHard();
                else if(j == 3) 
                {
                  startGame();
                  return false;
                }
                else game->setLevelEasy();
              }
              texts[j] = SDL_CreateTextureFromSurface(renderer->sdl_renderer, newSurface);
          } 
      	}

	  }

      // Initialize renderer color white for the background
      SDL_SetRenderDrawColor(renderer->sdl_renderer, 0x00, 0x00, 0x00, 0xFF);

      // Clear screen
      SDL_RenderClear(renderer->sdl_renderer);

      // Draw filled square
      SDL_RenderFillRect(renderer->sdl_renderer, &squareRect);

      // Draw text
      for(int m = 0; m < texts.size(); m++){
	  	SDL_RenderCopy(renderer->sdl_renderer, texts[m], NULL, &textRects[m]);    
	  }

      // Update screen
      SDL_RenderPresent(renderer->sdl_renderer);
    }
	TTF_Quit();
  	return false;
}

void Menu::startGame()
{
	SDL_RenderClear(renderer->sdl_renderer);
  	game->startGame();
}

void Menu::resetSelected(int i, TTF_Font *font)
{
	for(int n = 0; n < selected.size(); n++){
    	if(n == i) continue;
      	else {
          if(selected[n]){
        	SDL_Surface *newSurface;
          	newSurface = TTF_RenderText_Shaded(font, menuItems[n], textColor, textBackgroundColor);
            texts[n] = SDL_CreateTextureFromSurface(renderer->sdl_renderer, newSurface);
            selected[n] = false;
          }
		}
	}
}