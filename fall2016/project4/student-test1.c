/* these are some Student Tests for fs-sim.c */
/* we're testing the robustness of our UNIX Filesystem */

#include <stdio.h>
#include <assert.h>
#include "fs-sim.h"

int main() {
  Fs_sim filesystem;

  mkfs(&filesystem);

  touch(&filesystem, "mother");
  touch(&filesystem, "father");

  assert(mkdir(&filesystem, "child/ken") == 0);

  mkdir(&filesystem, "children");
  cd(&filesystem, "children");
  
  touch(&filesystem, "chris");
  touch(&filesystem, "anna");
  touch(&filesystem, "mary");
  
  ls(&filesystem, ".");
  printf("\n");

  cd(&filesystem, "/");
  assert(rm(&filesystem, "katheryn") == 0);
  assert(rm(&filesystem, "mary") == 0);
  rm(&filesystem, "mother");
  
  ls(&filesystem, ".");
  printf("\n");

  assert(cd(&filesystem, "father") == 0);
  rmfs(&filesystem);

  printf("You passed the student tests!\n");
  return 0;
}
