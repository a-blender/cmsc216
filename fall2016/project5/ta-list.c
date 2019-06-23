/* Anna Blendermann, ablender, 114474025, 0104 */
/* I pledge on my honor that I have not received any unauthorized assistance */
/* on this programming assignment (project5) */

/* this program uses a singly linked list of structures, named TA_list */
/* to keep track of data relevant to computer science TAs */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ta-list.h"

void reset_helper(TA_struct *current_node);
void print_list(TA_list *const ta_list);


/* INIT() initializes a new linked list of TAs (tested) */
/* this function intializes and allocates memory for the new list */
void init(TA_list *const ta_list_ptr) {

  /* check that the list param is valid */
  if (ta_list_ptr != NULL) {
    
    /* allocate memory for the head structure */
    ta_list_ptr->head = malloc(sizeof(TA_struct));
    ta_list_ptr->tail = malloc(sizeof(TA_struct));

    /* set both head and tail references to null */
    ta_list_ptr->head = NULL;
    ta_list_ptr->tail = NULL;
  }
}


/* HIRE_TA() adds a new TA to the current list (tested) */
/* this function adds new TA to the end of the list using tail reference */
int hire_TA(TA_list *const ta_list_ptr, const char *const first_name, const
	    char *const last_name) {

  TA_struct *new_ta; /* pointer to the new TA structure */
  TA_struct *curr; /* pointer to iterate through list */
  
  /* check that function parameters are valid */
  if (first_name != NULL && last_name != NULL) {
      
    /* dynamically allocate memory for the new TA */
    new_ta = malloc(sizeof(TA_struct));
    new_ta->first_name = malloc(sizeof(char)*(strlen(first_name)+1));
    new_ta->last_name = malloc(sizeof(char)*(strlen(last_name)+1));

    /* set new fields for new TA structure */
    strcpy(new_ta->first_name, first_name);
    strcpy(new_ta->last_name, last_name);
    new_ta->salary = 0.0;
    new_ta->next = NULL;

    /* CASE #1, LIST IS EMPTY = add TA to empty list, ta_id = 1 */
    if (ta_list_ptr->head == NULL) {

      /* set ta_id to 1 for starting element */
      new_ta->ta_id = 1;

      /* set both the head & tail reference to new_ta */
      ta_list_ptr->head = new_ta;
      ta_list_ptr->tail = new_ta;
      return 1;
    }

    /* CASE #2, LIST NOT EMPTY = add TA to end, ta_id = prev+1 */
    else if (ta_list_ptr->head != NULL) {

      /* TA already exists within non-empty list = return 0 */
      for (curr = ta_list_ptr->head; curr != NULL; curr = curr->next) {
	if (strcmp(curr->first_name, first_name) == 0 &&
	    strcmp(curr->last_name, last_name) == 0)
	  return 0;
      }
      /* set ta_id to the salary of the prev TA + 1 */
      new_ta->ta_id = ta_list_ptr->tail->ta_id + 1;

      /* add TA to end of list using tail reference */
      ta_list_ptr->tail->next = new_ta;
      ta_list_ptr->tail = new_ta;
      return 1;
    } 
  }
  return 0;
}


/* NUM_TAS() finds the number of TAs in the list (tested) */
/* this function returns the number of elements in the list, over zero */
int num_TAs(TA_list ta_list) {

  TA_struct *curr;  /* pointer to iterate through list */
  int result = 0; /* var for number of list elements */

  /* iterate through list and accumulate result */
  if (ta_list.head != NULL) {
    for (curr = ta_list.head; curr != NULL; curr = curr->next)
      result = result + 1;
  }
  return result;
}


/* LOOKUP_TA() looks up TA by first/last name (tested) */
/* this function returns the TA ID or num of TAs with last name */
int lookup_TA(TA_list ta_list, const char *const first_name, const char *const
	      last_name, int *const id) {
  
  TA_struct *curr; /* pointer to iterate through list */
  int num; /* variable to log TAs in case first name is null */
  
  /* first check that function parameters are valid */
  if (last_name != NULL && id != NULL) {

    /* list is empty = return -1 because no TAs exist there */
    if (ta_list.head == NULL)
      return -1;
    
    /* first name isn't null = search TA by first & last name, modify id */
    if (first_name != NULL) {

      for (curr = ta_list.head; curr != NULL; curr = curr->next) {

	if (strcmp(curr->first_name, first_name) == 0
	   && strcmp(curr->last_name, last_name) == 0) {
	  /* MODIFY THE ID HERE */
	  return 1;
	}
      }
    }

    /* first name is null = search TAs by last name, don't modify id */
    else if (first_name == NULL) {

      for (curr = ta_list.head; curr != NULL; curr = curr->next) {
	if (strcmp(curr->last_name, last_name) == 0)
	  num = num + 1;
      }
      return num; /* return num of TAs with same last name */
    }
    return -1; /* TA not found = return -1 */
  }
  else return 0;
}


