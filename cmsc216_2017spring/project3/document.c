/* DOCUMENT by Anna Blendermann, 114474025, ablender */
/* this program allows the user to create and edit document structures */

/* function: uses Document and nested Paragraph structures to create a */
/* design for which paragraphs/lines can be added, maniplated, replaced, */
/* highlighted, removed, and printed for the user to view */
#include <stdio.h>
#include <string.h>
#include "document.h"

/* INIT DOCUMENT*********************************************************** */
/* initializes the document to be empty */
int init_document(Document *doc, const char *name) {

   if (doc != NULL && name != NULL && strlen(name) <= MAX_STR_SIZE) {
      strcpy(doc->name, name);
      return SUCCESS;
   }
   return FAILURE;
}

/* RESET DOCUMENT********************************************************** */
/* sets the number of paragraphs to zero */
int reset_document(Document *doc) {

   if (doc != NULL) {
      doc->number_of_paragraphs = 0;
      return SUCCESS;
   }
   return FAILURE;
}

/* PRINT DOCUMENT********************************************************** */
/* prints the doc name and number of paragraphs, followed by the paragraphs */
int print_document(Document *doc) {
   int x, y;
   
   if (doc != NULL) {
      printf("Document name: \"%s\"\n", doc->name);
      printf("Number of Paragraphs: %d\n", doc->number_of_paragraphs);

      /* iterate through each paragraph */
      for (x = 0; x < doc->number_of_paragraphs; x++) {

	 /* if paragraph not empty, print lines of that paragraph */
	 if (doc->paragraphs[x].number_of_lines > 0) {
	    
	    for (y = 0; y < doc->paragraphs[x].number_of_lines; y++) {
	       printf("%s\n", doc->paragraphs[x].lines[y]);
	    }
	    if (x < (doc->number_of_paragraphs - 1))
	       printf("\n");
	 }
      }
      return SUCCESS;
   }
   return FAILURE;
}

/* ADD PARAGRAPH AFTER****************************************************** */
/* adds a paragraph after the specified paragraph number (start = 1) */
int add_paragraph_after(Document *doc, int paragraph_number) {
   int x, start = 0, end = 0, num_paras = 0;
   
   if (doc != NULL) {

      num_paras = doc->number_of_paragraphs;
      if (num_paras < MAX_PARAGRAPHS && paragraph_number <= num_paras) {
	 
	 /* 1. insert paragraph at the beginning of the array */
	 if (paragraph_number == 0 && !num_paras) {
	    doc->paragraphs[0].number_of_lines = 0;
	 }
	 /* 2. insert paragraph at the end of the array */
	 else if (paragraph_number == doc->number_of_paragraphs) {
	    end = doc->number_of_paragraphs;
	    doc->paragraphs[end].number_of_lines = 0;
	 }
	 /* 3. insert paragraph in the middle of the array */
	 else {
	    start = doc->number_of_paragraphs;
	    for (x = start; x >= paragraph_number; x--) {
	       doc->paragraphs[x + 1] = doc->paragraphs[x];
	    }
	    /* insert element at position paragraph_number */
	    doc->paragraphs[paragraph_number].number_of_lines = 0;
	 }
	 (doc->number_of_paragraphs)++;	 
	 return SUCCESS;
      }
   }
   return FAILURE;
}

