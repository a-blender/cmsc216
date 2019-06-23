/* Anna Blendermann, ablender, 114474025, 0104 */
/* I pledge on my honor that I have not given or received any unauthorized */
/* assistance on this programming assignment */

/* Fm-sim.c simulates a UNIX filesystem with five simple commands */
/* This program uses the Fm-sim and Directory data structures to build the */
/* working filesystem that uses the commands: touch, mkdir, cd, ls, pwd */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fs-sim.h" /* includes fs-sim-datastructure.h */

void print_directory(Fs_sim *files, const char arg[]);
char * list_contains(Fs_sim *files, const char arg[]);
void pwd_helper(Fs_comp *curr, Fs_comp *root);

void rmfs_helper(Fs_comp *curr);
void remove_element(Fs_comp *prev, Fs_comp *curr, const char arg[]);


/* MKFS() creates an empty filesystem with a root directory */
/* pointers for both the root and current directory are initialized */
void mkfs(Fs_sim *files) {

  /* allocate memory for the root and name */
  files->root = malloc(sizeof(Fs_comp));
  files->root->type = malloc(sizeof(char)+1);
  files->root->name = malloc(sizeof(char)+1);

  /* initialize the root directory parameters */
  strcpy(files->root->type, "D");
  strcpy(files->root->name, "/");
  files->root->sub_dir = NULL;
  files->root->parent_dir = NULL;
  files->root->next = NULL;
  
  /* initialize the current directory to root */
  files->curr_dir = files->root;
}


/* TOUCH() creates a file in the current location */
/* returns zero for invalid parameters or nonexistent file name */
int touch(Fs_sim *files, const char arg[]) {
  
  Fs_comp *prev, *curr; /* pointer to iterate through list */
  Fs_comp *file; /* pointer to the new file */
  
  /* check that mkfs() has already been called on *files */
  if (files != NULL && files->curr_dir != NULL) {

    /* check that the arg[] parameter is completely valid = return 1 */
    if (arg != NULL && strcmp(arg, ".") != 0 && strcmp(arg, "..") != 0
	&&  strcmp(arg, "/") != 0) {

      /* arg[] is empty or contains (/) = return 0 */
      if (strcmp(arg, "") != 0 && strchr(arg, '/') == NULL) {

	/* allocate memory for the file and the filename */
	file = malloc(sizeof(Fs_comp));
	file->type = malloc(sizeof(char)+1);
	file->name = malloc(sizeof(char)*(strlen(arg)+1));
	
	/* initialize struct members and pointers */
	strcpy(file->type, "F");
	strcpy(file->name, arg);
	file->sub_dir = NULL;
	file->parent_dir = files->curr_dir;

	/* set the curr_dir pointer to the subdirectory list */
	curr = files->curr_dir->sub_dir;
	
	/* check for empty subdirectory and if so, add new file */
	if (curr == NULL) {
	  files->curr_dir->sub_dir = file;
	  file->next = NULL;
	}
	/* subdirectory not empty BUT file < first element */
	else if (curr != NULL && strcmp(curr->name, arg) > 0) {
	  files->curr_dir->sub_dir = file;
	  file->next = curr;
	}
      
	/* subdirectory list already contains files!! */
	else {

	  /* file found and already exists = return 1 */
	  if (list_contains(files, arg) != 0)
	    return 1;
	  
	  /* else, iterate until you find a file greater than target */
	  while (curr != NULL && strcmp(curr->name, arg) < 0) {
	    prev = curr;
	    curr = curr->next;
	  }
      
	  /* curr is null = add new file to the end of the list */
	  if (curr == NULL) {
	    prev->next = file;
	    file->next = NULL;
	  }
	  /* curr is not null = add new file to middle of the list */
	  else {
	    prev->next = file;
	    file->next = curr;
	  }
	}
      }
      else return 0; /* arg[] was empty or contained (/) */ 
    }
  }
  return 1; /* function was successful */
}


