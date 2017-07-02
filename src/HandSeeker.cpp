#include "../include/HandSeeker.hpp"
#include <iostream>

HandList::HandList()
  : position_ {0},
    score_ {0}
{
}

HandSeeker::HandSeeker()
  : myplate_(),
    sub_ {0},
    mystone_{Stone::Space},
    max_depth_ {2},
    mydepth_ {0}
{
}

HandSeeker::HandSeeker(const HandSeeker& src)
  : myplate_ {src.myplate_},
    sub_ {0},
    mystone_ {src.mystone_},
    max_depth_ {src.max_depth_},
    mydepth_ {src.mydepth_}
{
  for (int i = 0; i < PLATE_WIDTH; i++) hand_list_[i].position_ = i;
}

int HandSeeker::operator()(VirtualPlate game_plate)
{
  myplate_ = game_plate;
  mystone_ = myplate_.get_active_stone();
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
  for (int i = 0; i < PLATE_WIDTH; i++)
    std::cout << "score [" << i << "] = " << hand_list_[i].score_ << std::endl;  
  return hand_list_[best_pos].position_;
}

float HandSeeker::get_list_score()
{
  if ((max_depth_ - mydepth_) < 0) return evaluate_plate();
  for (int i = 0; i < PLATE_WIDTH; i++) {
    if (!myplate_.is_valid_hand(i)) continue;
    sub_ = new HandSeeker(*this);
    sub_->mydepth_++;
    sub_->myplate_.insert(i);
    sub_->myplate_.switch_active_stone();
    hand_list_[i].score_ = sub_->get_list_score();
    //    show(sub_->myplate_);
    delete sub_;
  }
  float sum = 0;
  for (int i = 0; i < PLATE_WIDTH; i++) sum += hand_list_[i].score_;
  return sum/PLATE_WIDTH;
}

float HandSeeker::evaluate_plate()
{
  if (myplate_.get_active_stone() != mystone_) myplate_.switch_active_stone();
  float score = 0;
  for (short i = 0; i < 4; i++)
    for (short y = 0; y < PLATE_HEIGHT; y++)
      for (short x = 0; x < PLATE_WIDTH; x++) {
        score += myplate_.get_length(x, y, dx[i], dy[i])*200;
        myplate_.switch_active_stone();
        score -= myplate_.get_length(x, y, dx[i], dy[i])*500;
        myplate_.switch_active_stone();
      }
  return score / mydepth_+1/10;
}
