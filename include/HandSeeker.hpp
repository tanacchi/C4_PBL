#ifndef HAND_SEEKER_H_
#define HAND_SEEKER_H_

#include "../include/VirtualPlate.hpp"

class HandList {
public:
  HandList();
  HandList(const HandList& src);
  int position_;
  float score_;
};

class HandSeeker {
 public:
  HandSeeker(int max_depth = 5);
  HandSeeker(VirtualPlate game_plate);
  HandSeeker(const HandSeeker& src);
  const HandSeeker& operator=(const HandSeeker& src);
  int operator()(VirtualPlate game_plate); 
  float get_list_score();
  float evaluate_plate();
private:
  VirtualPlate myplate_;
  HandSeeker* sub_;
  Stone mystone_;
  HandList hand_list_[6];
  int max_depth_;
  int mydepth_;
};

#endif // HAND_SEEKER_H_
