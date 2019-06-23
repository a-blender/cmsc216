/* BAG by Anna Blendermann, ablender, 114474025 */
/* execution of a bag structure with elements */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bag.h"
#include "bag-implementation.h"
int contains(Bag *bag, const char *element);

/* INIT BAG***************************************************************** */
/* initializes head pointer and elements of the new bag */
void init_bag(Bag *bag) {
   
   /* checking that bag isn't null */
   if (bag) {            
      bag->head = NULL;
      bag->num_elements = 0;      
   }	       
}

/* ADD TO BAG************************************************************** */
/* adds a new element to the bag using name parameter */
void add_to_bag(Bag *bag, const char *element) {
   Element *new_element, *temp;
   
   /* check that bag and element aren't null */
   if (bag && element) {

      /* case 1 = no elements */
      if (bag->num_elements == 0) {
	 new_element = malloc(sizeof(Element));
	 new_element->name = malloc(sizeof(char) * (strlen(element) + 1));
	 strcpy(new_element->name, element);
	 new_element->num_occurrences = 1;

	 bag->head = new_element;
	 new_element->next = NULL;
	 (bag->num_elements)++;
      }
      /* case 2 = bag has elements */
      else if (bag->num_elements > 0) {

	 /* case 2.1 = bag has elements, target doesn't exist */
	 if (contains(bag, element) == -1) {
	    new_element = malloc(sizeof(Element));
	    new_element->name = malloc(sizeof(char) * (strlen(element) + 1));
	    strcpy(new_element->name, element);
	    new_element->num_occurrences = 1;
	    
	    new_element->next = bag->head;
	    bag->head = new_element;
	    (bag->num_elements)++;
	 }
	 /* case 2.2 = bag has elements, target DOES exist */
	 else {
	    temp = bag->head;
	    while (temp != NULL) {
	       if (strcmp(temp->name, element) == 0) {
		  (temp->num_occurrences)++;
	       }
	       temp = temp->next;
	    }
	 } /* end of the else clause */	      
      } /* end of case 2 */      
   } /* end of null check */
}

/* CONTAINS***************************************************************** */
/* auxilary function for searching if an element exists in the bag */
int contains(Bag *bag, const char *element) {
   Element *temp;
   
   if (bag && element) {
      
      temp = bag->head;
      while (temp != NULL) {
	 if (strcmp(temp->name, element) == 0) {
	    return 0; /* success, element was found! */
	 }
	 temp = temp->next;
      }
   }
   return -1; /* failure, element not found */
}

/* SIZE********************************************************************* */
/* testing done! */
size_t size(Bag bag) {
   return bag.num_elements;
}

/* COUNT******************************************************************** */
/* counts the number of occurrences for a specific element */
int count(Bag bag, const char *element) {
   Element *temp;
   
   if (bag.num_elements != 0 && element) {

      temp = bag.head;
      while (temp != NULL) {
	 if (strcmp(temp->name, element) == 0) {
	    return temp->num_occurrences;
	 }
	 temp = temp->next;	 
      }
   }
   return -1;
}

/* REMOVE OCCURRENCE******************************************************* */
/* removes one occurrence of the given element from the bag */
int remove_occurrence(Bag *bag, const char *element) {
   Element *temp;

   /* check that bag and element aren't null */
   if (bag && element) {
      
      if (contains(bag, element) != -1) {
	 temp = bag->head;
	 while (temp != NULL) {

	    if (strcmp(temp->name, element) == 0) {
	       if (temp->num_occurrences == 1) {
		  remove_from_bag(bag, element);
	       }
	       else if (temp->num_occurrences > 1) {
		  (temp->num_occurrences)--;
		  return temp->num_occurrences;
	       }
	    }
	    temp = temp->next;
	 }
      }
   }
   return -1;
}

