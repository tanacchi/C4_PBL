#include "HandSeeker.h"

HandSeeker::HandSeeker(VirtualPlate game_plate)
  : myplate { game_plate },
    sub { 0 },
    dist_x { 0 }
{
}

HandSeeker::HandSeeker(const HandSeeker& src)
  : myplate { src.myplate },
    sub { src.sub },
    dist_x { src.dist_x }
{
}

const HandSeeker& HandSeeker::operator=(const HandSeeker& src) {
  myplate = src.myplate;
  sub = src.sub;
  dist_x = src.dist_x;
}

int HandSeeker::get_conclusion() {
  return dist_x;
}
