#if !defined(FS_COMP)
#define FS_COMP

/* Two structures to implement the filesystem for project3 */
/* directly included in "fs-sim.h," indirectly included in "fs-sim.c" */
/* Fs_comp is declared first because Fs_sim depends on components */

/* Structure #1 - directory or file with linked list pointers */

/* type = specifies whether the struct is a directory or a file*/
/* name = specifies the directory/file name */
/* *sub_dir = pointer to sub directory (set to NULL for files) */
/* *parent_dir = pointer parent directory (set to NULL for files) */
/* *next = pointer to next directory/file in the current location */

typedef struct Component {
  char *type;
  char *name;
  struct Component *sub_dir;
  struct Component *parent_dir;
  struct Component *next;
} Fs_comp;

/* Structuree #2 - filesystem with root and current directory level */

/* *root = pointer to the filesystem's root directory  */
/* *curr_dir = pointer to the current directory */

typedef struct Filesystem {
  struct Component *root;
  struct Component *curr_dir;
} Fs_sim;

#endif
