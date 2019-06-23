/* STUDENT02 TEST by Anna Blendermann */
#include <stdio.h>
#include <string.h>
#include "document.h"

int main() {
   Document doc;
   const char *doc_name = "Adding Lines";

   if (init_document(&doc, doc_name) == FAILURE) {
      printf("Initialization failed\n");
   } else {
      print_document(&doc);
   }

   /* adding first paragraph */
   add_paragraph_after(&doc, 0);
   
   /* adding lines to the paragraph */
   add_line_after(&doc, 1, 0, "First Paragraph, yo dog #1");
   add_line_after(&doc, 1, 1, "First Paragraph, yo dog #2");
   add_line_after(&doc, 1, 2, "First Paragraph, yo dog #3");
   print_document(&doc);

   if(add_line_after(&doc, 5, 0, "This won't work") == FAILURE)
      printf("Failure - doc only has three paragraphs\n");

   /* add lines to the middle of the paragraph */
   add_line_after(&doc, 1, 2, "This is the middle line!");
   print_document(&doc);
   return 0;
}

