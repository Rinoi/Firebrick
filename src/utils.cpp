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
