/* Anna Blendermann, ablender, 114474025, 0104 */
/* I pledge on my honor that I have not received any unauthorized assistance */
/* on this programming assignment (project5) */

/* BLACK BOX TESTING PROGRAM with comprehensive functional testing */
/* this file tests the functionality of CMSC216 project5 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ta-list.h"

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
static void test14(void);
static void test15(void);
static void test16(void);
static void test17(void);
static void test18(void);
static void test19(void);
static void test20(void);
static void test21(void);
static void test22(void);
static void test23(void);
static void test24(void);
static void test25(void);
static void test26(void);
static void test27(void);
static void test28(void);

/* MAIN() FUNCTION CALLS THE TEST FUNCTIONS */
int main(void) {

  /* test init() for bugs */
  test1();
  /* test hire_TA() for bugs */
  test2();
  test3();
  test4();
  /* test num_TAs() for bugs */
  test5();
  test6();
  /* test lookup_TA() for any bugs */
  test7();
  test8();
  test9();
  test10();
  test11();
  test12();
  /* test set_salary() for bugs */
  test13();
  test14();
  test15();
  test16();
  /* test get_salary() for bugs */
  test17();
  test18();
  /* tests fire_TA() for the bugs */
  test19();
  test20();
  test21();
  test22();
  test23();
  /* tests reset() for any bugs */
  test24();
  test25();
  test26();
  /* Just some additional tests... */
  test27();
  test28();
  
  printf("No bugs were detected!\n");
  return CORRECT;
}

/* WE ARE TESTING INIT() NOW************************************************* */ 

/* tests the functionality of init() */
static void test1(void) {
  TA_list student_list;
  init(&student_list);
  
  init(NULL);
  printf("You passed student test #1!\n");
}

/* WE ARE TESTING HIRE_TA() NOW8********************************************* */

