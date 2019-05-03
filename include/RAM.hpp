#pragma once

#include <iostream>
#include <mutex>

#include "my.h"

class RAM
{
public:
  RAM();
  virtual ~RAM();

  template <typename T>
  T getValue(u32 idx)
  {
    T value;
    u32 id = idx / 0x1000000;
    u32 addr = idx - (id * 0x1000000);

    switch (id)
    {
      case 2:
        return (*(T*)(WRAM + addr));
      case 3:
        return (*(T*)(IRAM + addr));
      case 4:
        return (*(T*)(IO + addr));
      case 6:
        //std::cout << "GET :" << std::hex << addr << std::endl;
        return (*(T*)(VRAM + addr));
      case 7:
        return (*(T*)(OAM + addr));
      case 8:
        return (*(T*)(ROM + addr));
      default:
        return (value);
    }

    return (value);
  }

  template <typename T>
  bool setValue(u32 idx, T v)
  {
    u32 id = idx / 0x1000000;
    u32 addr = idx - (id * 0x1000000);

    switch (id)
    {
      case 2:
        *(T*)(WRAM + addr) = v;
        return (true);
      case 3:
        *(T*)(IRAM + addr) = v;
        return (true);
      case 4:
        *(T*)(IO + addr) = v;
        return (true);
      case 6:
        //std::cout << "WRITE " << std::hex << addr << " : " << idx << std::endl;
        *(T*)(VRAM + addr) = v;
        return (true);
      case 7:
        *(T*)(OAM + addr) = v;
        return (true);
      case 8:
        *(T*)(ROM + addr) = v;
        return (true);
      default:
        return (false);
    }

    return (true);
  }

private:
  u8      *WRAM;
  u8      *IRAM;
  u8      *IO;
  u8      *VRAM;
  u8      *OAM;
  u8      *ROM;

};
