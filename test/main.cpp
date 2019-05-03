#include <gtest/gtest.h>

#include "RAM.hpp"
#include "CPU.hpp"

RAM *ram;
CPU *cpu;

int main(int argc, char **argv)
{
  RAM r;
  CPU c(&r);

  ram = &r;
  cpu = &c;
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
