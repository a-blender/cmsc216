/* some student tests for machine.c */
#include <stdio.h>
#include <assert.h>
#include "machine.h"

int main() {
  
  /* these should be correct */
  assert(valid_instruction(0x011a, 000000) == 1);
  assert(valid_instruction(0x10d9, 000000) == 1);
  
  /* these are incorrect mwhahaha */
  assert(valid_instruction(0xf040, 00000) == 0);
  assert(valid_instruction(0xf000, 62331) == 0);
  
  printf("Finished all the student tests!\n");
  return 0;
}
