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
  int maximum = 0;
  for (int j = 1; j < 5; j++) if (hand_list_[j] > hand_list_[maximum]) maximum = j;
  // for (int i = 0; i < PLATE_WIDTH; i++)
  //   std::cout << "score [" << i << "] = " << hand_list_[i] << std::endl;;
  return maximum;
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
  if (myplate_.get_active_stone() != mystone_) myplate_.switch_active_stone();
  float score = 0;
  for (short i = 0; i < 4; i++)
    for (short y = 0; y < PLATE_HEIGHT; y++)
      for (short x = 0; x < PLATE_WIDTH; x++)
        if (myplate_.get_length(x, y, dx[i], dy[i]) > 2) score += 30;
  myplate_.switch_active_stone();
  for (short i = 0; i < 4; i++)
    for (short y = 0; y < PLATE_HEIGHT; y++)
      for (short x = 0; x < PLATE_WIDTH; x++)
        if (myplate_.get_length(x, y, dx[i], dy[i]) > 2) score -= 30;
  return score / mydepth_+1;
}
