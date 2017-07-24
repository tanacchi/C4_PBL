#include <iostream>
#include "include/HandSeeker.hpp"


int main()
{
  VirtualPlate plate;
  HandSeeker* seeker;
  int select_x;
  int turn = 0;

  
  while (plate.can_continue()) {
    turn++;
    do {
      //  if (turn%2){
        std::cin >> select_x;
        // }
      // else {
      //   seeker = new HandSeeker(2);
      //   select_x = seeker->get_conclusion(plate);
      //   delete seeker;
      // }
    } while (!plate.is_valid_hand(select_x));


  }
  
  return 0;
}
