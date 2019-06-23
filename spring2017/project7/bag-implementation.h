/* BAG IMPLEMENTATION by Anna Blendermann, ablender, 114474025 */
/* defines the bag and types for the elements */
#if !defined(BAG_IMPLEMENTATION)
#define BAG_IMPLEMENTATION

typedef struct element {
   char *name;
   int num_occurrences;
   struct element *next;
} Element;

typedef struct bag {
   Element *head;
   int num_elements;
} Bag;

#endif
   
