#include "fs-sim-datastructure.h"

/* (c) Larry Herman, 2016.  You are allowed to use this code yourself, but
   not to provide it to anyone else. */

void mkfs(Fs_sim *files);
int touch(Fs_sim *files, const char arg[]);
int mkdir(Fs_sim *files, const char arg[]);
int cd(Fs_sim *files, const char arg[]);
int ls(Fs_sim *files, const char arg[]);
void pwd(Fs_sim *files);
void rmfs(Fs_sim *files);
int rm(Fs_sim *files, const char arg[]);
