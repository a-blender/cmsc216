/* Anna Blendermann, ablender 114474025, 0104 */
/* I pledge on my honor that I have not given or received any unauthorized */
/* assistance on this programming assignment (project6) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <sysexits.h>

#include "mockfile.h"
#include "split.h"
#include "safe-fork.h"

void destroy_targets(Target *curr_target);

/* READ MOCKFILE************************************************************* */
Mockfile *read_mockfile(const char filename[]) {

  struct Mockfile *mockfile;
  char line1[1000], line2[1000];
  FILE * new_file;
  /* printf("read_mockfile\n"); */
  
  if (filename != NULL) {

    mockfile = malloc(sizeof(Mockfile));
    mockfile->name = malloc((strlen(filename)+1)*sizeof(char));

    strcpy(mockfile->name, filename);
    mockfile->num_targets = 0;
    mockfile->head = NULL;
    mockfile->tail = NULL;
    
    strcpy(mockfile->name, filename);
    new_file = fopen(filename, "r");
    
    if (new_file == NULL)
      return NULL;

    while (fgets(line1, 1000, new_file)) {

      /* new target line found */
      if (line1[0] != '\n' && line1[0] != '#' && line1[0] != '\t') {
	struct Target *new_target;

	/* new action line found - got both lines! */
	if (fgets(line2, 1000, new_file) && line2[0] == '\t') {
	  new_target = malloc(sizeof(Target));
	  new_target->target_line = split(line1);
	  new_target->action_line = split(line2);
	
	  new_target->target_id = mockfile->num_targets; /* think about zero */
	  mockfile->num_targets++;
	
	  /* case1: tail is null = add target to empty mockfile list */
	  if (mockfile->tail == NULL) {
	    mockfile->head = new_target;
	    mockfile->tail = new_target;
	    mockfile->tail->next = NULL;
	  }

	  /* case2: tail is not null = add target to end of mockfile list */
	  else if (mockfile->tail != NULL) {
	    mockfile->tail->next = new_target;
	    mockfile->tail = new_target;
	    new_target->next = NULL;
	  }
	} /* end of adding both lines to target */
      } /* end of finding new target line */
    } /* end of while loop, find new line */
    fclose(new_file);
    return mockfile;
  }
  return NULL; 
}

/* LOOKUP TARGET************************************************************* */
int lookup_target(Mockfile *const mockfile, const char target_name[]) {
  struct Target *curr;
  /* printf("lookup_target\n"); */

  if(mockfile != NULL && target_name != NULL) {
    
    curr = mockfile->head;
    while(curr != NULL && strcmp(target_name, *(curr->target_line)) != 0) {
      curr = curr->next;
    }
    if(curr != NULL)
      return curr->target_id;
  }
  return -1;
}

/* PRINT ACTION************************************************************** */
void print_action(Mockfile *const mockfile, int rule_num) {
  struct Target *curr;
  char **action_temp;
  /* printf("print_action\n"); */

  if (mockfile != NULL && rule_num >= 0) {
    if(rule_num == 0 || rule_num < mockfile->num_targets) {
    
      curr = mockfile->head;
      while(curr != NULL && curr->target_id != rule_num) {
	curr = curr->next;
      }
      if (curr != NULL) {
	action_temp = curr->action_line;
	printf("%s", *action_temp);
	action_temp++;
	while(*action_temp != NULL) {
	  printf(" %s", *action_temp);
	  action_temp++;
        }
      }
    }
  } /* end of if statements */
}

/* PRINT MOCKFILE************************************************************ */
void print_mockfile(Mockfile *const mockfile) {
  struct Target *curr;
  /* printf("print_mockfile\n"); */

  if (mockfile != NULL) {
    curr = mockfile->head;
    
    while(curr != NULL) {
      char **target_temp = curr->target_line;
      char **action_temp = curr->action_line;

      printf("%s:", *target_temp);
      target_temp++;      
      while(*target_temp != NULL) { /* print target line */
	printf(" %s", *target_temp);
	target_temp++;
      }
	
      printf("\n\t%s", *action_temp);
      action_temp++;
      while(*action_temp != NULL) { /* print action line */
	printf(" %s", *action_temp);
	action_temp++;
      }
	
      if(curr->next != NULL)
	printf("\n\n"); /* add two blank spaces */
      else printf("\n"); /* just one blank space */
      curr = curr->next;
    }
  }
}

