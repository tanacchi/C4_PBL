#ifndef HAND_SEEKER_H_
#define HAND_SEEKER_H_

#include "../include/VirtualPlate.hpp"

typedef struct {
  short position_;
  float score_;
} HandList;

class HandSeeker {
public:
  HandSeeker();
  HandSeeker(const HandSeeker& src);
  ~HandSeeker() = default;
  int get_conclusion(VirtualPlate game_plate);
  float get_list_score();
  float evaluate_plate();
private:
  const HandSeeker& operator=(const HandSeeker&);
  VirtualPlate myplate_;
  HandList hand_list_[PLATE_WIDTH];
  HandSeeker* sub_;
  Stone mystone_;
  const unsigned short max_depth_;
  unsigned short mydepth_;
};

#endif // HAND_SEEKER_H_
