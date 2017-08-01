#include <iostream>
#include "include/HandSeeker.hpp"

const char* to_char(Stone stone)
{
  return
    (stone == Stone::Red) ? "●":
    (stone == Stone::Blue) ? "◯":
    " ";
}

void show(const VirtualPlate& src)
{
  std::cout << "=====================" << std::endl;
  for (int y = 0; y < PLATE_HEIGHT; std::cout << "\n", y++)
    for (int x = 0; x < PLATE_WIDTH; std::cout << "　", x++)
      std::cout << to_char(src.plate_[y][x]);
  std::cout << "=====================\n\n" << std::endl;
}

int main()
{

  VirtualPlate plate;
  HandSeeker* seeker;
  int select_x;
  int turn = 0;

  show(plate);
  
  while (plate.can_continue()) {
    turn++;
    do {
      if (turn%2){
        std::cin >> select_x;
      }
      else {
        seeker = new HandSeeker(5);
        select_x = seeker->get_conclusion(plate);
        delete seeker;
      }
    } while (!plate.is_valid_hand(select_x));
    plate.insert(select_x);
    show(plate);
    if (plate.is_game_finish()) { std::cout << "FINISH!!" << std::endl; return 0;}
    plate.switch_active_stone();
  }
  
  return 0;
}
