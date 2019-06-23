#if !defined(MOCKFILE_H)
#define MOCKFILE_H

/* (c) Larry Herman, 2016.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

#include "mockfile-datastructure.h"

Mockfile *read_mockfile(const char filename[]);
int lookup_target(Mockfile *const mockfile, const char target_name[]);
void print_action(Mockfile *const mockfile, int rule_num);
void print_mockfile(Mockfile *const mockfile);
int num_dependencies(Mockfile *const mockfile, int rule_num);
char *get_dependency(Mockfile *const mockfile, int rule_num,
                     int dependency_num);
int exists(const char filename[]);
int is_older(const char filename1[], const char filename2[]);
int do_action(Mockfile *const mockfile, int rule_num);
void clear_mockfile(Mockfile **const mockfile);

#endif
