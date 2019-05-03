#include <gtest/gtest.h>

#include "RAM.hpp"
#include "CPU.hpp"

extern RAM *ram;
extern CPU *cpu;

//MOVE

TEST(CPU, MOVE_directe1)
{
  inst_u inst = {0};
  value_u v = {0};

  inst.data.cond = 0xF;
  inst.data.op = 0xD;
  inst.data.Rd = 2;
  inst.data.I = true;
  v.d.imm = 0x42;
  v.d.rot = 0x0;

  inst.data.op2 = v.op2;

  cpu->interpret(inst);
  EXPECT_EQ((*cpu)[2], 0x42);
}

TEST(CPU, MOVE_directe2)
{
  inst_u inst = {0};
  value_u v = {0};

  inst.data.cond = 0xF;
  inst.data.op = 0xD;
  inst.data.Rd = 2;
  inst.data.I = true;
  v.d.imm = 0x0;
  v.d.rot = 0x0;

  inst.data.op2 = v.op2;

  cpu->interpret(inst);
  EXPECT_EQ((*cpu)[2], 0x0);
}

TEST(CPU, MOVE_directe3)
{
  inst_u inst = {0};
  value_u v = {0};

  inst.data.cond = 0xF;
  inst.data.op = 0xD;
  inst.data.Rd = 0;
  inst.data.I = true;
  v.d.imm = 0xFF;
  v.d.rot = 0x0;

  inst.data.op2 = v.op2;

  cpu->interpret(inst);
  EXPECT_EQ((*cpu)[0], 0xFF);
}

TEST(CPU, MOVE_directe_with_rot1)
{
  inst_u inst = {0};
  value_u v = {0};

  inst.data.cond = 0xF;
  inst.data.op = 0xD;
  inst.data.Rd = 10;
  inst.data.I = true;
  v.d.imm = 0x42;
  v.d.rot = 0x5;

  inst.data.op2 = v.op2;

  cpu->interpret(inst);
  EXPECT_EQ((*cpu)[10], 0x10800000);
}

TEST(CPU, MOVE_directe_with_rot2)
{
  inst_u inst = {0};
  value_u v = {0};

  inst.data.cond = 0xF;
  inst.data.op = 0xD;
  inst.data.Rd = 5;
  inst.data.I = true;
  v.d.imm = 0x32;
  v.d.rot = 28/2;

  inst.data.op2 = v.op2;

  cpu->interpret(inst);
  EXPECT_EQ((*cpu)[5], 0x320);
}

//ADD
