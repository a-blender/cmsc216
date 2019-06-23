/* USER INTERFACE by Anna Blendermann, ablender, 114474025 */

/* this code functions as the user interface for my small document manager */
/* system, which loads data to/from documents and uses the functions from */
/* document.c to manipulate the lines and paragraphs */

/* the user calls this interface in one of two ways: */
/* 1. user_interface or 2. user_interface <filename> */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <ctype.h>
#include "document.h"

char *remove_quotes(char *command, char *result);
int validate_command(Document *doc, char *command);

/* RUN ADD PARAGRAPH AFTER************************************************* */
/* adds a paragraph to the document (tested) */
int run_add_paragraph_after(Document *doc, char *command) {
   char name[MAX_STR_SIZE + 1], extra[MAX_STR_SIZE + 1];
   int num_values, num;

   num_values = sscanf(command, "%s%d%s", name, &num, extra);
   if (num_values == 2 && num >= 0) {
      
      if (add_paragraph_after(doc, num) == FAILURE) {
	 printf("add_paragraph_after failed\n");
      }
      return SUCCESS;
   }
   return FAILURE;
}

/* RUN ADD LINE AFTER****************************************************** */
/* adds a line after the line with the specified line number (tested) */
int run_add_line_after(Document *doc, char *command) {
   char name[MAX_STR_SIZE + 1], line[MAX_STR_SIZE + 1];
   char buffer[MAX_STR_SIZE + 1];
   int num_values, num1, num2;

   num_values = sscanf(command, "%s%d%d%s", name, &num1, &num2, buffer);
   if (num_values == 4 && num1 > 0 && num2 >= 0) {

      if (strchr(command, '*') != NULL) {
	 strcpy(line, strchr(command, '*') + 1);
	 
	 if (add_line_after(doc, num1, num2, line) == FAILURE) {
	    printf("add_line_after failed\n");
	 }
	 return SUCCESS;
      }
   }
   return FAILURE;
}

/* RUN PRINT DOCUMENT****************************************************** */
/* this command prints the document information (tested) */
int run_print_document(Document *doc, char *command) {
   char name[MAX_STR_SIZE + 1], buffer[MAX_STR_SIZE + 1];
   int num_values;

   num_values = sscanf(command, "%s%s", name, buffer);
   if (num_values == 1) {

      if (print_document(doc) == FAILURE) {
	 printf("print_document failed\n");
      }
      return SUCCESS;
   }
   return FAILURE;
}

/* RUN APPEND LINE ******************************************************** */
/* appends a line to the specified paragraph (tested) */
int run_append_line (Document *doc, char *command) {
   char name[MAX_STR_SIZE + 1], line[MAX_STR_SIZE + 1];
   char buffer[MAX_STR_SIZE + 1];
   int num_values, num;

   num_values = sscanf(command, "%s%d%s", name, &num, buffer);
   if (num_values == 3 && num > 0) {

      if (strchr(command, '*') != NULL) {
	 strcpy(line, strchr(command, '*') + 1);
	 
	 if (append_line(doc, num, line) == FAILURE) {
	    printf("append_line failed\n");
	 }
	 return SUCCESS;
      }
   }
   return FAILURE;
}

/* RUN REMOVE LINE******************************************************** */
/* removes the specified line from the paragraph (tested) */
int run_remove_line(Document *doc, char *command) {
   char name[MAX_STR_SIZE + 1], buffer[MAX_STR_SIZE + 1];
   int num_values, num1, num2;

   num_values = sscanf(command, "%s%d%d%s", name, &num1, &num2, buffer);
   if (num_values == 3 && num1 > 0 && num2 > 0) {

      if (remove_line(doc, num1, num2) == FAILURE) {
	 printf("remove_line failed\n");
      }
      return SUCCESS;
   }
   return FAILURE;
}

/* RUN LOAD FILE********************************************************** */
/* loads the specified file into the current document (tested) */
int run_load_file(Document *doc, char *command) {
   char name[MAX_STR_SIZE + 1], file[MAX_STR_SIZE + 1];
   char buffer[MAX_STR_SIZE + 1];
   int num_values;

   num_values = sscanf(command, "%s%s%s", name, file, buffer);
   if (num_values == 2) {
      
      if (load_file(doc, file) == FAILURE) {
	 printf("load_file failed\n");
      }
      return SUCCESS;
   }
   return FAILURE;
}

