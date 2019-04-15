#pragma once

#include <SFML/System/Clock.hpp>

typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;

extern int arm_S;
extern int arm_N;

int       toCycle(const sf::Time &t);
sf::Time  toTime(int cycle);