/* tests adding three entries to the list */
static void test2(void) {
  TA_list student_list;
  init(&student_list);

  if(hire_TA(&student_list, "Jade", "Price") != 1 ||
     hire_TA(&student_list, "Wesley", "Price") != 1 ||
     hire_TA(&student_list, "Mary", "Rosenthal") != 1) {
    printf("Bug Found: hire_TA() failed to add TAs\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #2!\n");
}

/* tests adding a duplicate entry to the list */
static void test3(void) {
  TA_list student_list;
  init(&student_list);

  hire_TA(&student_list, "$dollar", "$sign");
  hire_TA(&student_list, "Jenny", "Money");

  if (hire_TA(&student_list, "Jenny", "Money") != 0) {
    printf("Bug Found: your duplicate entry was added!\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #3!\n");
}

/* tests adding to the list with null params */
static void test4(void) {
  TA_list student_list;
  init(&student_list);

  if (hire_TA(&student_list, NULL, "Bloomberg") != 0 ||
      hire_TA(&student_list, "Chris", NULL) != 0) {
    printf("Bug Found: null params were not dealt with\n");
    exit(FOUND_BUG);
  }

  if (hire_TA(&student_list, NULL, NULL) != 0) {
    printf("Bug Found: null params were not dealt with\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #4!\n");
}

/* WE ARE TESTING NUM_TAS() NOW*********************************************** */

/* tests the number of TAs with zero and one element */
static void test5(void) {
  TA_list student_list;
  init(&student_list);

  if(num_TAs(student_list) != 0) {
    printf("Bug Found: num_TAs() didn't return correct amount!\n");
    exit(FOUND_BUG);
  }

  hire_TA(&student_list, "Chris", "Bloomberg");
  if(num_TAs(student_list) != 1) {
    printf("Bug Found: num_TAs() didn't return correct amount!\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #5!\n");
}

/* tests the number of TAs with five elements */
static void test6(void) {
  TA_list student_list;
  init(&student_list);

  hire_TA(&student_list, "Ryan", "Weasley");
  hire_TA(&student_list, "Harry", "Potter");
  hire_TA(&student_list, "Ginny", "Weasley");
  hire_TA(&student_list, "Hermione", "Granger");

  if(num_TAs(student_list) != 4) {
    printf("Bug Found: num_TAs should've printed four\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #6!\n");
}

/* WE ARE TESTING LOOKUP_TA() NOW******************************************** */

/* tests finding TA in an empty list */
static void test7(void) {
  
  TA_list student_list;
  int id = -1;
  init(&student_list);

  if(lookup_TA(student_list, "Mary", "Folly", &id) != -1) {
    printf("Bug Found: lookup_TA() didn't return correct number\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #7!\n");
}

/* tests finding TA in a list of one/two elements */
static void test8(void) {
  
  TA_list student_list;
  int id = -1;
  init(&student_list);
  hire_TA(&student_list, "Cocoa", "Bear");
  
  if(lookup_TA(student_list, "Cocoa", "Bear", &id) != 1) {
    printf("Bug Found: lookup_TA() didn't find Cocoa Bear\n");
    exit(FOUND_BUG);
  }

  hire_TA(&student_list, "Double-Cocoa", "Bear");
  
  if(lookup_TA(student_list, "Cocoa", "Bear", &id) != 1) {
    printf("Bug Found: lookup_TA() didn't find Cocoa Bear\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #8!\n");
}

/* tests finding TA in a list of multiple TAs */
static void test9(void) {

  TA_list student_list;
  int id = -1;
  init(&student_list);

  hire_TA(&student_list, "John", "Lennon");
  hire_TA(&student_list, "Paul", "McCartney");
  hire_TA(&student_list, "George", "Harrison");
  hire_TA(&student_list, "Ringo", "Starr");

  if(lookup_TA(student_list, "Paul", "McCartney", &id) != 1) {
    printf("Bug Found: lookup() didn't find Paul McCartney\n");
    exit(FOUND_BUG);
  }
  if(lookup_TA(student_list, "Ringo", "Starr", &id) != 1) {
    printf("Bug Found: lookup() didn't find Ringo Starr\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #9!\n");
}    

/* tests lookup_TA() up TAs who don't exist */
static void test10(void) {

  TA_list student_list;
  int id = -1;
  init(&student_list);

  hire_TA(&student_list, "John", "Lennon");
  hire_TA(&student_list, "Paul", "McCartney");

  if(lookup_TA(student_list, "Paul", "Garrison", &id) != -1) {
    printf("Bug Found: lookup() returned the wrong number\n");
    exit(FOUND_BUG);
  }
  if(lookup_TA(student_list, "Tor*by", "McCartney", &id) != -1) {
    printf("Bug Found: lookup() returned the wrong number\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #10!\n");
}

/* tests lookup_TA() where first_name == NULL, search for last */
static void test11(void) {
  TA_list student_list;
  int id = -1;
  init(&student_list);

  hire_TA(&student_list, "A-list", "McCartney");
  hire_TA(&student_list, "B-list", "McCartney");
  hire_TA(&student_list, "C-list", "McCartney");

  if(lookup_TA(student_list, NULL, "McCartney", &id) != 3) {
    printf("Bug Found: lookup_TA() didn't handle fn = null correctly\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #11!\n");
}

/* tests lookup_TA() with null parameters */
static void test12(void) {
  TA_list student_list;
  int new_id = 14;
  init(&student_list);

  if(lookup_TA(student_list, "Anna", NULL, &new_id) != 0
     || lookup_TA(student_list, "Anna", "Blender", NULL) != 0
     || lookup_TA(student_list, "Anna", NULL, NULL) != 0) {
    printf("Bug Found: lookup() didn't handle null properly\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #12!\n");
}

/* WE ARE TESTING SET_SALARY() NOW******************************************* */

/* tests set_salary() with TA list of empty list and one element */
static void test13(void) {

  TA_list student_list;
  init(&student_list);

  if(set_salary(student_list, 1, 9.50) != 0) {
    printf("Bug Found: set_salary() returned 1 for empty list\n");
    exit(FOUND_BUG);
  }

  hire_TA(&student_list, "Chris", "Blender");
  if(set_salary(student_list, 1, 9.50) != 1) {
    printf("Bug Found: set_salary() failed to set the salary\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #13!\n");
}

/* tests set_salary with TA list of three elements */
static void test14(void) {

  TA_list student_list;
  init(&student_list);

  hire_TA(&student_list, "Brook", "Bands");
  hire_TA(&student_list, "Sandy", "Coatails");
  hire_TA(&student_list, "Rose", "Petals");

  if(set_salary(student_list, 1, 12.50) != 1
     || set_salary(student_list, 3, 12.50) != 1) {
    printf("Bug Found: set_salary() failed to set the salary\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #14!\n");
}

/* tests set_salary with TA that doesn't exist */
static void test15(void) {

  TA_list student_list;
  init(&student_list);

  hire_TA(&student_list, "Aplus", "student");
  hire_TA(&student_list, "Bplus", "student");
  
  if(set_salary(student_list, 4, 11.75) != 0) {
    printf("Bug Found: set_salary() found nonexistent TA\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #15!\n");
}

/* tests set_salary with null/invalid parameters */
static void test16(void) {

  TA_list student_list;
  init(&student_list);

  if(set_salary(student_list, -5, 10.50) != 0) {
    printf("Bug Found: set_salary() didn't handle empty list\n");
    exit(FOUND_BUG);
  }
  if(set_salary(student_list, 0, -8.90) != 0
     || set_salary(student_list, 20, -12.50) != 0) {
    printf("Bug Found: set_salary() didn't handle null properly\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #16!\n");
}


/* WE ARE TESTING GET_SALARY() NOW******************************************* */

/* tests get_salary() for TA list with two elements */
static void test17(void) {

  TA_list student_list;
  init(&student_list);

  hire_TA(&student_list, "Sister", "BORNS");
  hire_TA(&student_list, "Brother", "BORNS");
  set_salary(student_list, 2, 9.50);

  if(get_salary(student_list, 1) != 0.0
     || get_salary(student_list, 2) != 9.50) {
    printf("Bug Found: get_salary got the wrong amount\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #17!\n");
}

/* tests get_salary() for returning zero cases */
static void test18(void) {

  TA_list student_list;
  init(&student_list);

  hire_TA(&student_list, "Mary", "Blender");
  set_salary(student_list, 1, 7.50);

  if(get_salary(student_list, 1) != 7.50
    || get_salary(student_list, 2) != 0.0) {
    printf("Bug Found: get_salary() returned the wrong amount\n");
    exit(FOUND_BUG);
  }

  if(get_salary(student_list, -12) != 0.0
     || get_salary(student_list, 12) != 0.0) {
    printf("Bug Found: get_salary() didn't handle invalid params\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #18!\n");
}

/* WE ARE TESTING FIRE_TA() NOW********************************************** */

/* tests fire_TA() by resetting list with one element */
static void test19(void) {

  TA_list student_list;
  init(&student_list);

  hire_TA(&student_list, "Barr", "Brothers");
  fire_TA(&student_list, 1);

  if(num_TAs(student_list) != 0) {
    printf("Bug Found: the Barr Brothers were not removed\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #19!\n");
}

/* tests fire_TA() by removing 2/3 elements */
static void test20(void) {

  TA_list student_list;
  init(&student_list);

  hire_TA(&student_list, "Bamboo", "Monkey");
  hire_TA(&student_list, "Baby", "Panda");
  hire_TA(&student_list, "Red", "Panda");

  if(fire_TA(&student_list, 2) != 1 || fire_TA(&student_list, 2) != 0
     || fire_TA(&student_list, 3) != 1) {
    printf("Bug Found: both Monkey and Panda were not fired\n");
    exit(FOUND_BUG);
  }
  if(num_TAs(student_list) != 1) {
    printf("Bug Found: fire_TA() didn't remove two elements\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #20!\n");   
}

/* tests fire_TA() by removing non-existent elements */
static void test21(void) {

  TA_list student_list;
  init(&student_list);

  if(fire_TA(&student_list, 3) != 0) {
    printf("Bug Found: fire_TA() returned the wrong number\n");
    exit(FOUND_BUG);
  }
  hire_TA(&student_list, "Purple", "Panda");
  hire_TA(&student_list, "Blue", "Panda");
  if(fire_TA(&student_list, 4) != 0) {
    printf("Bug Found: fire_TA() fired non-existent TA\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #21!\n");
}

/* tests fire_TA() for null/invalid params */
static void test22(void) {

  TA_list student_list;
  init(&student_list);

  if(fire_TA(&student_list, 0) != 0 || fire_TA(&student_list, -6) != 0) {
    printf("Bug Found: fire_TA() didn't handle null correctly\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #22!\n");
}

/* tests fire_TA() for removing 2 singular elements */
static void test23(void) {

  TA_list student_list;
  init(&student_list);

  hire_TA(&student_list, "AreWeDone", "YET");
  hire_TA(&student_list, "Nope", "StillGoing");
  
  if(fire_TA(&student_list, 1) != 1 || fire_TA(&student_list, 1) != 1) {
    printf("Bug Found: couldn't delete all items from list\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #23!\n");  
}

/* WE ARE TESTING RESET() NOW************************************************ */

/* tests reset() by resetting one element */
static void test24(void) {

  TA_list student_list;
  init(&student_list);

  hire_TA(&student_list, "frank", "sinatra");
  reset(&student_list);
  hire_TA(&student_list, "frank", "sinatra2");

  if(num_TAs(student_list) != 1) {
    printf("Bug Found: list was not reset properly\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #24!\n");
}

/* tests reset with an empty list */
static void test25(void) {

  TA_list student_list;
  init(&student_list);

  reset(&student_list);
  reset(&student_list);

  if(num_TAs(student_list) != 0) {
    printf("Bug Found: there should be zero TAs here\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #25!\n");
}

/* tests reset() with an outrageous number of elements */
static void test26(void) {

  TA_list student_list;
  init(&student_list);

  hire_TA(&student_list, "Tigger", "Tiger");
  hire_TA(&student_list, "Pooh", "Bear");
  hire_TA(&student_list, "Mini", "piglet");
  hire_TA(&student_list, "greyyy", "Eyeore");
  hire_TA(&student_list, "somethin", "crazy");

  fire_TA(&student_list, 3); 
  if(num_TAs(student_list) != 4) {
    printf("Bug Found: number of TAs in list is incorrect\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #26!\n");
}

/* WE'RE DOING ADDITIONAL TESTS NOW****************************************** */

/* test hiring duplicate TAs and lookup_TA() again */
static void test27(void) {

  TA_list student_list;
  int new_id = 2;
  init(&student_list);

  hire_TA(&student_list, "Orange", "Cheeto");
  hire_TA(&student_list, "Buffy", "Cheeto");
  hire_TA(&student_list, "Buffy", "Cheeto");
  
  if(lookup_TA(student_list, NULL, "Cheeto", &new_id) != 2) {
    printf("Bug Found: lookup_TA() returned the wrong number\n");
    exit(FOUND_BUG);
  }
  printf("You passed student test #27!\n");
}

/* tests complex set_salary() and get_salary() situation */
static void test28(void) {

  TA_list student_list;
  init(&student_list);

  hire_TA(&student_list, "bank", "deposit-1");
  hire_TA(&student_list, "bank", "deposit-2");

  set_salary(student_list, 1, 22.50);
  set_salary(student_list, 2, -16.50);

  if(num_TAs(student_list) != 2 || get_salary(student_list, 1) != 22.50
     || get_salary(student_list, 2) != 0.0) {
    printf("Bug Found: bank salaries were not set correctly\n");
    exit(FOUND_BUG);
  }
  
  reset(&student_list);
  printf("You passed student test #28!\n");
}
