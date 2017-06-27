#include "VirtualPlate.hpp"

class HandList { // Template ??
public:
  HandList();
  ~HandList() = default;
  void activate();
  void set_score(float src);
  float get_score() const;
private:
  bool is_active_pos_;
  float score_;
};

class HandSeeker {
public:
  HandSeeker();
  ~HandSeeker();
  const HandSeeker& operator=();
  int operator()(VirtualPlate game_plate);
  void set_hand_list();
private:
  VirtualPlate myplate_;
  HandList hand_list_[PLATE_WIDTH];
  HandSeeker* sub_;
};
