#include <iostream>
#include "VirtualPlate.h"

VirtualPlate::VirtualPlate()
  : plate {std::vector<std::vector<Stone> > (PLATE_HEIGHT, std::vector<Stone> (PLATE_WIDTH, Stone::SPACE))},
    active_stone {Stone::Red}
{
}

VirtualPlate::VirtualPlate(const VirtualPlate& src)
  : plate {src.plate},
    active_stone {src.active_stone}
{
}

const VirtualPlate& VirtualPlate::operator=(const VirtualPlate& src) {
  plate = src.plate;
  active_stone = src.active_stone;
  return *this;
}  

void VirtualPlate::init() {
  for (int i = 0; i < PLATE_HEIGHT; i++)
    for (int j = 0; j < PLATE_WIDTH; j++)
      plate[i][j] = Stone::Space;
}

char convert_stone_to_char(Stone stone) {
  return
    (stone == Stone::Red)  ? 'O':
    (stone == Stone::Blue) ? 'X':
    ' ';
}

void show(VirtualPlate game_plate) {
  std::cout << "-----------------" << std::endl;
  std::cout << "| ";
  for (int i = 0; i < PLATE_WIDTH; i++) std::cout << i << ' ';
  std::cout <<"|\n";
  for (int y = 0; y < PLATE_HEIGHT; std::cout.put('\n'), y++) {
    std::cout << "| ";
    for (int x = 0; x < PLATE_WIDTH; std::cout.put(' '), x++)
      std::cout.put(convert_stone_to_char(game_plate.plate[y][x]));
    std::cout << "|";
  }
  std::cout << "-----------------" << std::endl;
}

bool VirtualPlate::is_valid_hand(int x) const {
  return (plate[0][x] == Stone::Space) ;
}

void VirtualPlate::insert(int input_x) {
  for (int y = 0; y < PLATE_HEIGHT; y++)
    if (!can_drop(input_x, y)) { plate[y][input_x] = active_stone; return; }
}

bool VirtualPlate::can_drop(int x, int y) const {
  return (y < PLATE_HEIGHT-1) && (plate[y+1][x] == Stone::Space);
}

void VirtualPlate::switch_active_stone() {
  active_stone = (active_stone == Stone::Red) ? Stone::Blue : Stone::Red;
}

bool VirtualPlate::can_continue() const {
  int count = 0;
  for (int i = 0; i < PLATE_HEIGHT; i++)
    for (int j = 0; j < PLATE_WIDTH; j++)
      if (plate[i][j] == Stone::Space) count++;
  return (count > 0);
}

bool VirtualPlate::is_inside_plate(int x, int y) const {
  return (0 <= x && x < PLATE_WIDTH) && (0 <= y && y < PLATE_HEIGHT);
}

bool VirtualPlate::is_game_finish() const {
  const std::vector<int> dx = { 1, 1, 1, 0 };
  const std::vector<int> dy = {-1, 0, 1, 1 };
  for (int i = 0; i < 4; i++) 
    for (int y = 0; y < PLATE_HEIGHT; y++) 
      for (int x = 0; x < PLATE_WIDTH; x++) {
        if (plate[y][x] != active_stone) continue;
        if (get_length(x, y, dx[i], dy[i]) >= 4) return true;
      }
  return false;
}

int VirtualPlate::get_length(int x, int y, int dx, int dy) const {
  int i;
  for (i = 1; is_inside_plate(x+i*dx, y+i*dy); i++)
    if (plate[y+i*dy][x+i*dx] == active_stone) continue;
    else break;
  return i;
}