/* ADD LINE AFTER********************************************************** */
/* adds a new line after the line with the specified line number */
int add_line_after(Document *doc, int paragraph_number, int line_number, const char *new_line) {
   int y, num_lines = 0;
   char *pos, *line1, *line2;
   
   if (doc != NULL && new_line != NULL) {

      if (paragraph_number <= doc->number_of_paragraphs) {
	 
	 num_lines = doc->paragraphs[paragraph_number - 1].number_of_lines;
	 if (num_lines < MAX_PARAGRAPH_LINES && line_number <= num_lines) {
     
	    /* 1. insert line at the beginning of the array */
	    if (line_number == 0 && !num_lines) {
	       pos = doc->paragraphs[paragraph_number - 1].lines[0];
	       strcpy(pos, new_line);
	    }
	    /* 2. insert line at the end of the array */
	    else if (line_number == num_lines) {
	       pos = doc->paragraphs[paragraph_number - 1].lines[line_number];
	       strcpy(pos, new_line);
	    }
	    /* 3. insert line in the middle of the array */
	    else {
	       /* move line elements from x to x+1 */
	       for (y = num_lines; y >= line_number; y--) {
	      
		  line1 = doc->paragraphs[paragraph_number - 1].lines[y];
		  line2 = doc->paragraphs[paragraph_number - 1].lines[y+1];
		  strcpy(line2, line1);
	       }
	       /* add the new_line to "line_number" position */
	       pos = doc->paragraphs[paragraph_number - 1].lines[line_number];
	       strcpy(pos, new_line);
	    }
	    (doc->paragraphs[paragraph_number - 1].number_of_lines)++;
	    return SUCCESS;
	 }
      }
   }
   return FAILURE;
}

/* GET NUMBER LINES PARAGRAPH********************************************** */
/* returns the number of lines in a paragraph */
int get_number_lines_paragraph(Document *doc, int paragraph_number, int *number_of_lines) {
   int lines = 0;

   if (doc != NULL) {      
      if (paragraph_number <= doc->number_of_paragraphs) {	 
	 lines = doc->paragraphs[paragraph_number].number_of_lines;	 
	 *number_of_lines = lines;
	 return SUCCESS;
      }
   }
   return FAILURE;
}

/* APPEND LINE************************************************************ */
/* appends a line to a specified paragraph */
int append_line(Document *doc, int paragraph_number, const char *new_line) {
   int num_lines = 0, para_num = paragraph_number;
   
   if (doc != NULL && new_line != NULL) {

      num_lines = doc->paragraphs[para_num - 1].number_of_lines;
      if (para_num <= MAX_PARAGRAPHS && num_lines < MAX_PARAGRAPH_LINES) {

	 /* append line to paragraph using the add_line_after() function */
	 if (!add_line_after(doc, para_num, num_lines, new_line)) {
	    return SUCCESS;
	 }
      }
   }
   return FAILURE;
}

/* REMOVE LINE************************************************************* */
/* removes the specified line from the paragraph */
int remove_line(Document *doc, int paragraph_number, int line_number) {
   int x, y, num_lines = 0, para_num = paragraph_number;
   char *line, *line2;

   if (doc != NULL) {
      num_lines = doc->paragraphs[para_num - 1].number_of_lines;      
      if (para_num <= doc->number_of_paragraphs && line_number <= num_lines) {
	 
	 if (line_number < num_lines) {
	    /* 1. remove line from anywhere in the paragraph */
	    for (x = line_number - 1; x < num_lines - 1; x++) {

	       /* set variables "line" and "line2" for x and x+1 lines */
	       line = doc->paragraphs[para_num - 1].lines[x];
	       line2 = doc->paragraphs[para_num - 1].lines[x + 1];

	       /* overwrite line x by moving other lines down */
	       for (y = 0; y < MAX_STR_SIZE; y++) {
		  line[y] = line2[y];
	       }
	    }
	 }
	 (doc->paragraphs[para_num - 1].number_of_lines)--;
	 return SUCCESS;
      }
   }
   return FAILURE;
}

/* LOAD DOCUMENT*********************************************************** */
/* adds data_lines (num of lines) from the data array to the document */
int load_document(Document *doc, char data[][MAX_STR_SIZE + 1], int data_lines) {
   int x = 0;
   if (doc != NULL && data != NULL && data_lines) {
	 /* add preliminary paragragh because start = 1 */
	 add_paragraph_after(doc, doc->number_of_paragraphs);

	 /* add data lines, adding additional paragraphs where needed */
	 for (x = 0; x < data_lines; x++) {

	    if (strcmp(data[x], "") == 0) {	       
	       add_paragraph_after(doc, doc->number_of_paragraphs);
	       (doc->number_of_paragraphs)++;
	    }
	    else append_line(doc, doc->number_of_paragraphs, data[x]);
	 }
	 return SUCCESS;
   }
   return FAILURE;
}

