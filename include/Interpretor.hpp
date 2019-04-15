#pragma once

#include <fstream>

#include "RAM.hpp"
#include "CPU.hpp"
#include "LCD.hpp"

class Interpretor
{
public:
  Interpretor();
  ~Interpretor();

  int init();
  int run(std::ifstream &file);

private:
  void VDraw();

private:

  CPU *cpu;
  RAM *ram;
  LCD *lcd;

  int scanline;
  int cycle;
};
