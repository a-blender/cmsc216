#if !defined(DOCUMENT_H)

#define DOCUMENT_H
#define MAX_PARAGRAPH_LINES 20
#define MAX_PARAGRAPHS 15
#define MAX_STR_SIZE 80 
#define HIGHLIGHT_START_STR "["
#define HIGHLIGHT_END_STR "]"
#define SUCCESS 0
#define FAILURE -1

typedef struct {
   int number_of_lines;
   char lines[MAX_PARAGRAPH_LINES][MAX_STR_SIZE + 1];
} Paragraph;

typedef struct {
   char name[MAX_STR_SIZE + 1];
   int number_of_paragraphs;
   Paragraph paragraphs[MAX_PARAGRAPHS];
} Document;

int init_document(Document *doc, const char *name);
int reset_document(Document *doc);
int print_document(Document *doc);
int add_paragraph_after(Document *doc, int paragraph_number);
int add_line_after(Document *doc, int paragraph_number, int line_number,
		   const char *new_line);
int get_number_lines_paragraph(Document *doc, int paragraph_number, int *number_of_lines);
int append_line(Document *doc, int paragraph_number, const char *new_line);
int remove_line(Document *doc, int paragraph_number, int line_number);
int load_document(Document *doc, char data[][MAX_STR_SIZE + 1], int data_lines);
int replace_text(Document *doc, const char *target, const char *replacement);
int highlight_text(Document *doc, const char *target);
int remove_text(Document *doc, const char *target);
#endif
