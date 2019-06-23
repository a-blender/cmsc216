/* EXECUTOR.C by Anna Blendermann, ablender, 114474025 */
/* this program executes commands from a tree structure with nodes */
/* Node: argv[] array of command+args, input/output redirection files */

#define MAX_LINE_SIZE 1024
#define FILE_PERMISSIONS 0664
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sysexits.h>
#include <fcntl.h>
#include <err.h>
#include "executor.h"
#include "command.h"

static int recurse_tree(struct tree *t, int input_fd, int output_fd);

/* EXECUTE FUNCTION********************************************************* */
/* the execute function does two things: checks that the tree isn't null, */
/* and then calls recurse_tree() to recursively traverse the tree */
int execute(struct tree *t) {
   
   /* case 1 = check that the tree isn't null */
   if (t != NULL) {
      /* call the auxilary function to traverse the tree */
      return recurse_tree(t, -1, -1);
   }
   return 0;
}

/* RECURSE_TREE FUNCTION**************************************************** */
/* the recurse_tree() function recursively executes commands in the tree */
/* Node options: NONE (command), AND (&&), PIPE (|), or SUBSHELL */
static int recurse_tree(struct tree *t, int input_fd, int output_fd) {   
   pid_t process_id;
   int status, status2;
   
   /* 1. NONE = leaf node with a command and argv[] array */
   /* handles redirection and forks a process to execvp the command */
   if (t->conjunction == NONE) {
	 
      /* "cd" command = execute chdir() with argv[] array */
      if (!strcmp(t->argv[0], "cd")) {	    
	 chdir(t->argv[1]);
      }
      /* "exit" command = terminate the entire program */
      else if (!strcmp(t->argv[0], "exit")) {
	 exit(0);
      }
      /* other command = use execvp to execute command */
      else {	    
	 if ((process_id = fork()) < 0) {	   
	    err(EX_OSERR, "fork error");
	 }
	 else {
	    /* parent process found -> wait for child, then return */
	    if (process_id != 0) {
	       wait(&status);
	       return status;
	    }	       
	    /* child process found -> file rediction, execute command */
	    if (process_id == 0) {		  
	       /* input file found -> redirect stdin to that file */
	       if (t->input) {
		  if ((input_fd = open(t->input, O_RDONLY)) < 0) {
		     err(EX_OSERR, "Input file couldn't be opened.\n");     
		  }
		  if (dup2(input_fd, STDIN_FILENO) < 0) {
		     err(EX_OSERR, "dup2 input failed.\n");
		  }		     
		  close(input_fd);
	       }       	       
	       /* output file found -> redirect stdout to that file */
	       if (t->output) {
		  if ((output_fd = open(t->output, O_WRONLY | O_CREAT | O_TRUNC, FILE_PERMISSIONS)) < 0) {
		     err(EX_OSERR, "Output file couldn't be opened.\n");
		  }		     
		  if (dup2(output_fd, STDOUT_FILENO) < 0) {
		     err(EX_OSERR, "dup2 output failed.\n");
		  }		     
		  close(output_fd);		  
	       }
	       /* execute the command with argv[] array */
	       execvp(t->argv[0], t->argv);
	       fprintf(stderr, "Failed to execute %s\n", t->argv[0]);    
	       exit(-1);	    
	    } /* exiting the child process */
	 }
      }
   } /* end of NONE conjunction */
      
   /* 2. AND = internal node with two children */
   /* handles redirection and then executes the left and right nodes */
   else if (t->conjunction == AND) {

      /* checks for and handles input redirection */
      if (t->input) {
	 if ((input_fd = open(t->input, O_RDONLY) < 0)) {
	    err(EX_OSERR, "Input file couldn't be opened.\n");
	 }
      }
      /* checks for and handles output redirection */
      if (t->output) {
	 if ((output_fd = open(t->output, O_WRONLY | O_CREAT | O_TRUNC, FILE_PERMISSIONS)) < 0) {
	    err(EX_OSERR, "Output file couldn't be opened.\n");
	 }
      }
      /* executes left node, then depending on status, the right node */
      status2 = recurse_tree(t->left, input_fd, output_fd);  
      if (status2 == 0) {	    
	 recurse_tree(t->right, input_fd, output_fd);
      }
   } /* end of the AND conjunction */
      
   /* 3. PIPE = internal node with two children */
   /* handles redirection and then creates a pipeline between nodes */
   else if (t->conjunction == PIPE) {	 
      int pipe_fd[2];	 	 
	 
      /* check that left child doesn't have output redirect */
      if (t->left->output) {
	 printf("Ambiguous output redirect.\n");	   
      }
      else {
	 /* check that right child doesn't have input redirect */
	 if (t->right->input) {
	    printf("Ambiguous input redirect.\n");
	 }
	 /* piping allowed -> redirect the children stdout/stdin */	    
	 else {	       
	    /* check for input/output redirection on the PIPE node */
	    if (t->input) {
	       if ((input_fd = open(t->input, O_RDONLY)) < 0) {
		  err(EX_OSERR, "PIPE - input file couldn't be opened\n");
	       }
	    }
	    if (t->output) {
	       if ((output_fd = open(t->output, O_WRONLY | O_CREAT | O_TRUNC, FILE_PERMISSIONS)) < 0) {
		  err(EX_OSERR, "PIPE - output file couldn't be opened\n");
	       }
	    }	       
	    /* create the pipe here and fork the process */
	    if (pipe(pipe_fd) < 0) {
	       err(EX_OSERR, "pipe error");
	    }	       
	    if ((process_id = fork()) < 0) {
	       err(EX_OSERR, "fork error");
	    }
	    /* child found = execute the left node (write) */
	    if (process_id == 0) {
	       close(pipe_fd[0]);
	       if (dup2(pipe_fd[1], STDOUT_FILENO) < 0) {
		  err(EX_OSERR, "dup2 error");
	       }
	       recurse_tree(t->left, input_fd, pipe_fd[1]);		  
	       close(pipe_fd[1]);
	       exit(0);
	    }
	    /* parent found = execute the right child */
	    if (process_id != 0) {
		  
	       close(pipe_fd[1]);		  
	       if (dup2(pipe_fd[0], STDIN_FILENO) < 0) {
		  err(EX_OSERR, "dup2 error");
	       }
	       recurse_tree(t->right, pipe_fd[0], output_fd);	  
	       close(pipe_fd[0]);
	       wait(NULL); /* wait for child */
	    }
	 } /* end of the else statement */	 	 	 
      } /* end of checking for right child input */
   } /* end of the pipe if-statement */
      
   /* 4. SUBSHELL = internal node with left child only */
   /* handles redirection and then creates a shell sub-process */
   else if (t->conjunction == SUBSHELL) {	 

      /* check if SUBSHELL has input/output redirection */
      if (t->input) {
	 if ((input_fd = open(t->input, O_RDONLY)) < 0) {
	    err(EX_OSERR, "SUBSHELL - input file couldn't be opened\n");
	 }
      }
      if (t->output) {
	 if ((output_fd = open(t->output, O_WRONLY | O_CREAT | O_TRUNC, FILE_PERMISSIONS)) < 0) {
	    err(EX_OSERR, "SUBSHELL - output file couldn't be opened\n");
	 }
      }	 
      /* fork the process and execute the left child */
      if ((process_id = fork()) < 0) {
	 err(EX_OSERR, "fork error");
      }
      else {
	 /* parent found = wait for child process(es) to finish */
	 if (process_id != 0) {
	    wait(NULL);
	 }
	 /* child found = recursively execute left child only */
	 if (process_id == 0) {
	    recurse_tree(t->left, input_fd, output_fd);
	    exit(0);
	 }
      }
   } /* end of subshell statement */   
   return 0;
} /* END OF THE RECURSE_TREE FUNCTION */


