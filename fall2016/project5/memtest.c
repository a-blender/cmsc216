/* Anna Blendermann, ablender, 114474025, 0104 */
/* I pledge on my honor that I have not given or received any unauthorized */
/* assistance on this programming assignment */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ta-list.h"

static void test1(void);
static void test2(void);

int main(void) {
  test1();
  test2();
  return CORRECT;
}

static void test1(void) {

  TA_list student_list;
  init(&student_list);
  
  hire_TA(&student_list, "A", "man");
  hire_TA(&student_list, "B", "man");
  hire_TA(&student_list, "C", "man");
  hire_TA(&student_list, "D", "man");
  
  reset(&student_list);
  printf("Fuck - you passed.\n");
}

static void test2(void) {

  TA_list student_list;
  init(&student_list);

  hire_TA(&student_list, "A", "girl");
  hire_TA(&student_list, "B", "girl");
  hire_TA(&student_list, "C", "girl");

  reset(&student_list);
  printf("Fuck - you passed this one too.\n");
}
