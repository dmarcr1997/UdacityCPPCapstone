#include "Menu.h"

Menu::Menu(Game* g, Renderer* r): game(g), renderer(r){}

bool Menu::drawMenu() {
   	TTF_Init();
  	SDL_Color textColor = { 45, 207, 255, 0xFF };
  	SDL_Color textColorActivated = { 0x00, 0xFF, 0x00, 0xFF};
    SDL_Color textBackgroundColor = { 0x00, 0x00, 0x00, 0xFF };

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
    SDL_Texture *text = NULL;
  	SDL_Texture *text_2 = NULL;
    SDL_Texture *text_3 = NULL;
    SDL_Texture *text_4 = NULL;
  
    SDL_Rect textRect;
  	SDL_Rect textRect_2;
    SDL_Rect textRect_3;
    SDL_Rect textRect_4;
  

    SDL_Surface *textSurface = TTF_RenderText_Shaded(font, "Easy", textColor, textBackgroundColor);
	SDL_Surface *textSurface_2 = TTF_RenderText_Shaded(font, "Medium", textColor, textBackgroundColor);
	SDL_Surface *textSurface_3 = TTF_RenderText_Shaded(font, "Hard", textColor, textBackgroundColor);
	SDL_Surface *textSurface_4 = TTF_RenderText_Shaded(font, "Start", textColor, textBackgroundColor);
  
    if(!textSurface) {
      printf("Unable to render text surface!\n"
             "SDL2_ttf Error: %s\n", TTF_GetError());
    } else {
      // Create texture from surface pixels
      text = SDL_CreateTextureFromSurface(renderer->sdl_renderer, textSurface);
      text_2 = SDL_CreateTextureFromSurface(renderer->sdl_renderer, textSurface_2);
      text_3 = SDL_CreateTextureFromSurface(renderer->sdl_renderer, textSurface_3);
      text_4 = SDL_CreateTextureFromSurface(renderer->sdl_renderer, textSurface_4);
      
      if(!text || !text_2 || !text_3 || !text_4) {
        printf("Unable to create texture from rendered text!\n"
               "SDL2 Error: %s\n", SDL_GetError());
        return true;
      }

      // Get text dimensions
      textRect.w = textSurface->w;
      textRect.h = textSurface->h;
	  
      textRect_2.w = textSurface_2->w;
      textRect_2.h = textSurface_2->h;
      
      textRect_3.w = textSurface_3->w;
      textRect_3.h = textSurface_3->h;
      
      textRect_4.w = textSurface_4->w;
      textRect_4.h = textSurface_4->h;
      
      SDL_FreeSurface(textSurface);
      SDL_FreeSurface(textSurface_2);
      SDL_FreeSurface(textSurface_3);
      SDL_FreeSurface(textSurface_4);
    }

    textRect.x = ((SCREEN_WIDTH - textRect.w) / 2) - 80;
    textRect.y = squareRect.y - textRect.h - 10;
  	textRect_2.x = ((SCREEN_WIDTH - textRect_2.w) / 2) - 80;
    textRect_2.y = squareRect.y - textRect_2.h + 60;
  	textRect_3.x = ((SCREEN_WIDTH - textRect_3.w) / 2) - 80;
    textRect_3.y = squareRect.y - textRect_3.h + 130;
  	textRect_4.x = ((SCREEN_WIDTH - textRect_4.w) / 2) - 80;
    textRect_4.y = squareRect.y - textRect_4.h + 300;
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
		if(textRect.x < mouseX && textRect.x+textRect.w > mouseX &&
        textRect.y < mouseY && textRect.y+textRect.h > mouseY){
        	std::cout << "Easy" << std::endl;
          	SDL_Surface *newSurface = TTF_RenderText_Shaded(font, "Easy", textColorActivated, textBackgroundColor);
          	
          	text = SDL_CreateTextureFromSurface(renderer->sdl_renderer, newSurface);
          	game->setLevelEasy();
		} 
        else if(textRect_2.x < mouseX && textRect_2.x+textRect_2.w > mouseX &&
        textRect_2.y < mouseY && textRect_2.y+textRect_2.h > mouseY){
        	std::cout << "Medium" << std::endl;
          	SDL_Surface *newSurface_2 = TTF_RenderText_Shaded(font, "Medium", textColorActivated, textBackgroundColor);
          	
          	text = SDL_CreateTextureFromSurface(renderer->sdl_renderer, newSurface_2);
          	game->setLevelMedium();
		} 
        else if(textRect_3.x < mouseX && textRect_3.x+textRect_3.w > mouseX &&
        textRect_3.y < mouseY && textRect_3.y+textRect_3.h > mouseY){
        	std::cout << "Hard" << std::endl;
            SDL_Surface *newSurface_3 = TTF_RenderText_Shaded(font, "Hard", textColorActivated, textBackgroundColor);
          	
          	text = SDL_CreateTextureFromSurface(renderer->sdl_renderer, newSurface_3);
          	game->setLevelHard();
		} 
        else if(textRect_4.x < mouseX && textRect_4.x+textRect_4.w > mouseX &&
        textRect_4.y < mouseY && textRect_4.y+textRect_4.h > mouseY){
        	std::cout << "Start" << std::endl;
          	SDL_Surface *newSurface_4 = TTF_RenderText_Shaded(font, "Start", textColorActivated, textBackgroundColor);
          	
          	text = SDL_CreateTextureFromSurface(renderer->sdl_renderer, newSurface_4);
          	startGame();
          	return false;
		} 
	  }

      // Initialize renderer color white for the background
      SDL_SetRenderDrawColor(renderer->sdl_renderer, 0x00, 0x00, 0x00, 0xFF);

      // Clear screen
      SDL_RenderClear(renderer->sdl_renderer);

      // Draw filled square
      SDL_RenderFillRect(renderer->sdl_renderer, &squareRect);

      // Draw text
      SDL_RenderCopy(renderer->sdl_renderer, text, NULL, &textRect);
      SDL_RenderCopy(renderer->sdl_renderer, text_2, NULL, &textRect_2);
      SDL_RenderCopy(renderer->sdl_renderer, text_3, NULL, &textRect_3);
      SDL_RenderCopy(renderer->sdl_renderer, text_4, NULL, &textRect_4);

      // Update screen
      SDL_RenderPresent(renderer->sdl_renderer);
    }
	TTF_Quit();
  	return false;

//     drawButton(&rect, "Easy", 'E');
//     rect.y += rect.h + 50;
//     drawButton(&rect, "Medium", 'M');
//     rect.y += rect.h + 50;
//     drawButton(&rect, "Hard", 'H');
//     rect.y += rect.h + 50;
//     drawButton(&rect, "Start", 'S');
}

void Menu::startGame()
{
	SDL_RenderClear(renderer->sdl_renderer);
  	game->startGame();
}


void Menu::teardown()
{
    SDL_DestroyRenderer(renderer->sdl_renderer);
    SDL_DestroyWindow(renderer->sdl_window);
    SDL_Quit();
}