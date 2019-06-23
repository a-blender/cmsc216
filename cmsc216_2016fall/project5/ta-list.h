#if !defined(TA_LIST_H)
#define TA_LIST_H

#include "ta-list-datastructure.h"

#define CORRECT 1
#define FOUND_BUG 2

void init(TA_list *const ta_list_ptr);
int hire_TA(TA_list *const ta_list_ptr, const char *const first_name,
            const char *const last_name);
int num_TAs(TA_list ta_list);
int lookup_TA(TA_list ta_list, const char *const first_name,
              const char *const last_name, int *const id);
int set_salary(TA_list ta_list, int id, double salary);
double get_salary(TA_list ta_list, int id);
int fire_TA(TA_list *const ta_list_ptr, int id);
void reset(TA_list *const ta_list_ptr);

#endif
