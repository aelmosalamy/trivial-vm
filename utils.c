#include "utils.h"

void copy(int8 *dst, int8 *src, int16 size) {
  int8 *d, *s;
  int16 n;

  for (n=size, d=dst, s=src; n; n--, d++, s++)
    *d = *s;

  return;
}

void zero(int8 *str, int16 size) {
    int8 *p;
    int16 n;

    for (n=0, p=str; n<size; n++, p++)
        *p = 0;

    return;
}
