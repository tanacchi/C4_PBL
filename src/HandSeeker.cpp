#include "../include/HandSeeker.hpp"

HandSeeker::HandSeeker(unsigned short max_depth)
  : myplate_(),
    sub_ {0},
    mystone_{Stone::Space},
    max_depth_ {max_depth},
    mydepth_ {0}
{
  for (unsigned char i = 0; i < PLATE_WIDTH; i++) hand_list_[i].position_ = i;
}

HandSeeker::HandSeeker(const HandSeeker& src)
  : myplate_ {src.myplate_},
    sub_ {0},
    mystone_ {src.mystone_},
    max_depth_ {src.max_depth_},
    mydepth_ {src.mydepth_}
{
  for (unsigned char i = 0; i < PLATE_WIDTH; i++) hand_list_[i].position_ = i;
}

short HandSeeker::get_conclusion(VirtualPlate game_plate)
{
  myplate_ = game_plate;
  mystone_ = myplate_.get_active_stone();
  get_list_score();
  for (unsigned char i = 0; i < PLATE_WIDTH; i++) {
    unsigned char maximum = i;
    for (unsigned char j = i; j < PLATE_WIDTH; j++)
      if (hand_list_[j].score_ > hand_list_[maximum].score_) maximum = j;
    HandList buff = hand_list_[i];
    hand_list_[i] = hand_list_[maximum];
    hand_list_[maximum] = buff;
  }
  unsigned char best_pos = 0;
  while (!hand_list_[best_pos].score_) best_pos++;
  for (unsigned char i = 0; i < PLATE_WIDTH; i++)
    std::cout << hand_list_[i].position_ << ' ' << hand_list_[i].score_ << std::endl;
  std::cout << "best position is " << hand_list_[best_pos].position_ << std::endl;
  return hand_list_[best_pos].position_;
}

float HandSeeker::get_list_score()
{
  if ((max_depth_ - mydepth_) < 0) return evaluate_plate();
  for (unsigned char i = 0; i < PLATE_WIDTH; i++) {
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
  for (unsigned char i = 0; i < PLATE_WIDTH; i++) sum += hand_list_[i].score_;
  return sum/PLATE_WIDTH;
}

float HandSeeker::evaluate_plate()
{
  if (myplate_.get_active_stone() != mystone_) myplate_.switch_active_stone();
  float score = 0.1;
  for (unsigned char i = 0; i < 4; i++)
    for (unsigned char y = 0; y < PLATE_HEIGHT; y++)
      for (unsigned char x = 0; x < PLATE_WIDTH; x++) {
        short length_buff = 0;
        if ((length_buff = myplate_.get_length(x, y, dx[i], dy[i])) > 3) score += length_buff*300;
        myplate_.switch_active_stone();
        if ((length_buff = myplate_.get_length(x, y, dx[i], dy[i])) > 3) score -= length_buff*500;
        myplate_.switch_active_stone();
      }
  return score / mydepth_+1/10;
}
