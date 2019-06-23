/* This file and derivatives (C) 2012 Neil Spring and the
 * University of Maryland.  Any use, copying, or
 * distribution without permission is prohibited.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "executor.h"
#include "lexer.h"

#define MAX_LINE 1024

/* wanted to add cwd to the prompt, but doing so will
   bork expectations for test output. for next time:
   maybe ansi brightness. */
int main() {
  if( isatty(STDIN_FILENO) ) { 
    /* this is the code used for an interactive shell; it prints a prompt, just 
       executes the commands on each line */
    char * buffer;
    while((buffer = readline ("d8sh% "))) { 
      if(buffer[0] == 0) { continue; }

      add_history(buffer);
      
      yy_scan_string(buffer); /* set up bison to read from memory */
      /* yyparse will invoke execute() on the parsed tree. */
      /* execute should block until we're ready for the next prompt */
      if (yyparse() != 0) {
        fprintf(stderr, "Problem with command: '%s'\n", buffer);
        continue; /* try again if parse error */
      }
      
      /* readline allocates the buffer, which must be freed. */
      free(buffer);
    }
  } else { 
    /* this is the code used when testing; prints no prompt, just 
       executes the commands on each line */
    char buffer[MAX_LINE];
    while( fgets(buffer, MAX_LINE, stdin) != NULL) { /* exit on eof */
      yy_scan_string(buffer); /* set up bison to read from memory */
      if (yyparse() != 0) {
        fprintf(stderr, "Problem with command: '%s'\n", buffer);
        continue; /* try again if parse error */
      }
    }
  }
  return(0);
}

/* required by bison */
void yyerror (const char *s) {
  fprintf (stderr, "Parse error: %s\n", s);
}
