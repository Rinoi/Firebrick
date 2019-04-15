
#include <cmath>
#include <iostream>

#include "CPU.hpp"

const char *CPU::opName[16]
{
  "AND",
  "EOR",
  "SUB",
  "RSB",
  "ADD",
  "ADC",
  "SBC",
  "RSC",
  "TST",
  "TEQ",
  "CMP",
  "CMN",
  "ORR",
  "MOV",
  "BIC",
  "MVN"
};

CPU::CPU(RAM *ram)
{
  this->C = 0;
  this->V = 0;
  this->N = 0;
  this->Z = 0;

  this->ram = ram;
}

bool CPU::interpretCondition(inst_u inst)
{
  u8 cond = inst.data.cond;

  if (cond == 0) //EQ
    return (Z);
  else if (cond == 1) //NE
    return (!Z);
  return (true);
}

int CPU::interpret(inst_u inst)
{
  R[15] += 1;
  if (interpretCondition(inst) == false)
    return (1);

  // std::cout << "------" << std::endl;
  // std::cout << std::hex << inst.inst << std::endl;
  // std::cout << "cond: " << (int)(inst.data.cond) << " ze: " << (int)(inst.data.ze) << " i: " << (int)(inst.data.I) << std::endl;
  // std::cout << "op : " << (int)(inst.data.op) << " S: " << (int)(inst.data.S) << std::endl;
  // std::cout << "Rn : " << (int)(inst.data.Rn) << " Rd: " << (int)(inst.data.Rd) << std::endl;
  if (inst.bx.op == 0x12FFF1);
    //std::cout << "BX " << "  ";
  else
  {
    u8 code = inst.b.op;

    // std::cout << "code : " << std::hex << (int)(code) << std::endl;
    if (code == 0x5)
      return (B(inst));
    else if (code == 0x0 || code == 0x1)
    {
      // u32 codeN = getEncode(inst, 23, 2);
      //
      // // CHECK MSR MRS
      // if (codeN == 0x2)
      // {
      //   if (code == 0x0 && getEncode(inst, 0, 11) == 0x0 && getEncode(inst, 16, 6) == 0xF);
      //     //std::cout << "MRS" << "  ";
      //   else if (getEncode(inst, 12, 10) == 0x29F);
      //     //std::cout << "MSR" << "  ";
      //   else;
      //     //std::cout << "M00  " << std::endl;
      // }
      //END

      if (inst.mul.ze == 0x0)
      {
        if (inst.mul.op == 0x9)
          MUL(inst);
        else if (inst.strH.b1 == 1 && inst.strH.b2 == 1)
          return (STRH(inst));
        else
          return (interpretOp(inst));
      }
      else
        return (interpretOp(inst));
    }
    //CHECK LDR, STR
    else if (code == 0x2 || code == 0x3)
      return (STR(inst));

    else if (inst.swi.op == 0xF)
      return (SWI(inst));
      //std::cout << "000  " << std::endl;
  }
  return (1);
}

int     CPU::SWI(inst_u inst)
{
  u32   v = inst.swi.off;

  if (v == 0x60000)
    return (SWI_DIV(inst));
  return (1);
}

int     CPU::SWI_DIV(inst_u)
{
  u32   n1 = R[0];
  u32   n2 = R[1];

  R[0] = n1 / n2;
  R[1] = n1 % n2;
  R[2] = std::abs((int)(R[1]));
  //std::cout << "DIV " << n1 << " / " << n2 << " = " << R[0] << std::endl;
  return (20);
}

int     CPU::interpretOp(inst_u inst)
{
  //std::cout << "OK" << std::endl;
  switch (inst.data.op)
  {
    case 0x2 :
      return (SUB(inst));
    case 0x4 :
      return (ADD(inst));
    case 0xD :
      return (MOV(inst));
    default:
      std::cout << opName[inst.data.op] << std::endl;
      return (1);
  }
}

u32   CPU::getRot(u8 value, u8 rot)
{
  u32 v;

  if (rot == 0)
    return (value);
  rot *= 2;
  v = value >> rot;
  v += value << (32 - rot);

  return (v);
}

/******************************************/
/********           inst         **********/
/******************************************/

int  CPU::MOV(inst_u inst)
{
  u32 v = getV(inst);

  //std::cout << "MOV " << std::hex << (int)(inst.data.Rd) << " " << v << std::endl;
  R[inst.data.Rd] = v;
  return (4);
}

int  CPU::ADD(inst_u inst)
{
  u8  Rn;
  u8  Rd;
  u32 v = getV(inst);

  Rn = inst.data.Rn;
  Rd = inst.data.Rd;

  R[Rd] = R[Rn] + v;
  //std::cout << "ADD:" << (int)(Rd) << "=" << (int)(Rn) << "+" << v << std::endl;
  return (4);
}

int  CPU::MUL(inst_u inst)
{
  //std::cout << "MUL " << (int)(inst.mul.Rd) << "=" << (int)(inst.mul.Rm) << "*" << (int)(inst.mul.Rs) << std::endl;
  R[inst.mul.Rd] = R[inst.mul.Rm] * R[inst.mul.Rs];
  return (5);
}

int  CPU::STR(inst_u inst)
{
  //std::cout << I << " " << P << " " << U << " " << W << " " << L << std::endl;
  //std::cout << "STR:" << (int)(inst.strH.Rn) << ":" << (int)(inst.strH.Rd) << std::endl;

  this->ram->setValue(R[inst.strH.Rn], R[inst.strH.Rd]);
  return (4);
}

int  CPU::STRH(inst_u inst)
{
  bool  P = inst.strH.P;
  bool  U = inst.strH.U;

  //std::cout << P << " " << U << " " << W << " " << L << " " << (int)(Rm) << std::endl;
  //std::cout << "STRH:" << (int)(inst.strH.Rn) << ":" << (int)(inst.strH.Rd) << std::endl;

  R[inst.strH.Rn] += (P == true ? 1 : 0) * (U == true ? 1 : -1) * inst.strH.Rm;
  this->ram->setValue<u16>(R[inst.strH.Rn], R[inst.strH.Rd]);
  R[inst.strH.Rn] += (P == true ? 0 : 1) * (U == true ? 1 : -1) * inst.strH.Rm;
  return (4);
}

int  CPU::SUB(inst_u inst)
{
  u8  Rn = inst.data.Rn;
  u8  Rd = inst.data.Rd;
  u32 v = getV(inst);

  //std::cout << "SUB:" << (int)(Rd) << ":" << (int)(R[Rn]) << "-" << v << "=" << (int)(R[Rn] - v) << std::endl;
  R[Rd] = R[Rn] - v;
  if (R[Rd] == 0)
    Z = true;
  else
    Z = false;
  return (4);
}

int  CPU::B(inst_u inst)
{
  int v = inst.b.off;

  if (v < 0)
    v += 1;
  //std::cout << "B:" << std::dec << (v) << std::endl;
  R[15] += v;
  return (2 * arm_S + arm_N);
}
