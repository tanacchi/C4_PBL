#ifndef HAND_SEEKER_H_
#define HAND_SEEKER_H_

#include <iostream>
#include "../include/VirtualPlate.hpp"

class HandSeeker {
  VirtualPlate myplate_;
  bool hand_list_[PLATE_WIDTH];
  HandSeeker* sub_;
  const unsigned int max_depth_;
  unsigned int mydepth_;
  int branch_;
 public:
  HandSeeker();
  HandSeeker(const HandSeeker& src);
  ~HandSeeker();
  int operator()(const VirtualPlate& game_plate);
  const HandSeeker& operator=(const HandSeeker& src);
  const bool* init_list();
  void set_myplate(const VirtualPlate& src);
  void record_list();
  double set_list_score();
  int seek();
  int evaluate_hand();
};

#endif // HAND_SEEKER_H_
