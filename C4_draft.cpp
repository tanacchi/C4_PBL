#include <iostream>
#include <vector>

#define PLATE_HEIGHT 6
#define PLATE_WIDTH 7

enum class Stone {
  SPACE,
  RED,
  BLUE
};

class Plate {
  std::vector <std::vector <Stone> > plate;
  Stone active_stone;
public:
  Plate();
  void init();
  void show();
  char convert_stone_to_char(Stone stone);
  void insert(int input_x);
  bool can_drop(int x, int y);
  void switch_active_stone();
  bool can_continue();
  bool is_inside_plate(int x, int y);
};

Plate::Plate()
  : plate {std::vector<std::vector<Stone> > (PLATE_HEIGHT, std::vector<Stone> (PLATE_WIDTH))},
    active_stone {Stone::RED}
  {
  }

void Plate::init() {
  for (int i = 0; i < PLATE_HEIGHT; i++)
    for (int j = 0; j < PLATE_WIDTH; j++)
      plate[i][j] = Stone::SPACE;
}

void Plate::show() {
  std::cout << "-----------------" << std::endl;
  std::cout << "| ";
  for (int i = 0; i < PLATE_WIDTH; i++) std::cout << i << ' ';
  std::cout <<"|\n";
  for (int y = 0; y < PLATE_HEIGHT; std::cout.put('\n'), y++) {
    std::cout << "| ";
    for (int x = 0; x < PLATE_WIDTH; std::cout.put(' '), x++)
      std::cout.put(convert_stone_to_char(plate[y][x]));
    std::cout << "|";
  }
  std::cout << "-----------------" << std::endl;
}

char Plate::convert_stone_to_char(Stone stone) {
  return
    (stone == Stone::RED)  ? 'O':
    (stone == Stone::BLUE) ? 'X':
    ' ';
}

void Plate::insert(int input_x) {
  if (plate[0][input_x] != Stone::SPACE) return;
  for (int y = 0; y < PLATE_HEIGHT; y++) {
    if (!can_drop(input_x, y)) { plate[y][input_x] = active_stone; return; };
  }
}

bool Plate::can_drop(int x, int y) {
  return (y < PLATE_HEIGHT-1) && (plate[y+1][x] == Stone::SPACE);
}

void Plate::switch_active_stone() {
  active_stone = (active_stone == Stone::RED) ? Stone::BLUE : Stone::RED;
}

bool Plate::can_continue() {
  int count = 0;
  for (int i = 0; i < PLATE_HEIGHT; i++)
    for (int j = 0; j < PLATE_WIDTH; j++)
      if (plate[i][j] == Stone::SPACE) count++;
  return (count > 0);
}

bool Plate::is_inside_plate(int x, int y) {
  return (0 <= x && x < PLATE_WIDTH) && (0 <= y && y < PLATE_HEIGHT);
}

int main() {

  Plate plate;

  plate.init();
  plate.show();

  while (plate.can_continue()) { 
    int input_x;
    std::cout << "Input hand !!         >>>>>>> " << std::flush;
    std::cin >> input_x;
    plate.insert(input_x);

    plate.show();
    plate.switch_active_stone();
  }
  return 0;
}
