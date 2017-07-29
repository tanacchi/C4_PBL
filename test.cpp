#include <iostream>
#include "include/HandSeeker.hpp"


int main()
{

  std::cout << sizeof(VirtualPlate) + sizeof(HandSeeker)*5 << std::endl;

  // VirtualPlate plate;
  // HandSeeker* seeker;
  // int select_x;
  // int turn = 0;

  // plate.show();
  
  // while (plate.can_continue()) {
  //   turn++;
  //   do {
  //     if (turn%2){
  //       std::cin >> select_x;
  //     }
  //     else {
  //       seeker = new HandSeeker(5);
  //       select_x = seeker->get_conclusion(plate);
  //       delete seeker;
  //     }
  //   } while (!plate.is_valid_hand(select_x));
  //   plate.insert(select_x);
  //   plate.show();
  //   if (plate.is_game_finish()) { std::cout << "FINISH!!" << std::endl; return 0;}
  //   plate.switch_active_stone();

  // }
  
  return 0;
}
