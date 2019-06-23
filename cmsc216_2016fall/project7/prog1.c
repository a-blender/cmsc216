#include <stdio.h>

/* (c) Larry Herman, 2016.  You are allowed to use this code yourself, but
   not to provide it to anyone else. */

int n, reversed= 0, negative= 1;

int main() {
  scanf("%d", &n);

  if (n < 0) {
    negative= -1;
    n= -n;
  }

  while (n > 0) {
    reversed *= 10;
    reversed += n % 10;
    n /= 10;
  }

  reversed *= negative;

  printf("%d\n", reversed);

  return 0;
}
