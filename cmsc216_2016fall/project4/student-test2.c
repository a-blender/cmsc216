/* these are the second round of Student Tests for fs-sim.c */
/* we're testing the UNIX Filesystem operations of touch/mkdir */

#include <stdio.h>
#include <assert.h>
#include "fs-sim.h"

int main() {
  Fs_sim filesystem;

  mkfs(&filesystem);

  mkdir(&filesystem, "blue_swede");
  mkdir(&filesystem, "chris_pratt");
  mkdir(&filesystem, "chris/pratt");
  mkdir(&filesystem, "cherry*bomb");

  ls(&filesystem, ".");
  printf("\n");

  assert(touch(&filesystem, "blue_swede") == 1);
  assert(mkdir(&filesystem, "blue_swede") == 0);
  assert(cd(&filesystem, "pratt") == 0);

  cd(&filesystem, "cherry*bomb");
  touch(&filesystem, "chris_pratt");
  touch(&filesystem, "victoria_song");

  ls(&filesystem, ".");
  printf("\n");

  rm(&filesystem, "chris_pratt");
  ls(&filesystem, ".");

  printf("You passed all the student tests!\n");
  return 0;
}
  

