#include "../include/VirtualPlate.h"

VirtualPlate::VirtualPlate()
  : active_stone_ {Stone::Red}
{
  init();
}

VirtualPlate::VirtualPlate(const VirtualPlate& src)
  : active_stone_ {src.active_stone_}
{
  copy_plate(src);
}

const VirtualPlate& VirtualPlate::operator=(const VirtualPlate& src) {
  copy_plate(src);
  active_stone_ = src.active_stone_;
  return *this;
}  

void VirtualPlate::init() {
  for (int i = 0; i < PLATE_HEIGHT; i++)
    for (int j = 0; j < PLATE_WIDTH; j++)
      plate_[i][j] = Stone::Space;
}

void VirtualPlate::copy_plate(const VirtualPlate& src) {
  for (int i = 0; i < PLATE_HEIGHT; i++)
    for (int j = 0; j < PLATE_WIDTH; j++)
      this->plate_[i][j] = src.plate_[i][j];
}

bool VirtualPlate::is_valid_hand(int x) const {
  return (plate_[0][x] == Stone::Space);
}

void VirtualPlate::insert(int input_x) {
  for (int y = 0; y < PLATE_HEIGHT; y++)
    if (!can_drop(input_x, y)) { plate_[y][input_x] = active_stone_; return; }
}

inline bool VirtualPlate::can_drop(int x, int y) const {
  return (y < PLATE_HEIGHT-1) && (plate_[y+1][x] == Stone::Space);
}

void VirtualPlate::switch_active_stone() {
  active_stone_ = (active_stone_ == Stone::Red) ? Stone::Blue : Stone::Red;
}

bool VirtualPlate::can_continue() const {
  for (int i = 0; i < PLATE_HEIGHT; i++)
    for (int j = 0; j < PLATE_WIDTH; j++)
      if (plate_[i][j] == Stone::Space) return true;
  return false;
}

inline bool VirtualPlate::is_inside_plate(int x, int y) const {
  return (0 <= x && x < PLATE_WIDTH) && (0 <= y && y < PLATE_HEIGHT);
}

bool VirtualPlate::is_game_finish() const {
  for (int i = 0; i < 4; i++) 
    for (int y = 0; y < PLATE_HEIGHT; y++) 
      for (int x = 0; x < PLATE_WIDTH; x++)
        if (plate_[y][x] != active_stone_) continue;
        else if (get_length(x, y, dx[i], dy[i]) >= 4) return true;
  return false;
}

int VirtualPlate::get_length(int x, int y, int dx, int dy) const {
  int length;
  for (length = 1; is_inside_plate(x+dx*length, y+dy*length); length++)
    if (plate_[y+dy*length][x+dx*length] == active_stone_) continue;
    else break;
  return length;
}
