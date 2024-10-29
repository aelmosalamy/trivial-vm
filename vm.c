// Non-Copyright (c) 2024 Adham Elmosalamy.
// The entire design was made by Dr Jonas Birch, all credits go to him.
#include "vm.h"

void __mov(VM *vm, Opcode opcode, Arg a1, Arg a2) {
  vm $ax = (Reg)a1;

  return;
}

void execinstr(VM* vm, Program* p) {
  Arg a1, a2;
  int16 size;

  a1 = a2 = 0;
  size = map(*p);

  switch (size) {
    case 1:
      break;

    case 2:
      a1 = *(p+1);
      break;

    case 3:
      a1 = *(p+1);
      a2 = *(p+3);
      break;

    default:
      segfault(vm);
      break;
  }

  switch (*p) {
    case mov:
      __mov(vm, (Opcode)*p, a1, a2);
      break;

    case nop:
      break;

    case hlt:
      error(vm, SysHlt);
      break;
  }
}

void execute(VM *vm) {
  int32 brkaddr;
  Program *pp;
  int16 size;

  // check vm had a program loaded in memory
  assert(vm && *vm->m);
  size = 0;
  brkaddr = (int32)vm->m + vm->b;
  pp = (Program *)vm->m;

  /* instr1 arg1 instr2 instr3 */
  /* mov ax, 0x05; nop; hlt; */
  /* 0x01 0x00 0x05; */
  /* 0x02 */
  /* 0x03 */
  // while ((*pp != (Opcode)hlt) && (pp <= vm->b)) {
  do {
    vm $ip += size;
    pp += size;

    if ((int32)pp > brkaddr)
      segfault(vm);

    size = map(*pp);
    execinstr(vm, pp);

  } while(*pp != (Opcode)hlt);

  return;
}


void printhex(int8* program, int16 size, char delim) {
  while (size--) {
    printf("%.02x%c", *program, delim);
    program++;
  }
  printf("\n");
}

void error(VM* vm, ErrorCode e) {
  int8 exitCode = -1;

  switch (e) {
    case ErrSegv:
      fprintf(stderr, "%s\n", "VM Segmentation Fault");
      break;

    case SysHlt:
      fprintf(stderr, "%s\n", "System halted");
      exitCode = 0;

      // post-exit diagnostics
      printf("ax = %.04hx\n", $i vm $ax);
      printhex($1 vm->m, (map(mov)+map(nop)+map(hlt)+4), ' ');

      break;

    default:
      break;
  }
  
  if (vm)
    free(vm);

  exit($i exitCode);
}

int8 map(Opcode o) {
  int8 n, ret;
  IM *p;

  ret = 0;
  for (n=IMs, p=instrmap; n; n--, p++)
    if (p->o == o) {
      ret = p->s;
      break;
    }

  return ret;
}

VM *virtualmachine() {
  VM *p;
  // Program *pp;
  int16 size;

  size = $2 sizeof(struct s_vm);
  p = (VM *) malloc($i size);
  
  if (!p) {
    errno = ErrMem;
    return (VM *) 0;
  }

  zero($1 p, size);

  return p;
}


Program *exampleprogram(VM *vm) {
  Program *p;
  Instruction *i1, *i2, *i3;
  Arg a1;
  int16 s1, s2, sa1;

  a1 = 0;
  s1 = map(mov);
  s2 = map(nop);

  i1 = (Instruction *) malloc($i s1);
  i2 = (Instruction *) malloc(s2);
  i3 = (Instruction *) malloc(s2);
  assert(i1 && i2);
  zero($1 i1, s1);
  zero($1 i2, s2);
  zero($1 i3, s2);

  i1->o = mov;
  sa1 = (s1-1);
  a1 = 0x0005;

  p = vm->m;
  copy($1 p, $1 i1, 1);
  p++;

  if (a1) {
    copy($1 p, $1 &a1, sa1);
    p += sa1;
  }

  i2->o = nop;
  copy($1 p, $1 i2, 1);
  p++;

  i3->o = hlt;
  copy($1 p, $1 i3, 1);

  vm->b = (s1+sa1+s2+s2);
  vm $ip = (Reg)vm->m;
  vm $sp = (Reg)-1;

  free(i1);
  free(i2);

  return (Program *)&vm->m;
}


int main(int argc,  char *argv[]) {
  Program *prog;
  VM *vm;

  vm = virtualmachine();
  printf("vm  = %p (sz: %lld)\n", vm, sizeof(struct s_vm));

  prog = exampleprogram(vm);
  printf("prog  = %p\n", prog);

  printf("ax = %.04hx\n", $i vm $ax);

  printf("executing program on vm...\n");
  execute(vm);

  return 0;
}

