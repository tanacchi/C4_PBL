#include "../include/HandSeeker.h"

HandSeeker::HandSeeker()
  : myplate_(),
    sub_ { 0 },
    max_depth_ { 1 },
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

HandSeeker::~HandSeeker() {
  if (hand_list_) delete[] hand_list_;
}

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
  std::cout << "AHI !! " << std::flush;
  hand_list_ = new int[branch_];
  std::cout << "AHI !! " << std::endl;
  for (int i = 0; i < PLATE_WIDTH; i++)
    if (myplate_.is_valid_hand(i)) hand_list_[i] = i; // [] のオーバーロードでうまいこと行くかもしれない
}

int n = 0;

double HandSeeker::set_list_score() {
  double score;
  record_list();
  if (!(branch_ && max_depth_-mydepth_ > 0)) return evaluate_hand();
  for (int i = 0; i < branch_; i++) {
    std::cout << "Hello " << ++n << ' ' << std::flush;
    sub_ = new HandSeeker(*this);
    sub_->mydepth_++;
    sub_->myplate_.insert(hand_list_[i]);
    sub_->myplate_.switch_active_stone();
    std::cout << "How are you ? " << n << ' ' << std::flush;
    score += sub_->set_list_score();
    delete sub_;
    std::cout << "Bye " << n << ' ' << std::endl;
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
  std::cout << "sub_ = " << sub_ << std::endl;
  return max;
}
