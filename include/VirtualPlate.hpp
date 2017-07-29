#ifndef VIRTUAL_PLATE_H_
#define VIRTUAL_PLATE_H_

#define PLATE_HEIGHT 6
#define PLATE_WIDTH  7

#include <iostream>

enum class Stone {
	Space,
	Red,
	Blue
};

static const short dx[4] = { 1, 1, 1, 0 };
static const short dy[4] = {-1, 0, 1, 1 };

class VirtualPlate { 
  Stone plate_[PLATE_HEIGHT][PLATE_WIDTH];
  Stone active_stone_;
 public:
  VirtualPlate();
  VirtualPlate(const VirtualPlate& plate);
  const VirtualPlate& operator=(const VirtualPlate& src);
  ~VirtualPlate() = default;
  void init();
  void copy_plate(const VirtualPlate& src);
  void insert(short input_x);
  bool can_drop(short x, short y) const;
  void switch_active_stone();
  bool can_continue() const;
  bool is_inside_plate(short x, short y) const;
  bool is_game_finish() const;
  short get_length(short x, short y, short dx, short dy) const;
  bool is_valid_hand(short x) const;
  Stone get_active_stone() const;
  char to_char(Stone stone);
  void show();
};

#endif // VIRTUAL_PLATE_H_