/* MKDIR() creates a directory in the current location */
/* returns zero for invalid parameters or nonexistent directory */ 
int mkdir(Fs_sim *files, const char arg[]) {

  Fs_comp *prev, *curr; /* pointers to iterate through the list */
  Fs_comp *dir; /* pointer to the new directory */
  
  /* check that mkfs() has already been called on *files */
  if (files != NULL && files->curr_dir != NULL) {

    /* check that the arg[] parameter is completely valid */
    if (arg != NULL && strcmp(arg, "") != 0 && strcmp(arg, ".") != 0
	&& strcmp(arg, "..") != 0 && strcmp(arg, "/") != 0
	&& strchr(arg, '/') == NULL) {

      /* allocate memory for the new directory */
      dir = malloc(sizeof(Fs_comp));
      dir->type = malloc(sizeof(char)+1);
      dir->name = malloc(sizeof(char)*(strlen(arg)+1));

      /* initialize members of the new directory */
      strcpy(dir->type, "D");
      strcpy(dir->name, arg);
      dir->sub_dir = NULL;
      dir->parent_dir = files->curr_dir;

      /* set current directory pointer to subdirectory list */
      curr = files->curr_dir->sub_dir;

      /* check for empty subdirectory and if so, add new dir */
      if (curr == NULL) {
	files->curr_dir->sub_dir = dir;
	dir->next = NULL;
      }
      /* subdirectory not empty BUT dir > first element */
      else if (curr != NULL && strcmp(curr->name, arg) > 0) {
	files->curr_dir->sub_dir = dir;
	dir->next = curr;;
      }
      
      /* subdirectory list already contains things!! */
      else {

	/* subdirectory found and exists = return 1 */
	if (list_contains(files, arg) != 0)
	  return 0;
	
	/* else, iterate until you find a directory greater than target */
	while (curr != NULL && strcmp(curr->name, arg) < 0) {
	  prev = curr;
	  curr = curr->next;
	}
	
	/* curr equals null = add directory to the end */
	if (curr == NULL) {
	  prev->next = dir;
	  dir->next = NULL;
	}
	/* curr is not null = add directory to the middle */
	else {
	  prev->next = dir;
	  dir->next = curr;
	}
      }
      return 1; /* function was successful */
    }
  }
  return 0;
}


/* CD() moves between filesystem levels */
/* returns zero for invalid parameters or no dir to move to */
int cd(Fs_sim *files, const char arg[]) {

  /* check that mkfs() has already been called on *files */
  if (files != NULL && files->curr_dir != NULL && arg != NULL) {

    Fs_comp *tmp; /* pointer to iterate through subdirectory */

      /* arg equals (.) = function succeeds with no action */
      if (strcmp(arg, ".") == 0)
	return 1;

      /* arg equals (..) = function moves to parent directory */
      else if (strcmp(arg, "..") == 0) {
	/* make sure curr_dir != root, root has no parent_dir */
	if (files->curr_dir != files->root) {
	  files->curr_dir = files->curr_dir->parent_dir;
	  return 1;
	}
      }
      
      /* arg equals (/) = function moves to root directory */
      else if (strcmp(arg, "/") == 0 || strcmp(arg, "") == 0) {
	files->curr_dir = files->root;
	return 1;
      }

      /* arg is a string = function checks if the str exists */
      /* subdirectory exists = function moves curr_dir to sub_dir */
      else if (strchr(arg, '/') == NULL) {	
	for (tmp = files->curr_dir->sub_dir; tmp != NULL; tmp = tmp->next) {
	  
	  if (strcmp(tmp->name, arg) == 0) {
	    
	    if (strcmp(tmp->type, "D") == 0) {
	      files->curr_dir = tmp;
	      return 1;
	    }
	  }
	}
	return 0; /* file/directory was not found */
      }
      else return 0; /* arg contains (/) in the name */
  }
  return 0; /* cd() function has failed */
}


/* LS() prints information from the current location */
/* prints file names regularly and directories with an extra (/) */
/* returns zero for invalid parameters and incorrect location */
int ls(Fs_sim *files, const char arg[]) {
  
  /* check that mfks() has already been called on *files */  
  if (files != NULL && files->curr_dir != NULL && arg != NULL) {
    
    /* 1. arg equals (.) or empty = print current directory list */
    if (strcmp(arg, ".") == 0 || strcmp(arg, "") == 0) {
      print_directory(files, ".");
    }

    /* 2. arg equals (..) = print parent directory list */
    else if (strcmp(arg, "..") == 0) {
      cd(files, "..");
      print_directory(files, ".");
    }

    /* 3. arg equals (/) = print root directory list */
    else if (strcmp(arg, "/") == 0) {
      files->curr_dir = files->root;
      print_directory(files, ".");
    }

    /* arg equals either file/directory, so check existence */
    /* make sure that the file/directory name doesn't contain (/) */
    else if (strchr(arg, '/') == NULL) {
      
      /* check if target name exists in the curr_dir */
      if(list_contains(files,arg) != 0) {

	/* file found = print the filename */
	if (strcmp(list_contains(files, arg), "F") == 0)
	  printf("%s/n", arg);

	/* directory found = cd into subdirectory and print dir */
	else if (strcmp(list_contains(files, arg), "D") == 0) {
	  cd(files, arg);
	  print_directory(files, ".");
	  cd(files, "..");
	}
      }
      else return 0; /* arg name doesn't exist */
    }
    else return 0; /* arg contains an (/) in the name */
    
    return 1; /* files/dirs were successfully printed */
  }
  return 0; /* nothing printed - errors found */
} /* end of ls() function */
	 

/* PRINT DIRECTORY - Helper method for ls() */
/* prints file and directory names from the current location */
/* returns void and only accepts the (.) parameter for arg */
void print_directory(Fs_sim *files, const char arg[]) {

  Fs_comp *tmp; /* pointer to iterate through files/dirs */
  /* check to make sure we're printing from curr_dir */
  if (strcmp(arg, ".") == 0) {
   
    /* print all files and directories in curr_dir */
    for(tmp = files->curr_dir->sub_dir; tmp != NULL; tmp = tmp->next) {

      /* file found = print the filename only */
      if (strcmp(tmp->type, "F") == 0) {
	  printf("%s\n", tmp->name);
      }
      /* directory found = print the dir name with slash */
      else if (strcmp(tmp->type, "D") == 0) {
	  printf("%s/\n", tmp->name);
      }
    }
  }
}


