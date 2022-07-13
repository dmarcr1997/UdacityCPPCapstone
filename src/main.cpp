#include <iostream>
#include <string>
#include <fstream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "Menu.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  std::string name;
  
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  Menu menu(&game, &renderer);
  bool failure = false;
  while(!game.started && !failure)
  	failure = menu.drawMenu();
  if(!failure)
  	game.Run(controller, renderer, kMsPerFrame);
  
  
  if(!failure){
    std::cout << "Game Over!\n";
    std::cout << "Enter Name: ";
    std::cin >> name;
    std::cin.ignore();

    std::cout << "Player: " << name << "\nScore:  " << game.GetScore() << "\nSize: " << game.GetSize() << std::endl;
  } else {
  	std::cout << "Game has terminated due to an error!\n";
  }
}

