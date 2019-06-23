#if !defined(MOCKFILE)
#define MOCKFILE

/* Anna Blendermann, ablender, 114474025, 0104 */
/* I pledge on my honor that I have not given or received any unauthorized */
/* assistance on this programming assignment (project6) */

typedef struct Target {
  int target_id;
  char **target_line;
  char **action_line;
  struct Target *next;
} Target;

typedef struct Mockfile {
  char *name;
  int num_targets;
  struct Target *head;
  struct Target *tail;
} Mockfile;

#endif
