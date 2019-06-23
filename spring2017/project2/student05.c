/* STUDENT04 TEST by Anna Blendermann */
#include <stdio.h>
#include <string.h>
#include "document.h"

int main() {
   Document doc;
   const char *doc_name = "Removing ALL the lines";

   if (init_document(&doc, doc_name) == FAILURE) {
      printf("Initialization failed\n");
   } else {
      print_document(&doc);
   }

   /* adding first paragraph */
   add_paragraph_after(&doc, 0);
   add_paragraph_after(&doc, 1);

   /* adding lines to the paragraph */
   append_line(&doc, 1, "First Paragraph, First line");
   append_line(&doc, 1, "First Paragraph, Second line");
   
   append_line(&doc, 2, "Second Paragraph, First line");
   append_line(&doc, 2, "Second Paragraph, Second line");
   
   /* remove "Paragraph" everywhere in the doc */
   remove_line(&doc, 1, 1);
   remove_line(&doc, 2, 2);

   if (remove_line(&doc, 1, 4) == FAILURE) {
      printf("Failure - no line there to remove\n");
   }
   print_document(&doc);

   return 0;
}
