#include "../include/HandSeeker.hpp"

HandList::HandList()
  : is_active_pos_ { false },
    score_ { 0.0 }
{
}
void HandList::activate() {
  is_active_pos_ = true;
}
void HandList::set_score(float score) {
  score_ = score;
}
float HandList::get_score() const {
  return score_;
}

HandSeeker::HandSeeker()
  : myplate_(),
    hand_list_(),
    sub_ {0}
{
}
const HandSeeker& HandSeeker::operator=() {
}
int HandSeeker::operator()(VirtualPlate game_plate) {
}
void set_hand_list() {
  for (int i = 0; i < PLATE_WIDTH; i++)
    if (myplate_.is_valid_hand(i)) hand_list[i].activate();
}
