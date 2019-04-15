#include <fstream>

#include "Interpretor.hpp"

int arm_S = 1;
int arm_N = 1;

int       toCycle(const sf::Time &t)
{
  double v = t.asMicroseconds();

  v /= 0.05959;
  return (v);
}

sf::Time  toTime(int cycle)
{
  sf::Time t;

  t = sf::microseconds(0.05959 * (double)(cycle));
  return (t);
}

sf::Time  toTime(int cycle);

int main(int argc, char **argv)
{
  if (argc < 2)
    return (1);

  std::ifstream file(argv[1]);
  Interpretor m;

  m.init();
  m.run(file);
}