/* REMOVE FROM BAG********************************************************* */
/* removes all occurrences of an entire element from the bag */
int remove_from_bag(Bag *bag, const char *element) {
   Element *prev, *curr;

   /* check that bag and element aren't null */
   if (bag && element && (contains(bag, element) != -1)) {

      curr = bag->head;
      /* case 1: one element -> remove that element from the bag */
      if (curr && !(curr->next)) {
	 bag->head = curr->next;
	 curr->next = NULL;
	 free(curr->name);
	 free(curr);	 
      }
      /* case 2: multiple elements -> find element to remove */
      else if (curr && curr->next) {
	 
	 prev = curr;
	 curr = curr->next;
	 /* case 2.1: target exists at the front of the array */
	 if (strcmp(prev->name, element) == 0) {
	    bag->head = curr;
	    prev->next = NULL;
	    free(prev->name);
	    free(prev);
	 }
	 else {
	    /* case 2.2: target exists in the middle/end of the array */
	    while (curr != NULL) {

	       if (strcmp(curr->name, element) == 0) {
		  prev->next = curr->next;
		  curr->next = NULL;
		  free(curr->name);
		  free(curr);
	       }
	       prev = curr;
	       curr = curr->next;
	    }
	 }
      } /* end of else-if clause */
      (bag->num_elements)--;
      return 0;
      
   } /* end of null and contains check */   
   return -1;
}

/* BAG UNION*************************************************************** */
/* adds two bags together into a new bag, which is returned */
Bag bag_union(Bag bag1, Bag bag2) {
   Bag new_bag; Element *temp;
   int x = 0, total = 0;
   char *new_element;   
   init_bag(&new_bag);	

   /* step 1: add elements from bag1, with matching elements from bag2 */
   /* check if bag1 has elements, if so - add from bag1 */ 
   if (bag1.num_elements) {
      temp = bag1.head;
      
      while (temp != NULL) {

	 new_element = malloc(sizeof(char) * strlen(temp->name)+1);
	 strcpy(new_element, temp->name);	 
	 if (contains(&bag2, temp->name) != -1) {
	    total = temp->num_occurrences + count(bag2, temp->name);
	 }
	 else total = temp->num_occurrences;		 
	 for (x = 0; x < total; x++) {
	    add_to_bag(&new_bag, new_element);
	 }
	 temp = temp->next;
      }
   }
   /* step 2: add remaining elements from bag 2 */
   /* check if bag1 has elements, if so - add from bag1 */ 
   if (bag2.num_elements) {
      
      temp = bag2.head;
      while (temp != NULL) {
	 
	 if (contains(&new_bag, temp->name) == -1) {
	    new_element = malloc(sizeof(char) * strlen(temp->name)+1);
	    strcpy(new_element, temp->name);
	      
	    for (x = 0; x < temp->num_occurrences; x++) {
	       add_to_bag(&new_bag, new_element);
	    }
	 }	
	 temp = temp->next;
      }
   }      
   return new_bag;
}

/* IS SUB BAG************************************************************** */
/* checks if the elements of bag1 are contained in bag2 */
int is_sub_bag(Bag bag1, Bag bag2) {
   Element *temp;   
   
   /* case 1: bag1 has no elements, always return 1 */
   if (bag1.num_elements) {
	
      /* case 2: bag1 has elements, compare with bag2 */
      temp = bag1.head;
      while (temp != NULL) {	 
	  	if (contains(&bag2, temp->name) == -1 
	  		|| (contains(&bag2, temp->name) != -1 && 
	  		(temp->num_occurrences > count(bag2, temp->name)))) {
	    return 0;
	 }	 	    	
	 temp = temp->next;
     }
   }
   return 1;
}

/* CLEAR BAG*************************************************************** */
/* clears all occurrences of all elements from the bag */
void clear_bag(Bag *bag) {
   Element *curr, *temp;
   
   if (bag && bag->head) {

      curr = bag->head;
      while (curr != NULL) {
	 temp = curr;
	 curr = curr->next;

	 temp->next = NULL;
	 free(temp->name);
	 free(temp);
      }
      bag->num_elements = 0;
   }
}



