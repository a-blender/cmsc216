#if !defined(TA_STRUCT)
#define TA_STRUCT

/* Two data structures to simulate a list of Computer Science TAs */
/* implemented as singly linked list of TA_struct structures */

/* Structure #1 - TA_struct with data fields for first name, last name */
/* teacher's ID, salary amount, and a "next" pointer */

typedef struct Assistant {
  char *first_name;
  char *last_name;
  int ta_id;
  double salary;
  struct Assistant *next;
} TA_struct;

/* Structure #2 - TA_list to hold the TA_struct structures with both */
/* head and tail references, and the number of elements */

typedef struct List {
  struct Assistant *head;
  struct Assistant *tail;
} TA_list;
  
#endif
