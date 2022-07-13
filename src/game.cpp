#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
      all_food = { &food, &food_2, &food_3, &food_4 };
      for(int i = 0; i < all_food.size(); i++){
      	PlaceFood(i);
      }
}


void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  while (running) {
    if(started){
      
      frame_start = SDL_GetTicks();

      // Input, Update, Render - the main game loop.
      controller.HandleInput(running, snake);
      Update();

      renderer.Render(snake, all_food);

      frame_end = SDL_GetTicks();

      // Keep track of how long each loop through the input/update/render cycle
      // takes.
      frame_count++;
      frame_duration = frame_end - frame_start;

      // After every second, update the window title.
      if (frame_end - title_timestamp >= 1000) {
        renderer.UpdateWindowTitle(score, frame_count);
        frame_count = 0;
        title_timestamp = frame_end;
      }

      // If the time for this frame is too small (i.e. frame_duration is
      // smaller than the target ms_per_frame), delay the loop to
      // achieve the correct frame rate.
      if (frame_duration < target_frame_duration) {
        SDL_Delay(target_frame_duration - frame_duration);
      }
    }
  }
  SDL_DestroyRenderer(renderer.sdl_renderer);
  SDL_DestroyWindow(renderer.sdl_window);
  SDL_Quit();
  return;
}

void Game::PlaceFood(int f) {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      //Debugg food message std::cout << "Placing Food " << f+1 << " at: " << x << ", " << y << std::endl;
      all_food[f]->x = x;
      all_food[f]->y = y;
      //Debugg food message std::cout << "Food is at: " << all_food[f]->x << ", " << all_food[f]->y << std::endl;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;
  
  snake.Update();

  // Check if there's food over here
  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
  MonitorFood(new_x, new_y);
}

void Game::MonitorFood(int new_x, int new_y) {
  for(int i = 0; i < all_food.size(); i++){
    if(all_food[i]->x == new_x && all_food[i]->y == new_y){
      	score++;
      	PlaceFood(i);
    	snake.GrowBody();
      	std::cout << "Speed: " << snake.speed << " Add " << snakeSpeed << std::endl;
      	snake.speed += snakeSpeed;
      	std::cout << "New Speed " << snake.speed << std::endl;
		return;
    }
  }
}

void Game::setLevelEasy() {
  	snakeSpeed = 0.01;
  	all_food =  { &food };
}
void Game::setLevelMedium() {
	snakeSpeed = 0.02;
  	all_food =  { &food, &food_2, &food_3 };
}
void Game::setLevelHard() {
	snakeSpeed = 0.03;
  	all_food =  { &food, &food_2, &food_3, &food_4 };
} 

void Game::startGame() {
	started = true;
}
int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }