#include "../include/HandSeeker.hpp"

HandList::HandList()
  : is_active_ { false },
    score_ { 0.0 }
{
}
void HandList::activate() {
  is_active_ = true;
}
bool HandList::is_active() const {
  return is_active_;
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
    sub_ {0},
    mystone_{Stone::Space},
    max_depth_ {3},
    mydepth_ {0}
{
}
HandSeeker::HandSeeker(const HandSeeker& src)
  : myplate_ {src.myplate_},
    hand_list_(),
    sub_ {0},
    mystone_ {src.mystone_},
    max_depth_ {src.max_depth_},
    mydepth_ {src.mydepth_}
{
}
int HandSeeker::operator()(VirtualPlate game_plate) {
  myplate_ = game_plate;
  mystone_ = myplate_.get_active_stone();
  return 0;
}
float HandSeeker::get_list_score() {
  if ((max_depth_ - mydepth_) < 0) return evaluate_plate();
  for (int i = 0; i < PLATE_WIDTH; i++)
    if (myplate_.is_valid_hand(i)) hand_list_[i].activate();
  for (int i = 0; i < PLATE_WIDTH; i++) {
    if (!hand_list_[i].is_active()) continue;
    sub_ = new HandSeeker(*this);
    sub_->mydepth_++;
    sub_->myplate_.insert(i);
    sub_->myplate_.switch_active_stone();
    hand_list_[i].set_score(sub_->get_list_score());
    delete sub_;
  }
  float sum = 0;
  for (int i = 0; i < PLATE_WIDTH; i++) sum += hand_list_[i].get_score();
  return sum;
}

float HandSeeker::evaluate_plate() {
  return 3.00;
}
