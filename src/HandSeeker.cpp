#include "../include/HandSeeker.h"

HandList::HandList()
  : position_ { 0 },
    score_ { 0.0 }
{
}

// HandList::~HandList() {
//   std::cout << "Bye!" << std::endl;
// }

void HandList::set_position(int x) {
  position_ = x;
}

double HandList::get_score() const {
  return score_;
}

int HandList::get_position() const {
  return position_;
}

HandSeeker::HandSeeker()
  : myplate_(),
    sub_ { 0 },
    branch_ { 0 }
{
}

HandSeeker::HandSeeker(const HandSeeker& src)
  : myplate_ { src.myplate_ },
    sub_ { src.sub_ },
    branch_ { 0 }
{
}

// HandSeeker::~HandSeeker() {
// }

int HandSeeker::operator()(const VirtualPlate& game_plate) {
  myplate_ = game_plate;
  return seek();
}

const HandSeeker& HandSeeker::operator=(const HandSeeker& src) {
  myplate_ = src.myplate_;
  sub_ = src.sub_;
  return *this;
}

void HandSeeker::record_list() {             // REFACTOR: どう考えても二度手間
  for (int i = 0; i < PLATE_WIDTH; i++)
    if (myplate_.is_valid_hand(i)) branch_++;
  hand_list_ = new HandList[branch_]; 
  for (int i = 0; i < PLATE_WIDTH; i++)
    if (myplate_.is_valid_hand(i)) hand_list_[i].set_position(i); // [] のオーバーロードでうまいこと行くかもしれない
}

long n;

void HandSeeker::set_sub() {
  sub_ = new HandSeeker[branch_];
  for (int i = 0; i < branch_ && n++ < 10000; i++) {
    sub_[i] = *this;
    sub_[i].myplate_.insert(hand_list_[i].get_position());
    sub_[i].myplate_.switch_active_stone();
    sub_[i].record_list();
    if (sub_[i].branch_) sub_[i].set_sub();
  }
}

int HandSeeker::seek() {
  record_list();
  set_sub();
  std::cout << "Done " << n << std::endl;
  return 0;
}