/* REPLACE TEXT************************************************************ */
/* replaces the text "target" with "replacement" in the document */
int replace_text(Document *doc, const char *target, const char *replacement) {
   int x, y, num_lines = 0;
   char *current, temp[MAX_STR_SIZE + 1] = {0};

   if (doc != NULL && target != NULL && replacement != NULL) {

      /* replace "target" with "replacement" for every line */
      for (x = 0; x < doc->number_of_paragraphs; x++) {
	 num_lines = doc->paragraphs[x].number_of_lines;
	 
	 for (y = 0; y < num_lines; y++) {

	    current = strstr(doc->paragraphs[x].lines[y], target);
	    while (current != '\0') {
	       
	       /* replace the found "target" with "replacement" */
	       strcpy(temp, current);
	       strcpy(current, "");
	       strcat(current, replacement);
	       strcat(current + strlen(replacement), temp + strlen(target));
	       
	       /* move current to next instance of "target" */
	       current = strstr(current + strlen(target), target);	       
	    }
	 }
      } /* end of nested for loop */
      return SUCCESS;
   }
   return FAILURE;
}

/* HIGHLIGHT TEXT********************************************************** */
/* highlights the text associated with "target" in the docment */
int highlight_text(Document *doc, const char *target) {
   char result[MAX_STR_SIZE + 1] = "";
   
   if (doc != NULL && target != NULL) {

      /* add front and end brackets to target */
      strcat(result, HIGHLIGHT_START_STR);
      strcat(result, target);
      strcat(result, HIGHLIGHT_END_STR);

      /* replace every instance of "target" with "[target]" */
      replace_text(doc, target, result);
      return SUCCESS;
   }
   return FAILURE;
}

/* REMOVE_TEXT************************************************************* */
/* removes the text "target" everywhere in the document */
int remove_text(Document *doc, const char *target) {

   if (doc != NULL && target != NULL) {
      /* replace every instance of "target" with empty string */
      replace_text(doc, target, "");
      return SUCCESS;
   }
   return FAILURE;
}

/* LOAD FILE************************************************************** */
/* similar to load_document, except data is loaded from a file */
int load_file(Document *doc, const char *filename) {
   FILE *input;
   char line[MAX_STR_SIZE + 1], line1, line2[MAX_STR_SIZE + 1];
   int num_values, paragraph_number = 1;
   
   if (doc != NULL && filename != NULL) { 
      if ((input = fopen(filename, "r")) != NULL) {

	 /* add preliminary paragraph if the doc is empty */
	 add_paragraph_after(doc, 0);	    
	
	 /* add other paragraphs and lines from *input */
	 while (fgets(line, MAX_STR_SIZE + 1, input)) { 
	    
	    num_values = sscanf(line, "%c%s", &line1, line2);
	    strtok(line, "\n");	    

	    if (line1 != '#') {	       
	       if (num_values < 2) {		  
		  add_paragraph_after(doc, paragraph_number);		  
		  paragraph_number++;
	       }
	       else append_line(doc, paragraph_number, line);
	    }
	 }
	 return SUCCESS;
      }
   }
   return FAILURE;
}

/* SAVE DOCUMENT********************************************************** */
/* prints the paragraphs associated with a document to "filename" */
int save_document(Document *document, char *filename) {
   FILE *output_file;   
   int x, y, num_lines;   
   
   if (document != NULL && filename != NULL) {
      if ((output_file = fopen(filename, "w")) != NULL) {

	 /* Copying data into the file */
	 for (x = 0; x <= document->number_of_paragraphs; x++) {

	    num_lines = document->paragraphs[x].number_of_lines;
	    for (y = 0; y <= num_lines; y++) {
	       
	       fputs(document->paragraphs[x].lines[y], output_file);
	       if (y < num_lines) {
		  fputs("\n", output_file);
	       }
	    }
	    if ((x+1) < document->number_of_paragraphs) {
	       fputs("\n", output_file);
	    }
	 } /* end of for loop */
	 fclose(output_file);
	 return SUCCESS;
      }
   }
   return FAILURE;
}
