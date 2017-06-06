#include "../include/HandSeeker.h"

HandList::HandList()
  : position { 0 },
    score { 0.0 }
{
}

void HandList::set_position(int x) {
  position = x;
}

double HandList::get_score() const {
  return score;
}

HandSeeker::HandSeeker(VirtualPlate game_plate)
  : myplate { game_plate },
    sub { 0 },
    dist_x { 0 }
{
}

HandSeeker::HandSeeker(const HandSeeker& src)
  : myplate { src.myplate },
    sub { src.sub },
    dist_x { src.dist_x }
{
}

const HandSeeker& HandSeeker::operator=(const HandSeeker& src) {
  myplate = src.myplate;
  sub = src.sub;
  dist_x = src.dist_x;
  return *this;
}

int HandSeeker::get_conclusion() const {
  return dist_x;
}

void HandSeeker::record_list() {             // REFACTOR: どう考えても二度手間
  int branch = 0;
  for (int i = 0; i < PLATE_WIDTH; i++)
    if (myplate.is_valid_hand(i)) branch++;
  hand_list = new HandList[branch]; 
  for (int i = 0; i < PLATE_WIDTH; i++)
    if (myplate.is_valid_hand(i)) hand_list[i].set_position(i); // [] のオーバーロードでうまいこと行くかもしれない
  std::cout << "branch = " << branch << std::endl;
}
