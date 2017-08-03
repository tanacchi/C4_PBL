#include "../include/VirtualPlate.hpp"

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

const VirtualPlate& VirtualPlate::operator=(const VirtualPlate& src)
{
  copy_plate(src);
  active_stone_ = src.active_stone_;
  return *this;
}

void VirtualPlate::init()
{
  for (short i = 0; i < PLATE_HEIGHT; i++)
    for (short j = 0; j < PLATE_WIDTH; j++)
      plate_[i][j] = Stone::Space;
}

void VirtualPlate::copy_plate(const VirtualPlate& src)
{
  for (short i = 0; i < PLATE_HEIGHT; i++)
    for (short j = 0; j < PLATE_WIDTH; j++)
      plate_[i][j] = src.plate_[i][j];
}

bool VirtualPlate::can_drop(short x, short y) const
{
  return (y < PLATE_HEIGHT-1) && (plate_[y+1][x] == Stone::Space);
}

void VirtualPlate::insert(short input_x)
{
  for (short y = 0; y < PLATE_HEIGHT; y++)
    if (!can_drop(input_x, y)) { plate_[y][input_x] = active_stone_; return; }
}

void VirtualPlate::switch_active_stone()
{
  active_stone_ = (active_stone_ == Stone::Red) ? Stone::Blue : Stone::Red;
}

bool VirtualPlate::can_continue() const
{
  for (short i = 0; i < PLATE_WIDTH; i++)
    if (can_drop(i, -1)) return true;
  return false;
}

bool VirtualPlate::is_inside_plate(short x, short y) const
{
  return (0 <= x && x < PLATE_WIDTH) && (0 <= y && y < PLATE_HEIGHT);
}

bool VirtualPlate::is_game_finish() const
{
  for (short i = 0; i < 4; i++) 
    for (short y = 0; y < PLATE_HEIGHT; y++) 
      for (short x = 0; x < PLATE_WIDTH; x++)
        if (plate_[y][x] != active_stone_) continue;
        else if (get_length(x, y, dx[i], dy[i]) >= 4) return true;
  return false;
}

short VirtualPlate::get_length(short x, short y, short dx, short dy) const
{
  short length;
  for (length = 1; is_inside_plate(x+dx*length, y+dy*length); length++)
    if (plate_[y+dy*length][x+dx*length] == active_stone_) continue;
    else break;
  return length;
}

bool VirtualPlate::is_valid_hand(short x) const
{
  return can_drop(x, -1);
}

Stone VirtualPlate::get_active_stone() const
{
  return active_stone_;
}
