#include "VirtualPlate.hpp"

class HandSeeker {
public:
  HandSeeker();
  HandSeeker(const HandSeeker& src);
  ~HandSeeker() = default;
  int operator()(VirtualPlate game_plate);
  float get_list_score();
  float evaluate_plate();
private:
  const HandSeeker& operator=(const HandSeeker&);
  VirtualPlate myplate_;
  float hand_list_[PLATE_WIDTH];
  HandSeeker* sub_;
  Stone mystone_;
  const unsigned short max_depth_;
  unsigned short mydepth_;
};