/* LIST CONTAINS - Helper method for ls() */
/* checks if the current location contains a specific name */
/* returns a char pointer for the "type" of struct found */
char * list_contains(Fs_sim *files, const char arg[]) {

  Fs_comp *tmp; /* pointer to iterate through files/dirs */
  /* check to make sure we're searching the curr_dir */
  if (arg != NULL && strcmp(arg, "") != 0) {

    /* iterate through curr_dir and search for target */
    for (tmp = files->curr_dir->sub_dir; tmp != NULL; tmp = tmp->next) {
      
      if (strcmp(tmp->name, arg) == 0) {
	return tmp->type; /* file/dir found, return type */
      }
    }
  }
  return 0; /* arg doesn't exist in curr_dir */
}


/* PWD() uses pwd_helper() to print the file path to curr_dir */
/* prints "(/) + directory" for each level, except the last one */
void pwd(Fs_sim *files) {

  /* check that mkfs() hasn't already been called on *files */
  if (files->curr_dir != NULL) {

    /* print (/) if the current location is the root */
    if (strcmp(files->curr_dir->name, "/") == 0)
      printf("/");
    else pwd_helper(files->curr_dir, files->root);
  }
  printf("\n"); /* print last newline */
}


/* PWD_HELPER() recursively prints the path from root to curr_dir */
/* takes two struct components, current directory and root */
void pwd_helper(Fs_comp *curr, Fs_comp *root) {

  /* base case = current tries to access root parent */
  if (curr == root)
    return;
  else pwd_helper(curr->parent_dir, root);

  /* print each directory name recursively */
  printf("/");
  printf("%s", curr->name);
}


/* RMFS() deallocates all memory from the existing fileystem */
/* takes one argument for the filesystem to remove */
void rmfs(Fs_sim *files) {

  /* check that mkfs() hasn't already been called on *files */
  if (files != NULL && files->curr_dir != NULL)
    rmfs_helper(files->root);
}

/* RMFS_HELPER() deallocates all files/dirs below a certain point */
/* takes one arg: curr = root for rmfs(), curr = target for rm() */
void rmfs_helper(Fs_comp *curr) {

  /* check whether curr_dir equals null */
  if (curr == NULL)
    return;

  /* keep iterating through the filesystem */
  else {
    rmfs_helper(curr->sub_dir);
    rmfs_helper(curr->next);
  }
  /* unwind and deallocate all files/directories */
  free(curr->name);
  free(curr->type);
  free(curr);
}


/* RM() removes a file/directory from the current filesystem */
/* takes two args: files = current filesystem, arg = file/dir to remove */
int rm(Fs_sim *files, const char arg[]) {

  /* check that mkfs() hasn't been called and params != null */
  if (files != NULL && files->curr_dir != NULL && arg != NULL) {

    /* check that the arg[] parameter is valid */
    if (strcmp(arg, ".") != 0 && strcmp(arg, "") != 0) {

      /* arg equals (/) = delete entire filesystem */
      if(strcmp(arg, "/") == 0) {
	rmfs_helper(files->root);
	return 1;
      }

      /* arg equals file/dir = delete file OR subdirectory */
      else if (strcmp(arg, "/") != 0 && strchr(arg, '/') == NULL) {

	/* check that the curr_dir contains target arg */
	if (list_contains(files, arg) != 0) {

	  /* use helper function to remove file/subdirectory */
	  remove_element(NULL, files->curr_dir->sub_dir, arg);
	  return 1;
	}
      }
    }
  }
  return 0;
}

/* REMOVE ELEMENT() removes the target file or subdirectory */
/* takes three args: prev & curr pointers, arg = file/dir to remove */
void remove_element(Fs_comp *prev, Fs_comp *curr, const char arg[]) {

  /* base case = curr_dir equals null */
  if(curr == NULL)
    return;

  /* arg found = check if target is file or directory */
  if (strcmp(curr->name, arg) == 0) {

    /* first element found = deallocate front of list */
    if (prev == NULL) {
      curr->parent_dir->sub_dir = curr->next;
      free(curr);
    }
    /* file found = deallocate the file */
    else if(strcmp(curr->type, "F") == 0) {
      prev->next = curr->next;
      free(curr);
    }
    /* directory found = deallocate whole subdirectory */
    else if (strcmp(curr->type, "D") == 0) {
      prev->next = curr->next;

      /* check if directory has sub-contents */
      if (curr->sub_dir == NULL)
	free(curr);
      else rmfs_helper(curr);
    }
  }
  
  /* continue iterating through the filesystem */ 
  else
    remove_element(curr, curr->next, arg);
}
