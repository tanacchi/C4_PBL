#include <stdlib.h>
#include <time.h>
#include "VirtualPlate.h"

enum class Task {
  Init,
  Show,
  Set,
  Insert,
  Judge,
  Ed
};

int main() {

  srand((unsigned)time(NULL));
  
  VirtualPlate plate;
  show(plate);

  while (plate.can_continue()) { 
      int input_x;
    do {
      // std::cout << "Input hand !!         >>>>>>> " << std::flush;
      // std::cin >> input_x;
      input_x = rand()%7;
    } while (!plate.is_valid_hand(input_x));
    plate.insert(input_x);
    show(plate);
    if (plate.is_game_finish()) break;
    plate.switch_active_stone();
  }

  return 0;
}

