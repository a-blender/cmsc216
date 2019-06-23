/* Anna Blendermann, ablender, 114474025, 0104 */
/* I pledge on my honor that I have not given or received any unauthorized */
/* help on this programming assignment (project6) */

/* Student tests for the functions of project6 */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "mockfile.h"

static void test1(void);
static void test2(void);
static void test3(void);
static void test4(void);
static void test5(void);
static void test6(void);
static void test7(void);
static void test8(void);
static void test9(void);
static void test10(void);
static void test11(void);
static void test12(void);
static void test13(void);

int main(void) {
  /* test the read_mockfile function */
  test1();
  test2();
  test3();
  /* test lookup_target for the rule number search */
  test4();
  test5();
  /* test print_action for it's functionality */
  test6();
  test7();
  /* tests num_dependencies for functionality */
  test8();
  test9();
  /* tests get_dependency for functionality */
  test10();
  test11();
  /* just some other tests */
  test12();
  test13();
  
  printf("\n*******************************\n");
  printf("YOU PASSED ALL THE STUDENT TESTS!");
  printf("\n*******************************\n");
  return 0;
}

/* tests that read_mockfile can read a simple mockfile */
static void test1(void) {
  Mockfile *mockfile = read_mockfile("public01.mockfile");

  assert(mockfile != NULL);
  printf("Output of public01.mockfile:\n");
  print_mockfile(mockfile);

  printf("You passed student test #1!\n");
}

/* tests reading two mockfiles at the same time */
static void test2(void) {
  Mockfile *file1 = read_mockfile("public01.mockfile");
  Mockfile *file2 = read_mockfile("public02.mockfile");

  if(file1 == NULL || file2 == NULL)
    printf("Your return value from read_mockfile was null\n");

  assert(num_dependencies(file1, 1) == -1);
  assert(num_dependencies(file2, 1) == 2);
  printf("You passed student test #2!\n");
}

/* tests running read_mockfile with null parameter */
static void test3(void) {
  Mockfile *file = read_mockfile(NULL);

  assert(file == NULL);
  printf("You passed student test #3!\n");
}

/* tests lookup_target for the first target in a mockfile */
static void test4(void) {
  Mockfile *file = read_mockfile("public01.mockfile");
  assert(file != NULL);
  
  assert(lookup_target(file,"main.x") == 0);
  assert(lookup_target(file, "main.edu") == -1);
  printf("You passed student test #4!\n");
}

/* tests lookup_target for the last target out of three */
static void test5(void) {
  Mockfile *file = read_mockfile("public04.mockfile");

  assert(lookup_target(file, "main.o") == 2);
  assert(lookup_target(file, "clean") == 3);
  assert(lookup_target(file, "clean5") == -1);

  printf("You passed student test #5!\n");
}

/* tests full valid functionality of print_action */
static void test6(void) {
  Mockfile *file = read_mockfile("public03.mockfile");

  print_action(file, 0); /* gcc main.o functions.o -o main.o */
  printf("\n");
  print_action(file, 1); /* gcc -c functions.c */
  printf("\n");

  printf("You passed student test #6!\n");
}

/* tests all invalid cases for print_action */
static void test7(void) {
  Mockfile *file = read_mockfile("public03.mockfile");

  /* these function calls should do nothing */
  print_action(NULL, 2);
  print_action(file, -500);
  print_action(file, 4);
  printf("You passed student test #7!\n");
}

/* tests all valid cases for num_dependencies */
static void test8(void) {
  Mockfile *file = read_mockfile("public04.mockfile");

  assert(num_dependencies(file, 0) == 2);
  assert(num_dependencies(file, 2) == 2);
  assert(num_dependencies(file, 3) == 0);

  printf("You passed student test #8!\n");
}

/* tests num_dependencies for invalid/nonexistent cases */
static void test9(void) {
  Mockfile *file = read_mockfile("public04.mockfile");
  assert(file != NULL);

  /* these should all return -1 */
  assert(num_dependencies(NULL, 0) == -1);
  assert(num_dependencies(NULL, 100) == -1);
  assert(num_dependencies(file, -20) == -1);
  assert(num_dependencies(file, 4) == -1);

  printf("You passed student test #9!\n");
}

/* tests get_dependency from the public02.mockfile */
static void test10(void) {
  Mockfile *file = read_mockfile("public02.mockfile");

  assert(strcmp(get_dependency(file, 0, 0), "main.o") == 0);
  assert(strcmp(get_dependency(file, 1, 0), "functions.c") == 0);
  assert(strcmp(get_dependency(file, 1, 1), "functions.h") == 0);
  
  printf("You passed student test #10!\n"); 
}

/* tests get_dependencies for ones that don't exist */
static void test11(void) {
  Mockfile *file = read_mockfile("public02.mockfile");

  /* these function calls should all return null */
  assert(get_dependency(NULL, 0, 0) == NULL);
  assert(get_dependency(file, 0, -2) == NULL);
  assert(get_dependency(file, -5, 1) == NULL);

  assert(get_dependency(file, 1, 2) == NULL);
  assert(get_dependency(file, 5, 0) == NULL);
  printf("You passed student test #11!\n");
}

/* tests some simple cases for clear_mockfile */
static void test12(void) {
  Mockfile *file = read_mockfile("public10.mockfile");
  Mockfile* void_file;

  assert(strcmp(get_dependency(file, 0, 0), "main.o") == 0);
  assert(strcmp(get_dependency(file, 2, 1), "functions.h") == 0);
  assert(get_dependency(file, 3, 0) == NULL);

  /* this function call should do nothing */
  clear_mockfile(&void_file);
  clear_mockfile(&file);
  assert(file == NULL);
  
  printf("You passed student test #12!\n");		
}

/* tests lookup_target and the two dep functions */
static void test13(void) {
  Mockfile *file = read_mockfile("public10.mockfile");

  assert(lookup_target(file, "main.o") == 2);
  assert(lookup_target(file, "trigger") == -1);
  
  assert(lookup_target(file, "clean") == 3);
  assert(num_dependencies(file, 3) == 0);
  assert(get_dependency(file, 3, -10) == NULL);

  clear_mockfile(&file);
  assert(file == NULL);
  printf("You passed student test #13!\n"); 
}
  

  
