#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "input.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  
  void setLevelEasy();
  void setLevelMedium();
  void setLevelHard();
  void startGame();
  bool started = false;
 private:
  Snake snake;
  SDL_Point food;
  SDL_Point food_2;
  SDL_Point food_3;
  SDL_Point food_4;
  std::vector <SDL_Point*> all_food;
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  int fruit{1};
  float snakeSpeed{0.02};
  int score{0};
  void PlaceFood(int f);
  void Update();

  void MonitorFood(int new_x, int new_y);
};

#endif