#ifndef HAND_SEEKER_H_
#define HAND_SEEKER_H_

#include "../include/VirtualPlate.hpp"

typedef struct {
  short position_;
  float score_;
} HandList;

class HandSeeker {
 public:
  HandSeeker(int max_depth = 2);
  HandSeeker(VirtualPlate game_plate);
  HandSeeker(const HandSeeker& src);
  const HandSeeker& operator=(const HandSeeker& src);
  int operator()(VirtualPlate game_plate); 
  float get_list_score();
  float evaluate_plate();
private:
  VirtualPlate myplate_;
  HandSeeker* sub_;
  HandList hand_list_[6];
  short depth_;
};

#endif // HAND_SEEKER_H_
