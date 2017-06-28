#include "../include/HandSeeker.hpp"
#include <iostream>

HandSeeker::HandSeeker()
  : myplate_(),
    hand_list_{0, 0, 0, 0, 0, 0},
    sub_ {0},
    mystone_{Stone::Space},
    max_depth_ {3},
    mydepth_ {0}
{
}
HandSeeker::HandSeeker(const HandSeeker& src)
  : myplate_ {src.myplate_},
    hand_list_{0, 0, 0, 0, 0, 0},
    sub_ {0},
    mystone_ {src.mystone_},
    max_depth_ {src.max_depth_},
    mydepth_ {src.mydepth_}
{
}
int HandSeeker::operator()(VirtualPlate game_plate) {
  myplate_ = game_plate;
  mystone_ = myplate_.get_active_stone();
  get_list_score();
  for (int i = 0; i < PLATE_WIDTH; i++)
    std::cout << "score [" << i << "] = " << hand_list_[i] << std::endl;;
  return 0;
}
float HandSeeker::get_list_score() {
  if ((max_depth_ - mydepth_) < 0) return evaluate_plate();
  for (int i = 0; i < PLATE_WIDTH; i++) {
    if (!myplate_.is_valid_hand(i)) continue;
    sub_ = new HandSeeker(*this);
    sub_->mydepth_++;
    sub_->myplate_.insert(i);
    sub_->myplate_.switch_active_stone();
    hand_list_[i] = sub_->get_list_score();
    delete sub_;
  }
  float sum = 0;
  for (int i = 0; i < PLATE_WIDTH; i++) sum += hand_list_[i];
  return sum;
}

float HandSeeker::evaluate_plate() {
  return 3.00;
}