/* NUM DEPENDENCIES********************************************************** */
int num_dependencies(Mockfile *const mockfile, int rule_num) {
  struct Target *curr;
  int num_depends = -1; /* start at 1 because of target name */
  char **dependency;
  /* printf("num_dependencies\n"); */
  
  if (mockfile != NULL && rule_num < mockfile->num_targets) {
    curr = mockfile->head;

    while(curr != NULL && curr->target_id != rule_num) {
      curr = curr->next;
}
    /* curr not null = rule number was found */
    if(curr != NULL) {
      
      dependency = curr->target_line;      
      while(*dependency != NULL) {
	num_depends++; /* increment number of dependencies */
	dependency++; /* move pointer to next word */
      }
    }
  }
  return num_depends;
}

/* GET_DEPENDENCY************************************************************ */
char *get_dependency(Mockfile *const mockfile, int rule_num,
		       int dependency_num) {
  struct Target *curr;
  char **pointer;
  int dep_num = 0;
  /* printf("get_dependency\n"); */
  
  if(mockfile != NULL && rule_num >= 0 && dependency_num >= 0) {
    if(rule_num == 0 || rule_num < mockfile->num_targets) {

      curr = mockfile->head;
      while(curr != NULL && curr->target_id != rule_num) {
	curr = curr->next;
      }
      
      if (curr != NULL) {
	pointer = curr->target_line;
       
	pointer++; /* bypass target */
	while(*pointer != NULL) {
	  
	  if(dep_num == dependency_num) {
	    return *pointer;
	  }
	  pointer++;
	  dep_num++;
	}
      }
    }
  }
  return NULL;
}
  
/* EXISTS******************************************************************** */
int exists(const char filename[]) {
  struct stat buffer;
  /* printf("exists\n"); */
  errno = 0;

  if(filename != NULL) {
    
    if(stat(filename, &buffer) == -1 && errno == ENOENT)
      return 0; /* file does not exist */
    else return 1; /* file exists and was found */
  }
  return 0;
}

/* IS_OLDER****************************************************************** */
int is_older(const char filename[], const char filename2[]) {
  struct stat buffer, buffer2;
  /* printf("is_older\n"); */

  if (filename != NULL && filename2 != NULL) {
      if(stat(filename, &buffer) == 0 && stat(filename2, &buffer2) == 0) {
	if(buffer.st_mtime < buffer2.st_mtime)
	  return 1;
      
      }
  }
  return 0;
}

/* DO_ACTION***************************************************************** */
int do_action(Mockfile *const mockfile, int rule_num) {

  struct Target *curr;
  pid_t childpid;
  int status;
  /* printf("do_action\n"); */
  
  if(mockfile != NULL && rule_num < mockfile->num_targets) {
    childpid = safe_fork();

    curr = mockfile->head;
    while(curr != NULL && curr->target_id != rule_num) {
      curr = curr->next;
    }
    /* if it's the parent, then wait for the child to finish */
    if(childpid > 0) {
      wait(&status);

      if(WIFEXITED(status) && WEXITSTATUS(status) == 0)
	return status;
    }
    /* if the child, exec program and use action_line for the args */
    else if(childpid == 0) {
      
      if(curr != NULL)
	execvp(curr->action_line[0], curr->action_line);
    }
  }
  return -1;
}

/* CLEAR_MOCKFILE************************************************************ */
void clear_mockfile(Mockfile **const mockfile) {

  /* printf("clear_mockfile\n"); */
  if (mockfile != NULL && *mockfile != NULL) {
    destroy_targets((*mockfile)->head);
  }
  free((*mockfile)->name);
  free(*mockfile);
  *mockfile = NULL;
}

/* DESTROY TARGETS********************************************************** */
void destroy_targets(Target *curr) {

  char **target_temp, **action_temp;
  if(curr->next != NULL)
    destroy_targets(curr->next);

  /* free each element in target line */
  target_temp = curr->target_line;
  while (*target_temp != NULL) {
    free(*target_temp);
    target_temp++;
  }
  free(curr->target_line);

  /* free each element in action line */
  action_temp = curr->action_line;
  while (*action_temp != NULL) {
    free(*action_temp);
    action_temp++;
  }
  free(curr->action_line);
  free(curr); /* free the current target */
}

