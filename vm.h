#include <stdlib.h>
#include <assert.h>
#include "utils.h"

#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"

#define NoErr     0x00
#define SysHlt    0x01
#define ErrMem    0x02
#define ErrSegv   0x04

#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $8 (int64)
#define $c (char *)
#define $i (int)

#define $ax ->c.r.ax
#define $bx ->c.r.bx
#define $cx ->c.r.cx
#define $dx ->c.r.dx
#define $sp ->c.r.sp
#define $ip ->c.r.ip

#define segfault(x)   error((x), ErrSegv)


/*
 * 16-bit VM
 * AX
 * BX
 * CX
 * DX
 * SP: stack pointer
 * IP: instruction pointer
 * 65KB memory
 *
 * (Serial COM port)
 * (Floppy drive)
 *
*/

typedef unsigned short int Reg;
struct s_registers {
  Reg ax;
  Reg bx;
  Reg cx;
  Reg dx;
  Reg sp;
  Reg ip;
};
typedef struct s_registers Registers;


struct s_cpu {
  Registers r;
};
typedef struct s_cpu CPU;


enum e_opcode {
  mov = 0x01,
  nop = 0x02,
  hlt = 0x03,
};
typedef enum e_opcode Opcode;


struct s_instrmap {
  Opcode o;
  int8 s;
};
typedef struct s_instrmap IM;


typedef int16 Arg;
struct s_instruction {
  Opcode o;
  Arg a[]; /* 0-2 bytes */
};
typedef struct s_instruction Instruction;


typedef unsigned char ErrorCode;
// couldnt allocate 0xffff on the windows heap (is it?)
// typedef int8 Memory[0xffff];
// tried -Wl,--heap,16000000 and -Wl,--stack,16000000 but did not work
// there is something i couldnt understand.
typedef int8 Memory[0x10ff];
typedef int8 Program;


struct s_vm {
  CPU c;
  Memory m;
  int16 b; /* break line */
};
typedef struct s_vm VM;
typedef Memory *Stack;

static IM instrmap[] = {
  { mov, 0x03 },
  { nop, 0x01 },
  { hlt, 0x01 },
};
#define IMs (sizeof(instrmap) / sizeof(struct s_instrmap))

void __mov(VM*, Opcode, Arg, Arg);

void printhex(Program*, int16, char);
void error(VM*, ErrorCode);
void execinstr(VM*, Program*);
void execute(VM*);
Program *exampleprogram(VM*);
int8 map(Opcode);
VM *virtualmachine(void);
int main(int, char**);

/*
Section .text (code) +read +exec -write
  #######
  ######

  --------- <- break line separating .text from our stack

  ****
  *****
  *****
  *****
Section .data +read -exec +write

*/
