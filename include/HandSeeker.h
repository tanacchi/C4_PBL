#ifndef HAND_SEEKER_H_
#define HAND_SEEKER_H_

#include "../include/VirtualPlate.h"

class HandList {
  int position;
  double score;
 public:
  HandList();
  void set_position(int x);
};

class HandSeeker {
  VirtualPlate myplate;
  HandSeeker* sub;
  int dist_x;   // <- size_t or unsigned ??
  HandList* hand_list;
  /* int dist_x, dist_y; */
  /* std::mt19937 rand_pos; */
  /* std::vector<StoneScoreList> score_list; */
  /* BoardMaster virtual_board; */
  /* int mydepth; */
  /* OthelloAI* subAI; */
  /* int serial_num; */
  /* int branch; */
 public:
  HandSeeker(VirtualPlate game_plate);
  HandSeeker(const HandSeeker& src);
  const HandSeeker& operator=(const HandSeeker& src);
  int get_conclusion() const;
  void record_list();
};

#endif // HAND_SEEKER_H_
