#include "Menu.h"
SDL_Color WHITE = {255, 255, 255};
Menu::Menu(Game* g, Renderer* r): game(g), renderer(r){}

void Menu::drawButton(SDL_Rect* rect, const char* text, char option)
{
   	TTF_Init();
  	SDL_Renderer *sdl_r = renderer->sdl_renderer;
	SDL_SetRenderDrawColor(sdl_r, 0x80, 0x80, 0x80, 0xFF);
    
    int oldW = rect->w;
    int oldX = rect->x;

    if( text )
    {
        SDL_Surface* textSurface = getTextSurface(text, "ShareTechMono-Regular", 50);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(sdl_r, textSurface);
        SDL_Rect surfRect;
        SDL_GetClipRect(textSurface, &surfRect);

        if( surfRect.w+20 > rect->w )
        {
            rect->x = rect->x - (surfRect.w - rect->w)/2;
            rect->w = surfRect.w + 20;
        }
        surfRect.x = rect->x - (surfRect.w - rect->w)/2;
        surfRect.y = rect->y - (surfRect.h - rect->h)/2;
        
        SDL_RenderFillRect(sdl_r, rect);

        SDL_RenderCopy(sdl_r, textTexture, NULL, &surfRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
    else
    {
        SDL_RenderFillRect(sdl_r, rect);
    }
    

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if( rect->x < mouseX && rect->x+rect->w > mouseX &&
        rect->y < mouseY && rect->y+rect->h > mouseY )
    {
      	SDL_Event e;
        if( SDL_PollEvent(&e) == SDL_MOUSEBUTTONDOWN ) {
          switch(option) {
            case 'E':
              game->setLevelEasy();
              break;
            case 'M':
              game->setLevelMedium();
              break;
            case 'H':
              game->setLevelHard();
              break;
            case 'S':
              startGame();
              break;
          }
        }
        SDL_SetRenderDrawColor(sdl_r, 0x00, 0x00, 0x00, 0x30);
        SDL_RenderFillRect(sdl_r, rect);
    }

    SDL_SetRenderDrawColor(sdl_r, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawRect(sdl_r, rect);

    rect->w = oldW;
    rect->x = oldX;
}

void Menu::drawMenu() {
    SDL_Rect rect;
    rect.x = (640-200)/2;
    rect.y = 100;
    rect.h = 120;
    rect.w = 240;

    drawButton(&rect, "Easy", 'E');
    rect.y += rect.h + 50;
    drawButton(&rect, "Medium", 'M');
    rect.y += rect.h + 50;
    drawButton(&rect, "Hard", 'H');
    rect.y += rect.h + 50;
    drawButton(&rect, "Start", 'S');
}

SDL_Surface* Menu::getTextSurface(const char* text, const char* font, int size){
	 TTF_Font* ttf_font = TTF_OpenFont(font, size);
    if( ttf_font == NULL )
    {
        char msg[100] = "Could not open font: ";
        strcat(msg, font);
        error(msg);
    }
    SDL_Surface* surface = TTF_RenderText_Solid(ttf_font, text, WHITE);
    TTF_CloseFont(ttf_font);
    return surface;

}
void Menu::startGame()
{
	SDL_RenderClear(renderer->sdl_renderer);
  	game->startGame();
}

void Menu::error(const char* message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message, renderer->sdl_window);
    teardown();
    exit(1);
}

void Menu::teardown()
{
    SDL_DestroyRenderer(renderer->sdl_renderer);
    SDL_DestroyWindow(renderer->sdl_window);
    SDL_Quit();
}