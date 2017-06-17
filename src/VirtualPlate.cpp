#include "../include/VirtualPlate.hpp"

VirtualPlate::VirtualPlate()
  : active_stone {Stone::Red}
{
  init();
}

VirtualPlate::VirtualPlate(const VirtualPlate& src)
  : active_stone {src.active_stone}
{
  copy_plate(src);
}

const VirtualPlate& VirtualPlate::operator=(const VirtualPlate& src) {
  copy_plate(src);
  active_stone = src.active_stone;
  return *this;
}  

void VirtualPlate::init() {
  for (int i = 0; i < PLATE_HEIGHT; i++)
    for (int j = 0; j < PLATE_WIDTH; j++)
      plate[i][j] = Stone::Space;
}

void VirtualPlate::copy_plate(const VirtualPlate& src) {
  for (int i = 0; i < PLATE_HEIGHT; i++)
    for (int j = 0; j < PLATE_WIDTH; j++)
      this->plate[i][j] = src.plate[i][j];
}

bool VirtualPlate::is_valid_hand(int x) const {
  return (plate[0][x] == Stone::Space);
}

void VirtualPlate::insert(int input_x) {
  for (int y = 0; y < PLATE_HEIGHT; y++)
    if (!can_drop(input_x, y)) { plate[y][input_x] = active_stone; return; }
}

inline bool VirtualPlate::can_drop(int x, int y) const {
  return (y < PLATE_HEIGHT-1) && (plate[y+1][x] == Stone::Space);
}

void VirtualPlate::switch_active_stone() {
  active_stone = (active_stone == Stone::Red) ? Stone::Blue : Stone::Red;
}

bool VirtualPlate::can_continue() const {
  for (int i = 0; i < PLATE_HEIGHT; i++)
    for (int j = 0; j < PLATE_WIDTH; j++)
      if (plate[i][j] == Stone::Space) return true;
  return false;
}

inline bool VirtualPlate::is_inside_plate(int x, int y) const {
  return (0 <= x && x < PLATE_WIDTH) && (0 <= y && y < PLATE_HEIGHT);
}

bool VirtualPlate::is_game_finish() const {
  static const int dx[] = { 1, 1, 1, 0 };
  static const int dy[] = {-1, 0, 1, 1 };
  for (int i = 0; i < 4; i++) 
    for (int y = 0; y < PLATE_HEIGHT; y++) 
      for (int x = 0; x < PLATE_WIDTH; x++)
        if (plate[y][x] != active_stone) continue;
        else if (get_length(x, y, dx[i], dy[i]) >= 4) return true;
  return false;
}

int VirtualPlate::get_length(int x, int y, int dx, int dy) const {
  int length;
  for (length = 1; is_inside_plate(x+dx*length, y+dy*length); length++)
    if (plate[y+dy*length][x+dx*length] == active_stone) continue;
    else break;
  return length;
}
