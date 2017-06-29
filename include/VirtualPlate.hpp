#ifndef VIRTUAL_PLATE_H_
#define VIRTUAL_PLATE_H_

#define PLATE_HEIGHT 6
#define PLATE_WIDTH  6

enum class Stone {
  Space,
  Red,
  Blue
};

static const short dx[] = { 1, 1, 1, 0 };
static const short dy[] = {-1, 0, 1, 1 };

class VirtualPlate {
 public:
  VirtualPlate();
  VirtualPlate(const VirtualPlate& plate);
  const VirtualPlate& operator=(const VirtualPlate& src);
  ~VirtualPlate() = default;
  void init();
  void copy_plate(const VirtualPlate& src);
  void insert(short input_x);
  inline bool can_drop(short x, short y) const;
  void switch_active_stone();
  bool can_continue() const;
  inline bool is_inside_plate(short x, short y) const;
  bool is_game_finish() const;
  int get_length(short x, short y, short dx, short dy) const;
  bool is_valid_hand(short x) const;
  friend void show(VirtualPlate game_plate);
  Stone get_active_stone() const;
private:
  /* enum class Stone { */
  /*   Space, */
  /*   Red, */
  /*   Blue */
  /* }; */
  Stone plate_[PLATE_HEIGHT][PLATE_WIDTH];
  Stone active_stone_;
};

#endif // VIRTUAL_PLATE_H_
