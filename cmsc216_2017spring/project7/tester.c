/* TESTER by Anna Blendermann, ablender, 114474025 */
/* black box testing program for the implementation of bag */
#include <stdio.h>
#include <stdlib.h>
#include "bag.h"
static void test1(void);
static void test2(void);

/* PROFESSOR TESTS******************************************** */
/* tests that size() works for a bag with several elements */
static void test1(void) {
  Bag bag; int i;
  char element[3];

  init_bag(&bag);

  for (i= 1; i <= 10; i++) {
    sprintf(element, "%d", i);
    add_to_bag(&bag, element);
  }
  if (size(bag) != 10) {
    printf("Buggy bag- size() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* tests that count() works for elements with 2+ occurrences */
static void test2(void) {
  Bag bag; int i;
  init_bag(&bag);

  for (i= 1; i <= 10; i++)
    add_to_bag(&bag, "I love CMSC 216!");

  if (count(bag, "I love CMSC 216!") != 10) {
    printf("Buggy bag- count() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* STUDENT TESTS********************************************** */
/* init_bag() - tests that null params don't cause seg faults */
static void test3(void) {
  init_bag(NULL);
}

/* add_to_bag() - tests that null params don't change anything */
static void test4(void) {
  Bag bag;

  init_bag(&bag);

  add_to_bag(&bag, NULL);
  add_to_bag(NULL, "null bag");
}

/* add_to_bag() - tests adding to bag with zero/one elements */
static void test5(void) {
  Bag bag; int x;
  init_bag(&bag);

  add_to_bag(&bag, "raspberry pie");
  for (x = 0; x < 2; x++) {
  	add_to_bag(&bag, "blueberry pie");
  }

  if (count(bag, "blueberry pie") != 2) {
    printf("Failure - count() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* add_to_bag() - tests adding new elements to the bag */
static void test6(void) {
  Bag bag; int x;
  init_bag(&bag);

  for (x = 0; x < 5; x++) {
  	add_to_bag(&bag, "father monk");
  }
  add_to_bag(&bag, "mother monk");

  if (count(bag, "mother monk") != 1) {
    printf("Failure - count() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* add_to_bag() - tests adding elements that already exist */
static void test7(void) {
  Bag bag; int x;
  init_bag(&bag);

  add_to_bag(&bag, "apaloosa");
  add_to_bag(&bag, "clydesdale");
  add_to_bag(&bag, "thoroughbred");

  for (x = 0; x < 2; x++) {
  	add_to_bag(&bag, "thoroughbred");
  }

  if (count(bag, "thoroughbred") != 3) {
    printf("Failure - count() is wrong!\n");
    exit(FOUND_BUG);
  }
}
/* size() - tests bag for multiple occurences of one element */
static void test8(void) {
  Bag bag; int x;
  init_bag(&bag);

  for (x = 0; x < 6; x++) {
  	add_to_bag(&bag, "apple pie");
  }
  if (size(bag) != 1) {
    printf("Failure - size() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* size() - tests bag for the existence of multiple elements */
static void test9(void) {
  Bag bag; int x;
  init_bag(&bag);

  add_to_bag(&bag, "elephant");
  add_to_bag(&bag, "wombat");
  for (x = 0; x < 2; x++) {
  	add_to_bag(&bag, "dingo");
  }
  if (size(bag) != 3) {
    printf("Failure - size() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* count() - tests null element and bag with zero elements */
static void test10(void) {
  Bag bag;
  init_bag(&bag);

  if (count(bag, NULL) != -1 || count(bag, "target") != -1) {
    printf("Failure - count() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* count() - tests cases for which function should return -1 */
static void test11(void) {
  Bag bag; int x;
  init_bag(&bag);

  add_to_bag(&bag, "elephant");
  for (x = 0; x < 2; x++) {
  	add_to_bag(&bag, "giraffe");
  }
  if (count(bag, NULL) != -1 || count(bag, "quokka") != -1) {
    printf("Failure - count() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* count() - tests for elements that exist in the bag */
static void test12(void) {
  Bag bag; int x;
  init_bag(&bag);

  add_to_bag(&bag, "elephant");
  for (x = 0; x < 4; x++) {
  	add_to_bag(&bag, "giraffe");
  }
  if (count(bag, "elephant") != 1 || count(bag, "giraffe") != 4) {
    printf("Failure - count() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* remove_occurrence() - tests for null params and zero elements*/
static void test13(void) {
  Bag bag;
  init_bag(&bag);

  if (remove_occurrence(NULL, NULL) != -1 ||
      remove_occurrence(&bag, "empty node") != -1) {
    printf("Failure - remove_occurence() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* remove_occurrence() - tests other cases than should return -1 */
/* cases: null params, element not present, element num=1 */
static void test14(void) {
  Bag bag;
  init_bag(&bag);

  add_to_bag(&bag, "element #1");
  add_to_bag(&bag, "element #2");

  if (remove_occurrence(&bag, "element #1") != -1 || 
  	remove_occurrence(&bag, "element #3") != -1) {
    printf("Failure - remove_occurence() is wrong!\n");
    exit(FOUND_BUG);
  }
  if (size(bag) != 1) {
  	printf("Failure - size() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* remove_occurrence() - tests removing an element's occurrence */
static void test15(void) {
  Bag bag; int x;
  init_bag(&bag);

  for (x = 0; x < 4; x++) {
  	add_to_bag(&bag, "puppydog");
  }
  if (remove_occurrence(&bag, "puppydog") != 3) {
    printf("Failure - remove_occurrence() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* remove_occurrence() - tests removing all elements from a bag */
static void test16(void) {
  Bag bag;
  init_bag(&bag);
  add_to_bag(&bag, "puppy1");
  add_to_bag(&bag, "puppy2");
  add_to_bag(&bag, "puppy3");

  if (remove_occurrence(&bag, "puppy1") != -1 ||
  remove_occurrence(&bag, "puppy2") != -1 ||
  remove_occurrence(&bag, "puppy3") != -1) {
    printf("Failure - remove_occurrence() is wrong!\n");
    exit(FOUND_BUG);
  }
  if (size(bag) != 0) {
  	printf("Failure - size() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* remove_from_bag() - params are null, element doesn't exist, */
/* bag size is zero to begin with */

/* remove_from_bag() - null params, or bag size was zero */
static void test17(void) {
  Bag bag;
  init_bag(&bag);

  if (remove_from_bag(NULL, NULL) != -1 || 
  remove_from_bag(&bag, "address") != -1) {
    printf("Failure - remove_occurrence() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* remove_from_bag() - tests removing for one-element bag */
static void test18(void) {
  Bag bag;
  init_bag(&bag);
  add_to_bag(&bag, "target");

  if (remove_from_bag(&bag, "not target") != -1 ||
    remove_from_bag(&bag, "target") != 0) {
    printf("Failure - remove_from_bag() is wrong!\n");
    exit(FOUND_BUG);
  }
  if (size(bag) != 0) {
    printf("Failure - size() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* remove_from_bag() - tests removing from multiple-element bag */
static void test19(void) {
  Bag bag; int x;
  init_bag(&bag);

  add_to_bag(&bag, "target");
  for (x = 0; x < 3; x++) {
    add_to_bag(&bag, "double target");
  }
  for (x = 0; x < 3; x++) {
    add_to_bag(&bag, "triple target");
  }

  if (remove_from_bag(&bag, "double target") != 0 ||
    remove_from_bag(&bag, "triple target") != 0) {
    printf("Failure - remove_from_bag() is wrong!\n");
    exit(FOUND_BUG);
  }
  if (size(bag) != 1) {
    printf("Failure - size() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* bag_union() - tests when bag1/bag2 have zero elements*/
static void test20(void) {
  Bag bag1, bag2, new_bag;
  init_bag(&bag1);
  init_bag(&bag2);

  new_bag = bag_union(bag1, bag2); 

  if (size(new_bag) != 0) {
    printf("Failure - size() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* bag_union() - bag1 has one element and bag2 has zero */
static void test21(void) {
  Bag bag1, bag2, new_bag;
  init_bag(&bag1);
  init_bag(&bag2);

  add_to_bag(&bag1, "bag1 element");
  new_bag = bag_union(bag1, bag2);

  if (count(new_bag, "bag1 element") != 1) {
    printf("Failure - contains() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* bag_union() - bag1 has zero and bag2 has two occurs */
static void test22(void) {
  Bag bag1, bag2, new_bag; int x;
  init_bag(&bag1);
  init_bag(&bag2);

  for (x = 0; x < 2; x++) {
      add_to_bag(&bag2, "bag2 element");
  }
  new_bag = bag_union(bag1, bag2);

  if (count(new_bag, "bag2 element") != 2) {
    printf("Failure - count() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* bag_union() - bag1 and bag2 both have two elements */
static void test23(void) {
  Bag bag1, bag2, new_bag; int x;
  init_bag(&bag1);
  init_bag(&bag2);

  for (x = 0; x < 2; x++) {
      add_to_bag(&bag1, "element #1");
  }
  for (x = 0; x < 5; x++) {
      add_to_bag(&bag1, "element #2");
  }
  for (x = 0; x < 2; x++) {
      add_to_bag(&bag2, "element #1");
  }
  for (x = 0; x < 3; x++) {
      add_to_bag(&bag2, "element #2");
  }
  new_bag = bag_union(bag1, bag2);

  if (count(new_bag, "element #1") != 4 ||
    count(new_bag, "element #2") != 8 || size(new_bag) != 2) {
    printf("Failure - count() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* bag_union() - tests complex makeup of bag1 and bag2 */
static void test24(void) {
  Bag bag1, bag2, new_bag; int x;
  init_bag(&bag1);
  init_bag(&bag2);
      
  add_to_bag(&bag1, "birthday");
  add_to_bag(&bag1, "christmas");
  for (x = 0; x < 2; x++) {
      add_to_bag(&bag1, "cross element");
  }

  add_to_bag(&bag2, "cross element");
  for (x = 0; x < 2; x++) {
      add_to_bag(&bag2, "easter");
  }
  new_bag = bag_union(bag1, bag2);

  if (count(new_bag, "cross element") != 3 || 
    count(new_bag, "easter") != 2 || size(new_bag) != 4) {
    printf("Failure - count() is wrong!\n");
    exit(FOUND_BUG);
  }
}

/* is_sub_bag() - tests for zero elements, and zero for bag1 */
static void test25(void) {
   Bag bag1, bag2;
  init_bag(&bag1);
  init_bag(&bag2);

  if (is_sub_bag(bag1, bag2) != 1) {
    printf("Failure - is_sub_bag() is wrong!\n");
    exit(FOUND_BUG);
  }
  add_to_bag(&bag2, "new element");
  if (is_sub_bag(bag1, bag2) != 1) {
    printf("Failure - is_sub_bag() is wrong!\n");
    exit(FOUND_BUG);
  }    
}

/* is_sub_bag() - test cases where bag1 IS subbag of bag2 */
static void test26(void) {
   Bag bag1, bag2;
  init_bag(&bag1);
  init_bag(&bag2);

  add_to_bag(&bag1, "money");
  add_to_bag(&bag2, "artifact");

  add_to_bag(&bag2, "money");
  add_to_bag(&bag2, "angel");
  add_to_bag(&bag2, "artifact");

  if (is_sub_bag(bag1, bag2) != 1) {
    printf("Failure - is_sub_bag() is wrong!\n");
    exit(FOUND_BUG);
  }    
}

/* is_sub_bag() - test cases where bag1 NOT subbag of bag2 */
static void test27(void) {
   Bag bag1, bag2; int x;
  init_bag(&bag1);
  init_bag(&bag2);

  for (x = 0; x < 2; x++) {
      add_to_bag(&bag1, "money");
  }
  add_to_bag(&bag2, "money");
  add_to_bag(&bag2, "angel");
  add_to_bag(&bag2, "artifact");

  if (is_sub_bag(bag1, bag2) != 0) {
    printf("Failure - is_sub_bag() is wrong!\n");
    exit(FOUND_BUG);
  }     
}

/* clear_bag() - tests function for one and multiple elements */
static void test28(void) {
  Bag bag;
  init_bag(&bag);

  add_to_bag(&bag, "chris");
  add_to_bag(&bag, "mary");
  add_to_bag(&bag, "anna");
  add_to_bag(&bag, "katie");

  clear_bag(NULL); /* checking for null */
  clear_bag(&bag);
  if (size(bag) != 0) {
    printf("Failure - size() is wrong!\n");
    exit(FOUND_BUG);
  }    
}

/* MAIN DRIVER************************************************ */
int main() {
  printf("Running test 1...\n");
  test1();
  printf("Running test 2...\n");
  test2();
  printf("Running test 3...\n");
  test3();
  printf("Running test 4...\n");
  test4();
  printf("Running test 5...\n");
  test5();

  printf("Running test 6...\n");
  test6();
  printf("Running test 7...\n");
  test7();
  printf("Running test 8...\n");
  test8();
  printf("Running test 9...\n");
  test9();
  printf("Running test 10...\n");
  test10();

  printf("Running test 11...\n");
  test11();
  printf("Running test 12...\n");
  test12();
  printf("Running test 13...\n");
  test13();
  printf("Running test 14...\n");
  test14();
  printf("Running test 15...\n");
  test15();

  printf("Running test 16...\n");
  test16();
  printf("Running test 17...\n");
  test17();
  printf("Running test 18...\n");
  test18();
  printf("Running test 19...\n");
  test19();
  printf("Running test 20...\n");
  test20();

  printf("Running test 21...\n");
  test21();
  printf("Running test 22...\n");
  test22();
  printf("Running test 23...\n");
  test23();
  printf("Running test 24...\n");
  test24();
  printf("Running test 25...\n");
  test25();

   printf("Running test 26...\n");
  test26();
   printf("Running test 27...\n");
  test27();
   printf("Running test 28...\n");
  test28();

  printf("No errors detected!\n");
  return CORRECT;
}

