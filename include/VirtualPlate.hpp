#ifndef VIRTUAL_PLATE_H_
#define VIRTUAL_PLATE_H_

#define PLATE_HEIGHT 6
#define PLATE_WIDTH  6

enum class Stone {
  Space,
  Red,
  Blue
};

static const int dx[] = { 1, 1, 1, 0 };
static const int dy[] = {-1, 0, 1, 1 };

class VirtualPlate {
  /* enum class Stone { */
  /*   Space, */
  /*   Red, */
  /*   Blue */
  /* }; */
  Stone plate_[PLATE_HEIGHT][PLATE_WIDTH];
  Stone active_stone_;
 public:
  VirtualPlate();
  VirtualPlate(const VirtualPlate& plate);
  const VirtualPlate& operator=(const VirtualPlate& src);
  ~VirtualPlate() = default;
  void init();
  void copy_plate(const VirtualPlate& src);
  void insert(int input_x);
  inline bool can_drop(int x, int y) const;
  void switch_active_stone();
  bool can_continue() const;
  inline bool is_inside_plate(int x, int y) const;
  bool is_game_finish() const;
  int get_length(int x, int y, int dx, int dy) const;
  bool is_valid_hand(int x) const;
  friend void show(VirtualPlate game_plate);
};

#endif // VIRTUAL_PLATE_H_
