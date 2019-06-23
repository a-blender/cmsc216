/* LINECHECK by Anna Blendermann (ablender,14474025, 0104) */

/* I pledge on my honor that I have not given or received any unauthorized */
/* assistance on this assignment */

/* this is a simple C program to check the string output from files */
/* this program checks whether size<80, counts lines, and prints output */
#include <stdio.h>

int main (void) {
  int lineCount = 1; /* counts number of lines */
  char mychar; /* variable for each character */
  
  /* read character by character for newline */
  while ((mychar = getchar()) != EOF) {
   
    int arrayCount = 0; /* counts number of chars in each line */
    char newline[999]; /* array for holding chars from each line */
    int x,y; /* x for the printing line loop: output */
    
    while (mychar != '\n') {
      newline[arrayCount] = mychar; /* add char to your array */
      arrayCount += 1; /* increment the array index */
      mychar = getchar(); /* get another character */
    }    
    newline[arrayCount] = '\n'; /* add newline to your array */

    /* print line output for size<=80 */
    if (arrayCount <= 80) {
      printf("%6d: ", lineCount);
      for (x = 0; x <= arrayCount; x++) {
	printf("%c", newline[x]);
      }
    }

    /* print line output for size>80 */
    else if (arrayCount > 80) {
      printf("*%5d: ", lineCount);
    
      for (x = 0; x <= arrayCount; x++) {
	printf("%c", newline[x]);
      }
      printf("%88s", "");
      for (y = 80; y < arrayCount; y++) {
	printf("^");
      }
      printf("\n"); /* print newline for bash */
    }
    
    lineCount += 1; /* increment line number */
  } /* end of outside while loop */
  return 0;
} /* end of main linecheck function */
