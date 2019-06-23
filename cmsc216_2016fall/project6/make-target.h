#if !defined(MAKE_TARGET_H)
#define MAKE_TARGET_H

/* just documenting that this header file uses definitions in mockfile.h */
#include "mockfile.h"

/*
 * (c) Larry Herman, 2016.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int make_target(Mockfile *const mockfile, const char target_name[]);

#endif
