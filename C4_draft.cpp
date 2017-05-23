#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#define PLATE_HEIGHT 6
#define PLATE_WIDTH  7

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
  Plate(const Plate& plate);
  const Plate& operator=(const Plate& src);
  ~Plate();
  void init();
  void show() const;
  char convert_stone_to_char(Stone stone) const;
  void insert(int input_x);
  bool can_drop(int x, int y) const;
  void switch_active_stone();
  bool can_continue() const;
  bool is_inside_plate(int x, int y) const;
  bool is_game_finish() const;
  int get_length(int x, int y, int dx, int dy) const;
};

Plate::Plate()
  : plate {std::vector<std::vector<Stone> > (PLATE_HEIGHT, std::vector<Stone> (PLATE_WIDTH))},
    active_stone {Stone::RED}
{
  init();
}

Plate::Plate(const Plate& src)
  : plate {src.plate},
    active_stone {src.active_stone}
{
}

const Plate& Plate::operator=(const Plate& src) {
  plate = src.plate;
  active_stone = src.active_stone;
  return *this;
}  

Plate::~Plate()
{
}

void Plate::init() {
  for (int i = 0; i < PLATE_HEIGHT; i++)
    for (int j = 0; j < PLATE_WIDTH; j++)
      plate[i][j] = Stone::SPACE;
}

void Plate::show() const {
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

char Plate::convert_stone_to_char(Stone stone) const {
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

bool Plate::can_drop(int x, int y) const {
  return (y < PLATE_HEIGHT-1) && (plate[y+1][x] == Stone::SPACE);
}

void Plate::switch_active_stone() {
  active_stone = (active_stone == Stone::RED) ? Stone::BLUE : Stone::RED;
}

bool Plate::can_continue() const {
  int count = 0;
  for (int i = 0; i < PLATE_HEIGHT; i++)
    for (int j = 0; j < PLATE_WIDTH; j++)
      if (plate[i][j] == Stone::SPACE) count++;
  return (count > 0);
}

bool Plate::is_inside_plate(int x, int y) const {
  return (0 <= x && x < PLATE_WIDTH) && (0 <= y && y < PLATE_HEIGHT);
}

bool Plate::is_game_finish() const {
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

int Plate::get_length(int x, int y, int dx, int dy) const {
  int i;
  for (i = 1; is_inside_plate(x+i*dx, y+i*dy); i++)
    if (plate[y+i*dy][x+i*dx] == active_stone) continue;
    else break;
  return i;
}

int main() {

  srand((unsigned)time(NULL));
  
  Plate plate;

  plate.init();
  plate.show();

  while (plate.can_continue()) { 
    int input_x;
    std::cout << "Input hand !!         >>>>>>> " << std::flush;
    std::cin >> input_x;
    // input_x = rand()%7;
    plate.insert(input_x);

    plate.show();
    if (plate.is_game_finish()) break;
    plate.switch_active_stone();
  }
  return 0;
}
