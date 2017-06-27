#include "../include/HandSeeker.hpp"

HandSeeker::HandSeeker()
  : myplate_(),
    sub_ { 0 },
    hand_list_ { init_list() },
    max_depth_ { 5 },
    mydepth_ { 0 },
    branch_ { 0 }
{
}

HandSeeker::HandSeeker(const HandSeeker& src)
  : myplate_ { src.myplate_ },
    sub_ { src.sub_ },
    hand_list_ { init_list() },
    max_depth_ { src.max_depth_ },
    mydepth_ { src.mydepth_ },
    branch_ { 0 }
{
}

HandSeeker::~HandSeeker() {
}

int HandSeeker::operator()(const VirtualPlate& game_plate) {
  myplate_ = game_plate;
  record_list();
  return seek();
}

const HandSeeker& HandSeeker::operator=(const HandSeeker& src) {
  myplate_ = src.myplate_;
  sub_ = src.sub_;
  mydepth_ = src.mydepth_;
  return *this;
}

const bool* HandSeeker::init_list() {
  static bool array[PLATE_WIDTH];
  for (int i = 0; i < PLATE_WIDTH; i++) array[i] = false;
  return array;
}

void HandSeeker::record_list() {             // REFACTOR: どう考えても二度手間
  for (int i = 0; i < PLATE_WIDTH; i++)
    if (myplate_.is_valid_hand(i)) {
      hand_list_[i] = true;
      branch_++;
    }
}

int n = 0;

double HandSeeker::set_list_score() {
  double score;
  if (!(branch_ && max_depth_-mydepth_ > 0)) return (double)evaluate_hand();
  for (int i = 0; i < branch_; i++) {
    if (!hand_list_[i]) continue;
    sub_ = new HandSeeker(*this);
    sub_->mydepth_++;
    sub_->myplate_.insert(i);
    sub_->myplate_.switch_active_stone();
    sub_->record_list();
    score += sub_->set_list_score();
    delete sub_;
  }
  return score;
}

int HandSeeker::seek() {
  return set_list_score();
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
