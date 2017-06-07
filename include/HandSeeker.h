#ifndef HAND_SEEKER_H_
#define HAND_SEEKER_H_

#include "../include/VirtualPlate.h"
#include <iostream>

class HandList {
  int position;
  double score;
 public:
  HandList();
  void set_position(int x);
  double get_score() const;
};

class HandSeeker {
  VirtualPlate myplate;
  HandSeeker* sub;
  int dist_x;   // <- size_t or unsigned ??
  HandList* hand_list;
  static const unsigned int max_depth; // <- byte ??
  unsigned int mydepth;    // <- byte ??
  /* int branch; */
 public:
  HandSeeker(VirtualPlate game_plate);
  HandSeeker(const HandSeeker& src);
  const HandSeeker& operator=(const HandSeeker& src);
  int get_conclusion() const;
  void record_list();
};

#endif // HAND_SEEKER_H_
