#include "Interpretor.hpp"

#include <SFML/System/Clock.hpp>

#include <iostream>

Interpretor::Interpretor()
{
  this->cpu = NULL;
  this->ram = NULL;
  this->lcd = NULL;

  this->scanline = 0;
  this->cycle = 0;
}

Interpretor::~Interpretor()
{
  if (this->cpu != NULL)
    delete this->cpu;
  if (this->ram != NULL)
    delete this->ram;
  if (this->lcd != NULL)
    delete this->lcd;
}

int Interpretor::init()
{
  if (this->ram == NULL)
    this->ram = new RAM();
  if (this->cpu == NULL)
    this->cpu = new CPU(this->ram);
  if (this->lcd == NULL)
  {
    this->lcd = new LCD(this->ram);
    this->lcd->run();
  }
  return (0);
}

int Interpretor::run(std::ifstream &file)
{
  int size = 1000000;
  int pc = 0x228;
  sf::Clock cl;

  pc /= 4;
  u32 *pr = new u32[size];
  size = file.read((char *)pr, size).gcount();
  (*cpu)[15] = pc;

  while (42)
  {
    inst_u inst;
    int t = 0;
    int cycle;

    cl.restart();
    while (t <= 2024)
    {
      inst.inst = pr[(*cpu)[15]];
      t += this->cpu->interpret(inst);
    }
    cycle = toCycle(cl.getElapsedTime());
    //std::cout << "sleep : " << std::dec << toTime(cycle - t).asMicroseconds() << std::endl;
    sf::sleep(toTime(cycle - t));
    //usleep(100000);
  }
  return (1);
}

// void  Interpretor::VDraw()
// {
//   u32 colorTab[240];
//   int y = this->scanline;
//   for (int x = 0; x < 240; x += 1)
//     {
//       u16 c = ram->getValue<u16>(0x6000000 + ((y * 160 + x) * sizeof(u16)));
//
//       int color;
//       u8 *cc = (u8*)(&color);
//       cc[0] = (float)(c & 0x001F) / 31 * 255;
//       cc[1] = (float)(c & 0x03E0) / 31 * 255;
//       cc[2] = (float)(c & 0x7C00) / 31 * 255;
//       cc[3] = 255;
//
//       colorTab[x] = color;
//     }
//   //this->lcd->getM().lock();
//   this->lcd->getTexture().update((u8*)&colorTab[0], 240, 1, 0, y);
//   this->lcd->draw();
//   //this->lcd->getM().unlock();
// }

// int Interpretor::run(std::ifstream &file)
// {
//   int i = 16;
//   int total = 0;
//   int size = 10000;
//   int pc = -1;
//
//   u32 *pr = new u32[size];
//   size = file.read((char *)pr, size).gcount();
//   std::cout << "SIZE " << size << std::endl;
//
//   for (int ptn = 0; ptn < size; ptn += 1)
//   {
//     u32 inst = pr[ptn];
//
//     if (i == 16)
//       std::cout << std::hex << total << " : ";
//     total += 4;
//     i -= 4;
//     if (total > 0x228)
//       this->cpu->interpret(inst);
//
//     if (i <= 0)
//     {
//       i = 16;
//       std::cout << std::endl;
//     }
//   }
//   return (1);
// }
