#ifndef HAND_SEEKER_H_
#define HAND_SEEKER_H_

#include "../include/VirtualPlate.h"
#include <iostream>

class HandList {
  int position_;
  double score_;
 public:
  HandList();
  ~HandList() = default;
  void set_position(int x);
  double get_score() const;
  int get_position() const;
};

class HandSeeker {
  VirtualPlate myplate_;
  HandSeeker* sub_;
  HandList* hand_list_;
  static const unsigned int max_depth_; // <- byte ??
  unsigned int mydepth_;    // <- byte ??
  int branch_;
 public:
  HandSeeker();
  HandSeeker(const HandSeeker& src);
  ~HandSeeker() = default;
  int operator()(const VirtualPlate& game_plate);
  const HandSeeker& operator=(const HandSeeker& src);
  void set_myplate(const VirtualPlate& src);
  void record_list();
  void set_sub();
  int seek();
};

#endif // HAND_SEEKER_H_