/* SET_SALARY() sets the salary of the TA target (tested) */
/* this function returns the success status of the salary modification */
int set_salary(TA_list ta_list, int id, double salary) {

  TA_struct *curr; /* pointer to iterate the list */
  
  /* check that the function parameters are valid */
  if (ta_list.head != NULL && id > 0 && salary >= 0) {

    for (curr=ta_list.head; curr != NULL; curr = curr->next) {

      /* TA id found = modify salary and return 1 */
      if (curr->ta_id == id) {
	curr->salary = salary; 
	return 1;
      }
    }
  }
  return 0;
}


/* GET_SALARY() returns the salary of the TA target (tested) */
/* this function gets the TA salary, if that element exists in the list */
double get_salary(TA_list ta_list, int id) {

  TA_struct *curr; /* pointer to iterate the list */
  
  /* check that the function parameters are valid */
  if (ta_list.head != NULL && id > 0) {

    for (curr = ta_list.head; curr != NULL; curr = curr->next) {

      /* TA id exists = return the salary of that TA */
      if (curr->ta_id == id)
	return curr->salary;
    }
  }
  return 0.0; /* TA ID doesn't exist */
}


/* FIRE_TA() removes TA from the current list by ID number */
/* this function deallocates memory from the target TA and deletes it */
int fire_TA(TA_list *const ta_list_ptr, int id) {

  TA_struct *temp, *prev, *curr; /* pointers to iterate list */
  
  /* check for non-empty list and valid parameters */
  if (ta_list_ptr->head != NULL && id > 0) {

    /* list has one TA and ID=1 = call reset and return 1 */
    if (ta_list_ptr->head->next == NULL && id == 1) {
      reset(ta_list_ptr);
      return 1;
    }
    /* list has multiple TAs and ID=1 = move head to second TA */
    if (ta_list_ptr->head->next != NULL && id == 1) {
      temp = ta_list_ptr->head;
      ta_list_ptr->head = ta_list_ptr->head->next;
      free(temp);
      return 1;
    }

    /* list has multiple elements and ID>1 = iterate list */
    for (curr = ta_list_ptr->head; curr != NULL; prev = curr,
	  curr = curr->next) {
      
      /* TA ID found = remove TA from list and return 1 */
      if (curr->ta_id == id) {
	
	/* curr->next not null = remove from middle of list */
	if (curr->next != NULL) {
	  prev->next = curr->next;
	  free(curr);
	  return 1;
	}
	else if (curr->next == NULL) {
	  prev->next = NULL;
	  free(curr);
	  return 1;
	}
      }
    } /* end of iterative for loop */
  }
  return 0; /* TA doesn't exist */
}


/* RESET() deallocates memory from the current list */
/* this function recursively deallocates memory and empties list */
void reset(TA_list *const ta_list_ptr) {

  /* recursively deallocate the entire list */
  if (ta_list_ptr->head != NULL) {

    if (ta_list_ptr->head->next == NULL) {
      free(ta_list_ptr->head->first_name);
      free(ta_list_ptr->head->last_name);
      free(ta_list_ptr->head);
      ta_list_ptr->head = NULL;
    }
    else {
      reset_helper(ta_list_ptr->head);
      free(ta_list_ptr->tail);
      free(ta_list_ptr->head);
    }
  }
}


/* HELPER FUNCTIONS************************************************** */

void reset_helper(TA_struct *current_node) {

  if(current_node->next != NULL)
    reset_helper(current_node->next);
    
  free(current_node->first_name);
  free(current_node->last_name);
  free(current_node);
}

/* PRINT_LIST() prints all elements in the current list */
void print_list(TA_list *const ta_list) {

  TA_struct *curr;
  for (curr = ta_list->head; curr != NULL; curr = curr->next) {
    
    printf("%s %s %d\n", curr->first_name, curr->last_name,
	   curr->ta_id);
  }
}
