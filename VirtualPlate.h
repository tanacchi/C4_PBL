#ifndef VirtualPlate_h
#define VirtualPlate_h

#include <vector>

#define PLATE_HEIGHT 6
#define PLATE_WIDTH  7

enum class Stone {
  Space,
  Red,
  Blue
};

class VirtualPlate {
  std::vector <std::vector <Stone> > plate;
  Stone active_stone;
public:
  VirtualPlate();
  VirtualPlate(const VirtualPlate& plate);
  const VirtualPlate& operator=(const VirtualPlate& src);
  ~VirtualPlate() = default;
  void init();
  void insert(int input_x);
  bool can_drop(int x, int y) const;
  void switch_active_stone();
  bool can_continue() const;
  bool is_inside_plate(int x, int y) const;
  bool is_game_finish() const;
  int get_length(int x, int y, int dx, int dy) const;
  bool is_valid_hand(int x) const;
  friend void show(VirtualPlate game_plate);
};

#endif
