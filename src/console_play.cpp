#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <chrono>

#include "../include/VirtualPlate.hpp"
#include "../include/HandSeeker.hpp"

enum class Task {
  Init,
  Show,
  Set,
  Insert,
  Judge,
  Ed
};

char to_char(Stone stone) {
  return
    (stone == Stone::Red)  ? 'O':
    (stone == Stone::Blue) ? 'X':
    ' ';
}

void show(VirtualPlate game_plate) {
  std::cout << "-----------------" << std::endl;
  std::cout << "| ";
  for (int i = 0; i < PLATE_WIDTH; i++) std::cout << i << ' ';
  std::cout <<"|\n";
  for (int y = 0; y < PLATE_HEIGHT; std::cout.put('\n'), y++) {
    std::cout << "| ";
    for (int x = 0; x < PLATE_WIDTH; std::cout.put(' '), x++)
      std::cout.put(to_char(game_plate.plate_[y][x]));
    std::cout << "|";
  }
  std::cout << "-----------------" << std::endl;
}

int main() {

  srand((unsigned)time(NULL));
  
  VirtualPlate plate;
  show(plate);
  int turn = 0;
  while (plate.can_continue()) {
    turn++;
    int input_x;
    HandSeeker* seeker = new HandSeeker();
    float buff = (*seeker)(plate);
    std::cout << seeker->get_list_score() << std::endl;
    delete seeker;
    do {
      if (turn%2) {
        std::cout << "Input hand !!/n> " << std::flush;
        std::cin >> input_x;
        input_x;
        std::cout.put('\n');
      }
      else {
        input_x = rand()%6;
      }
    } while (!plate.is_valid_hand(input_x));
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    plate.insert(input_x);
    show(plate);
    if (plate.is_game_finish()) break;
    plate.switch_active_stone();
  }
  return 0;
}

