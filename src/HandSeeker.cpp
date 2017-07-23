#include "../include/HandSeeker.hpp"

HandSeeker::HandSeeker(int depth)
  : myplate_(),
    sub_ {0},
    depth_ {depth}
{
  for (int i = 0; i < PLATE_WIDTH; i++) hand_list_[i].position_ = i;
}

HandSeeker::HandSeeker(const HandSeeker& src)
  : myplate_ {src.myplate_},
    sub_ {0},
    depth_ {src.depth_}
{
  for (int i = 0; i < PLATE_WIDTH; i++) hand_list_[i].position_ = i;
}

int HandSeeker::operator()(VirtualPlate game_plate)
{
  myplate_ = game_plate;
  get_list_score();
  for (int i = 0; i < PLATE_WIDTH; i++) {
    int maximum = i;
    for (int j = i; j < PLATE_WIDTH; j++)
      if (hand_list_[j].score_ > hand_list_[maximum].score_) maximum = j;
    HandList buff = hand_list_[i];
    hand_list_[i] = hand_list_[maximum];
    hand_list_[maximum] = buff;
  }
  int best_pos = 0;
  while (!hand_list_[best_pos].score_) best_pos++;
  return hand_list_[best_pos].position_;
}

float HandSeeker::get_list_score()
{
  if (depth_ < 0) return evaluate_plate();
  for (int i = 0; i < PLATE_WIDTH; i++) {
    if (!myplate_.is_valid_hand(i)) continue;
    sub_ = new HandSeeker(*this);
    sub_->depth_--;
    sub_->myplate_.insert(i);
    sub_->myplate_.switch_active_stone();
    hand_list_[i].score_ = sub_->get_list_score();
    delete sub_;
  }
  float sum = 0;
  for (int i = 0; i < PLATE_WIDTH; i++) sum += hand_list_[i].score_;
  return sum/PLATE_WIDTH;
}

float HandSeeker::evaluate_plate()
{
  float score = 0.1;
  for (short i = 0; i < 4; i++)
    for (short y = 0; y < PLATE_HEIGHT; y++)
      for (short x = 0; x < PLATE_WIDTH; x++) {
        int length_buff = 0;
        if ((length_buff = myplate_.get_length(x, y, dx[i], dy[i])) > 3) score += length_buff*300;
        myplate_.switch_active_stone();
        if ((length_buff = myplate_.get_length(x, y, dx[i], dy[i])) > 3) score -= length_buff*500;
        myplate_.switch_active_stone();
      }
  return score / depth_+1/10;
}
