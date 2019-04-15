#include <iostream>

#include "RAM.hpp"


RAM::RAM()
{
  this->WRAM = new u8[0x40000];
  this->IRAM = new u8[0x08000];
  this->IO = new u8[0x003FF];
  this->VRAM = new u8[0x18000];
  this->OAM = new u8[0x00400];
  this->ROM = new u8[0x1000000];
}

RAM::~RAM()
{
}
