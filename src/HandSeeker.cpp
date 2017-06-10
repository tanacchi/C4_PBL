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

void HandList::set_score(double s) {
  score_ = s;
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
    max_depth_ { 3 },
    mydepth_ { 0 },
    branch_ { 0 }
{
}

HandSeeker::HandSeeker(const HandSeeker& src)
  : myplate_ { src.myplate_ },
    // sub_ { src.sub_ },
    max_depth_ { src.max_depth_ },
    mydepth_ { src.mydepth_ },
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
  mydepth_ = src.mydepth_;
  return *this;
}

void HandSeeker::record_list() {             // REFACTOR: どう考えても二度手間
  for (int i = 0; i < PLATE_WIDTH; i++)
    if (myplate_.is_valid_hand(i)) branch_++;
  hand_list_ = new HandList[branch_]; 
  for (int i = 0; i < PLATE_WIDTH; i++)
    if (myplate_.is_valid_hand(i)) hand_list_[i].set_position(i); // [] のオーバーロードでうまいこと行くかもしれない
}

int n;

double HandSeeker::set_list_score() {
  double score;
  record_list();
  if (!(branch_ && max_depth_-mydepth_ > 0)) return evaluate_hand();
  for (int i = 0; i < branch_ && n++ < 10000; i++) {
    sub_ = new HandSeeker(*this);
    sub_->myplate_.insert(hand_list_[i].get_position());
    sub_->myplate_.switch_active_stone();
    score += sub_->set_list_score();
    delete sub_;
  }
  return score;
}

int HandSeeker::seek() {
  std::cout << "Done " << set_list_score() << std::endl;
  return 0;
}

int HandSeeker::evaluate_hand() {
  int max = 0;
  int score_buff;
  for (int i = 0; i < 4; i++)
    for (int y = 0; y < PLATE_HEIGHT; y++)
      for (int x = 0; x < PLATE_WIDTH; x++) {
        score_buff = myplate_.get_length(x, y, dx[i], dy[i]);
        if (score_buff > max) max = score_buff;
      }
  return max;
}