/* RUN REPLACE TEXT******************************************************* */
/* replaces the string "target" with "replacement" (tested) */
int run_replace_text(Document *doc, char *command) {
   char name[MAX_STR_SIZE + 1], *str1, *str2, *str3, *str4;
   char target[MAX_STR_SIZE + 1], replace[MAX_STR_SIZE + 1];   
   char temp1[MAX_STR_SIZE + 1], temp2[MAX_STR_SIZE + 1];   
   int num_values;

   num_values = sscanf(command, "%s%s%s", name, temp1, temp2);
   str1 = strstr(command, "\"");

   /* get pointers to all four quote locations */
   if (num_values == 3 && str1 != NULL) {
      str2 = strstr(str1 + 1, "\"");
      
      if (str2 != NULL) {
	 str3 = strstr(str2 + 1, "\"");
	 
	 if (str3 != NULL) {
	    str4 = strstr(str3 + 1, "\"");

	    if (str4 != NULL) {
	       /* isolate "target," and "replace" using pointer subs */ 
	       strncpy(target, str1 + 1, str2 - str1);
	       target[str2 - (str1 + 1)] = '\0';
	       
	       strncpy(replace, str3 + 1, str4 - str3);
	       replace[str4 - (str3 + 1)] = '\0';
	       	       		  		
	       if (replace_text(doc, target, replace) == FAILURE) {
		  printf("remove_line failed\n");	 
	       }	       
	       return SUCCESS;	       	      
	    }
	 }	 
      }
   }/* end of checking str pointers */
   return FAILURE;
}

/* RUN HIGHLIGHT TEXT***************************************************** */
/* highlights the string "target" (tested) */
int run_highlight_text(Document *doc, char *command) {
   char name[MAX_STR_SIZE + 1], target[MAX_STR_SIZE + 1];
   char temp[MAX_STR_SIZE + 1], *str, *result;
   int num_values;

   num_values = sscanf(command, "%s%s", name, temp);
   str = strstr(command, "\"");
   
   if (num_values == 2 && str != NULL) {
      
      if ((result = remove_quotes(str, target)) != NULL) {
	 highlight_text(doc, result);      
	 return SUCCESS;
      }
   }   
   return FAILURE;
}

/* RUN REMOVE TEXT********************************************************* */
/* removes the string "target" (tested) */
int run_remove_text(Document *doc, char *command) {
   char name[MAX_STR_SIZE + 1], target[MAX_STR_SIZE + 1];
   char temp[MAX_STR_SIZE + 1], *str, *result;
   int num_values;
   
   num_values = sscanf(command, "%s%s", name, temp);
   str = strstr(command, "\"");
   
   if (num_values == 2 && str != NULL) {

      if ((result = remove_quotes(str, target)) != NULL) {
	 remove_text(doc, result);
	 return SUCCESS;
      }
   }
   return FAILURE;
}

/* RUN SAVE DOCUMENT****************************************************** */
/* saves the current document to the specified file (tested) */
int run_save_document(Document *doc, char *command) {
   char name[MAX_STR_SIZE + 1], file[MAX_STR_SIZE + 1];
   char buffer[MAX_STR_SIZE + 1];
   int num_values;

   num_values = sscanf(command, "%s%s%s", name, file, buffer);
   if (num_values == 2) {
    
      if (save_document(doc, file) == FAILURE) {
	 printf("save_document failed\n");
      }      
      return SUCCESS;
   }
   return FAILURE;
}

/* RUN RESET DOCUMENT****************************************************** */
/* resets the current document (tested) */		     
int run_reset_document(Document *doc, char *command) {
   char name[MAX_STR_SIZE + 1], buffer[MAX_STR_SIZE + 1];
   int num_values;

   num_values = sscanf(command, "%s%s", name, buffer);
   if (num_values == 1) {
      reset_document(doc);
      return SUCCESS;
   }
   return FAILURE;
}

/* REMOVE QUOTES********************************************************** */
/* helper function that removes one pair of quotes from command */
char *remove_quotes(char *command, char *result) {
   char *str1, *str2;
   
   str1 = strstr(command, "\"");   
   if (str1 != NULL) {
      str2 = strstr(str1 + 1, "\"");

      if (str2 != NULL) {
	 strncpy(result, str1 + 1, str2 - str1);
	 result[str2 - (str1 + 1)] = '\0';

	 return result;
      }
   }
   return NULL;
}

