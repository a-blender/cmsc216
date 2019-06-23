/* STUDENT01 TEST by Anna Blendermann */
#include <stdio.h>
#include <string.h>
#include "document.h"

int main() {
   Document doc;
   const char *doc_name = "Adding Paragraphs";

   if (init_document(&doc, doc_name) == FAILURE) {
      printf("Initialization failed\n");
   } else {
      print_document(&doc);
   }

   /* adding first two paragraphs */
   add_paragraph_after(&doc, 0); /* add paragraph 1 */
   add_paragraph_after(&doc, 1); /* add paragraph 2 */
   add_paragraph_after(&doc, 2);
   
   /* adding lines to the paragraph */
   append_line(&doc, 1, "First Paragraph, baby dog");   
   append_line(&doc, 2, "Second Paragraph, baby cat");
   append_line(&doc, 3, "Third paragraph, baby duck");
   print_document(&doc);

   /* adding paragraph to the middle */
   add_paragraph_after(&doc, 0);
   append_line(&doc, 1, "This is now the middle paragraph!");

   print_document(&doc);   
   return 0;
}

