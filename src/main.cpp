#include <iostream>
#include <string>
#include <fstream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "Menu.h"
#include "Player.h"

bool writeToScoreBoard(PlayerObj p_1);

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
  
 
  
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Enter Name: ";
  std::cin >> name;
  std::cin.ignore();
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  PlayerObj user {
	name,
    game.GetScore(),
    game.GetSize()
  };
  
  std::cout << "Player" << user.name << " " << user.score << " " << user.snakeSize << std::endl;
  bool fileSaved = writeToScoreBoard(user);
  if(fileSaved)
    std::cout << "Player Saved to ScoreBoard\n";
  else
    std::cout << "Error Saving Player to ScoreBoard\n";
  return 0;
}

bool writeToScoreBoard(PlayerObj p_1)
{
	std::ofstream fs;
	std::string fileName = "PlayerNames.txt";
  	fs.open(fileName, std::ios::out);
  	
    if (fs.is_open() && !fs.bad())
    {
      std::cout << "Writing to file\n";
      fs << "Name: " << p_1.name << "\tScore: " << p_1.score << "\tSnakeSize: " << p_1.snakeSize << std::endl;
      fs.close();
      return true;
    } 
    return false;

}
//Figure out issue with name saving