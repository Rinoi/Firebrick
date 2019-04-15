#pragma once

#include "my.h"

#include "RAM.hpp"

typedef struct Direct_s
{
  u16   imm : 8;
  u8    rot : 4;
} __attribute__((packed)) Direct_t;

typedef struct InDirect_s
{
  u8    rm    : 4;
  bool  b     : 1;
  u8    type  : 2;
  u8    shift : 5;
} __attribute__((packed)) InDirect_t;

typedef union value_t
{
  u16   op2 : 12;
  Direct_t d;
  InDirect_t i;
} value_u;

typedef struct Datap_s
{
  u16   op2 : 12;
  u8    Rd : 4;
  u8    Rn : 4;
  bool  S : 1;
  u8    op : 4;
  bool  I : 1;
  u8    ze : 2;
  u8    cond : 4;
} __attribute__((packed)) Datap_t;


typedef struct Mul_s
{
  u8    Rm    : 4;
  u8    op    : 4;
  u8    Rs    : 4;
  u8    Rn    : 4;
  u8    Rd    : 4;
  bool  S     : 1;
  bool  A     : 1;
  bool  U     : 1;
  bool  L     : 1;
  u8    ze    : 4;
  u8    cond  : 4;
} __attribute__((packed)) Mul_t;

typedef struct StrH_s
{
  u8    Rm    : 4;
  bool  b1    : 1;
  bool  S     : 1;
  bool  H     : 1;
  bool  b2    : 1;
  u8    off   : 4;
  u8    Rd    : 4;
  u8    Rn    : 4;
  bool  L     : 1;
  bool  W     : 1;
  bool  D     : 1;
  bool  U     : 1;
  bool  P     : 1;
  u8    ze    : 3;
  u8    cond  : 4;
} __attribute__((packed)) StrH_t;

typedef struct Bx_s
{
  u8    Rn    : 4;
  u32   op    : 24;
  u8    cond  : 4;
} __attribute__((packed)) Bx_t;

typedef struct Bl_s
{
  int   off   : 24;
  bool  L     : 1;
  u8    op    : 3;
  u8    cond  : 4;
} __attribute__((packed)) Bl_t;

typedef struct Swi_s
{
  u32   off   : 24;
  u8    op    : 4;
  u8    cond  : 4;
} __attribute__((packed)) Swi_t;

typedef union inst
{
  u32     inst;
  Datap_t data;
  Mul_s   mul;
  Bl_s    b;
  Bx_s    bx;
  StrH_s  strH;
  Swi_s   swi;
} inst_u;

class CPU
{
public:
  static const char *opName[16];
private:
  typedef struct s_info
  {
    u8 cond;
    u8 type;
    u8 op;
    bool S;
    u8 Rn;
    u8 Rd;

    union
    {
      struct
      {
        u8 rot;
        u8 imm;
      };
      struct
      {
        u8 shift;
        u8 r2;
      };
    };
  } t_info;
public:
  CPU(RAM *ram);

  int   interpret(inst_u inst);

private:

  int   interpretOp(inst_u inst);
  bool  interpretCondition(inst_u inst);

private:

  inline u32 getV(inst_u inst)
  {
    u32 r;
    value_u v;

    v.op2 = inst.data.op2;
    if (inst.data.I == true)
    {
      r = getRot(v.d.imm, v.d.rot);
    }
    else
    {
      if (v.i.type == 0x0)
        r = R[v.i.rm] << v.i.shift;
      else
        r = R[v.i.rm] >> v.i.shift;
    }
    return (r);
  }

  int   MUL(inst_u inst);

  int   MOV(inst_u inst);
  int   ADD(inst_u inst);
  int   STR(inst_u inst);
  int   STRH(inst_u inst);
  int   SUB(inst_u inst);
  int   B(inst_u inst);
  int   SWI(inst_u inst);

private:
  int   SWI_DIV(inst_u inst);

public:
  u32   getR(int r) const
  {
    return (R[r]);
  }

  void  setR(int r, u32 v)
  {
    R[r] = v;
  }

  u32   &operator[](int v)
  {
    return (R[v]);
  }

private:
  u32   getEncode(u32 inst, u32 from, u32 size);
  bool  getInfo(u32 inst, t_info &info);
  u32   getRot(u8 value, u8 rot);

  u32   R[16];
  bool  V;
  bool  C;
  bool  Z;
  bool  N;

  RAM   *ram;
};