/* VALIDATE COMMAND******************************************************** */
/* this function searches for valid commands within an input string */
int validate_command(Document *doc, char *command) {
   int status = FAILURE;
   
   /* 1. find - search for command within "command" using strstr() */
   /* 2. validate - attempt to run command and return success/failure */
   if (strstr(command, "add_paragraph_after") != NULL) {
      if (!run_add_paragraph_after(doc, command)) {
	 status = SUCCESS;
      }
   }
   else if (strstr(command, "add_line_after") != NULL) {
      if (!run_add_line_after(doc, command)) {
	 status = SUCCESS;
      }
   }
   else if (strstr(command, "print_document") != NULL) {
      if (!run_print_document(doc, command)) {
	 status = SUCCESS;
      }
   }
   else if (strstr(command, "append_line") != NULL) {
      if (!run_append_line(doc, command)) {
	 status = SUCCESS;
      }
   }   
   else if (strstr(command, "remove_line") != NULL) {
      if (!run_remove_line(doc, command)) {
	 status = SUCCESS;
      }
   }
   else if (strstr(command, "load_file") != NULL) {
      if (!run_load_file(doc, command)) {
	 status = SUCCESS;
      }
   }
   else if (strstr(command, "replace_text") != NULL) {
      if (!run_replace_text(doc, command)) {
	 status = SUCCESS;
      }
   }
   else if (strstr(command, "highlight_text") != NULL) {
      if (!run_highlight_text(doc, command)) {
	 status = SUCCESS;
      }
   }
   else if (strstr(command, "remove_text") != NULL) {
      if (!run_remove_text(doc, command)) {
	 status = SUCCESS;
      }
   }
   else if (strstr(command, "save_document") != NULL) {
      if (!run_save_document(doc, command)) {
	 status = SUCCESS;
      }
   }
   else if (strstr(command, "reset_document") != NULL) {
      if (!run_reset_document(doc, command)) {
	 status = SUCCESS;
      }
   }

   /* if status = FAILURE, then the command failed */
   if (status == FAILURE) {
      printf("Invalid Command\n");
   }
   return status;
}

/* MAIN METHOD************************************************************** */
int main(int argc, char *argv[]) {
   Document doc;
   const char *doc_name = "main_document";
   FILE *input_file;
   
   char line[MAX_STR_SIZE + 1], line1, line2[MAX_STR_SIZE + 1];
   int num_values = 0;

   /* initialize "main_document" for stdin/file operations */
   if (init_document(&doc, doc_name) == FAILURE) {
      printf("Initialization failed\n");
   }
   else {
      /* 1. one arg = read from standard input */
      if (argc == 1) {
	 input_file = stdin;
	 
	 /* scan the first line of user input */
	 printf("> ");
	 fgets(line, MAX_STR_SIZE + 1, stdin);
      
	 /* scan input until user enters "quit" or "exit" */
	 while (strcmp(line, "quit\n") && strcmp(line, "exit\n")) {
	    
	    sscanf(line, " %c%s", &line1, line2); /* parse for comments */
	    strtok(line, "\n"); /* remove the annoying newline */
	    
	    if (strcmp(line, "\n") != 0 && line1 != '#') {
	       validate_command(&doc, line);
	    }
	    printf("> ");
	    fgets(line, MAX_STR_SIZE + 1, stdin);
	 }
      }
      /* 2. two args = read from file provided by the user */      
      else if (argc == 2) {
	 
	 /* input file not null -> process commands from the file */
	 if ((input_file = fopen(argv[1], "r")) == NULL) {
	    fprintf(stderr, "%s cannot be opened.\n", argv[1]);
	    exit(EX_OSERR);
	 }
	 else {	    
	    while (fgets(line, MAX_STR_SIZE + 1, input_file)) {
	       
	       if (strcmp(line, "quit\n") && strcmp(line, "exit\n")) {
		  
		  num_values = sscanf(line, " %c%s", &line1, line2);
		  strtok(line, "\n"); /* remove the newline */
		  
		  if (num_values > 0 && line1 != '#') {
		     validate_command(&doc, line);
		  }
	       }
	    } /* end of fgets loop */
	 }
      }
      /* 3. else = invalid number of arguments */
      else {
	 fprintf(stderr, "Usage: user_interface\n");
	 fprintf(stderr, "Usage: user_interface <filename>\n");
	 exit(EX_USAGE);
      }
   } /* end of checking init_document */ 
   fclose(input_file);
   exit(EXIT_SUCCESS);
}
