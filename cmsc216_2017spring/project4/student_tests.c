/* STUDENT TESTS by Anna Blendermann, ablender, 114474025 */
/* this program tests calendar.c for functional and logic errors */
#include <stdio.h>
#include <stdlib.h>
#include "event.h"
#include "calendar.h"
#include "my_memory_checker_216.h"

static int comp_minutes(const void *ptr1, const void *ptr2) {
   return ((Event *)ptr1)->duration_minutes - ((Event *)ptr2)->duration_minutes;
}

/* TEST 1************************************************************************ */
/* tests initializing, printing, and destroying an empty calendar */
static int test1() {
   Calendar *calendar;
   int days = 7, status = FAILURE;

   if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      if (destroy_calendar(calendar) == SUCCESS) {
          status = SUCCESS;
      }
   }
   return status;
}

/* TEST 2*********************************************************************** */
/* tests adding one event to each day of the calendar */
static int test2() {
    Calendar *calendar;
    int days = 2, status = FAILURE;

    if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        if (add_event(calendar, "day #1 meeting", 500, 60, NULL, 1) == SUCCESS &&
            add_event(calendar, "day #2 meeting", 500, 60, NULL, 2) == SUCCESS) {
            status = SUCCESS;
        }
        if (destroy_calendar(calendar) == FAILURE) {
            status = FAILURE;
        }
    }
    return status;
}

/* TEST 3*********************************************************************** */
/* tests adding multiple events to random calendar days */
static int test3() {
    Calendar *calendar;
    int days = 5, status = FAILURE;

    if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        if ((add_event(calendar, "brunch w/ john", 800, 60, NULL, 2) == SUCCESS) &&
            (add_event(calendar, "blind date", 800, 80, NULL, 2) == SUCCESS) &&
            (add_event(calendar, "festival", 800, 120, NULL, 4) == SUCCESS) &&
            (add_event(calendar, "recital", 800, 120, NULL, 5)) == SUCCESS) {
            status = SUCCESS;
        }
        if (destroy_calendar(calendar) == FAILURE) {
            status = FAILURE;
        }
    }
    return status;
}

/* TEST 4*********************************************************************** */
/* tests adding events with duplicate names to the calendar */
static int test4() {
    Calendar *calendar;
    int days = 5, status = FAILURE;

    if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {
        add_event(calendar, "girls night", 800, 60, NULL, 2);

        if (add_event(calendar, "girls night", 800, 80, NULL, 2) == FAILURE &&
            (add_event(calendar, "girls night", 800, 80, NULL, 5) == FAILURE)) {
            status = SUCCESS;
        }
        if (destroy_calendar(calendar) == FAILURE) {
            status = FAILURE;
        }
    }
    return status;
}

/* TEST 5*********************************************************************** */
/* tests finding two events that are present in the calendar */
static int test5() {
    Calendar *calendar;
    Event *event;
    int days = 5, status = FAILURE;

    if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        add_event(calendar, "event 1", 800, 60, NULL, 1);
        add_event(calendar, "event 2", 800, 60, NULL, 3);

        if (find_event(calendar, "event 1", &event) == SUCCESS &&
            find_event(calendar, "event 2", &event) == SUCCESS) {
            status = SUCCESS;
        }
        if (destroy_calendar(calendar) == FAILURE) {
            status = FAILURE;
        }
    }
    return status;
}

/* TEST 6*********************************************************************** */
/* tests finding two events that aren't in the calendar */
static int test6() {
    Calendar *calendar;
    Event *event;
    int days = 5, status = FAILURE;

    if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        add_event(calendar, "event 1", 800, 60, NULL, 1);
        add_event(calendar, "event 2", 800, 60, NULL, 3);

        if (find_event(calendar, "wrong event", &event) == FAILURE &&
            find_event(calendar, "upside down dog", &event) == FAILURE) {
            status = SUCCESS;
        }
        if (destroy_calendar(calendar) == FAILURE) {
            status = FAILURE;
        }
    }
    return status;
}

/* TEST 7*********************************************************************** */
/* tests finding one event in a specific day of the calendar */
static int test7() {
    Calendar *calendar;
    Event *event;
    int days = 5, status = FAILURE;

    if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {
        add_event(calendar, "puppy", 800, 60, NULL, 4);

        if (find_event_in_day(calendar, "puppy", 3, &event) == FAILURE &&
            find_event_in_day(calendar, "puppy", 4, &event) == SUCCESS) {
            status = SUCCESS;
        }
        if (destroy_calendar(calendar) == FAILURE) {
            status = FAILURE;
        }
    }
    return status;
}

/* TEST 8*********************************************************************** */
/* tests removing events from the front/end of a list */
static int test8() {
    Calendar *calendar;
    int days = 5, status = FAILURE;

    if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {
        add_event(calendar, "puppy 1", 800, 60, NULL, 1);
        add_event(calendar, "puppy 2", 800, 80, NULL, 1);
        add_event(calendar, "zen puppy", 800, 120, NULL, 1);

        if (remove_event(calendar, "puppy 1") == SUCCESS &&
            remove_event(calendar, "zen puppy") == SUCCESS) {
            status = SUCCESS;
        }
        if (destroy_calendar(calendar) == FAILURE) {
            status = FAILURE;
        }
    }
    return status;
}

/* TEST 9*********************************************************************** */
/* tests removing an event from the middle of a list */
static int test9() {
    Calendar *calendar;    
    int days = 5, status = FAILURE;

    if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {
        add_event(calendar, "puppy 1", 800, 60, NULL, 1);
        add_event(calendar, "puppy 2", 800, 80, NULL, 1);
        add_event(calendar, "zen puppy", 800, 120, NULL, 1);

        if (remove_event(calendar, "puppy 2") == SUCCESS) {
            status = SUCCESS;
        }
        if (destroy_calendar(calendar) == FAILURE) {
            status = FAILURE;
        }
    }
    return status;
}

/* TEST 10*********************************************************************** */
/* tests finding/removing events from an empty calendar */
static int test10() {
    Calendar *calendar;
    Event *event;
    int days = 5, status = FAILURE;

    if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        if (find_event(calendar, "small rabbit", &event) == FAILURE &&
            remove_event(calendar, "small puppy") == FAILURE) {
            status = SUCCESS;
        }
        if (destroy_calendar(calendar) == FAILURE) {
            status = FAILURE;
        }
    }
    return status;
}

/* TEST 11*********************************************************************** */
/* tests clearing calendar without destroying the Events array */
static int test11() {
    Calendar *calendar;
    int days = 5, status = FAILURE;

    if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        add_event(calendar, "meeting 1", 800, 60, NULL, 1);
        add_event(calendar, "meeting 2", 800, 60, NULL, 2);
        add_event(calendar, "meeting 3", 800, 100, NULL, 5);

        if (clear_calendar(calendar) == SUCCESS) {
            status = SUCCESS;
        }
        if (destroy_calendar(calendar) == FAILURE) {
            status = FAILURE;
        }
    }
    return status;
}

/* TEST 12*********************************************************************** */
/* tests clearing two days (free Event linked lists) */
static int test12() {
    Calendar *calendar;
    int days = 5, status = FAILURE;

    if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        add_event(calendar, "meeting 1", 800, 60, NULL, 1);
        add_event(calendar, "meeting 2", 800, 60, NULL, 2);
        add_event(calendar, "meeting 3", 800, 100, NULL, 5);

        if (clear_day(calendar, 1) == SUCCESS &&
            clear_day(calendar, 2) == SUCCESS) {
            status = SUCCESS;
        }
        if (destroy_calendar(calendar) == FAILURE) {
            status = FAILURE;
        }
    }
    return status;
}

/* TEST 13*********************************************************************** */
/* tests clearing days/calendar from an empty calendar */
static int test13() {
    Calendar *calendar;
    int days = 5, status = FAILURE;

    if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {

        /* these won't clear anything but should return success */
        if (clear_calendar(calendar) == SUCCESS &&
            clear_day(calendar, 1) && clear_day(calendar, 4)) {
            status = SUCCESS;
        }
        if (destroy_calendar(calendar) == FAILURE) {
            status = FAILURE;
        }
    }
    return status;
}

/* MAIN METHOD******************************************************************** */
/* this main method runs the student tests on calendar.c */
int main() {
   int result = SUCCESS;

   /***** Starting memory checking *****/
   start_memory_check();
   /***** Starting memory checking *****/

   printf("Running student test 1...\n");
   if (test1() == FAILURE) {
      printf("You failed student test 1.\n");
      result = FAILURE;
   }
   else printf("You passed student test 1!\n");

   printf("Running student test 2...\n");
   if (test2() == FAILURE) {
      printf("You failed student test 2.\n");
      result = FAILURE;
   }
   else printf("You passed student test 2!\n");

   printf("Running student test 3...\n");
   if (test3() == FAILURE) {
      printf("You failed student test 3.\n");
      result = FAILURE;
   }
   else printf("You passed student test 3!\n");

   printf("Running student test 4...\n");
   if (test4() == FAILURE) {
      printf("You failed student test 4.\n");
      result = FAILURE;
   }
   else printf("You passed student test 4!\n");

   printf("Running student test 5...\n");
   if (test5() == FAILURE) {
      printf("You failed student test 5.\n");
      result = FAILURE;
   }
   else printf("You passed student test 5!\n");

   printf("Running student test 6...\n");
   if (test6() == FAILURE) {
      printf("You failed student test 6.\n");
      result = FAILURE;
   }
   else printf("You passed student test 6!\n");

   printf("Running student test 7...\n");
   if (test7() == FAILURE) {
       printf("You failed student test 7.\n");
      result = FAILURE;
   }
   printf("You passed student test 7!\n");

    printf("Running student test 8...\n");
    if (test8() == FAILURE) {
        printf("You failed student test 8.\n");
        result = FAILURE;
    }
    else printf("You passed student test 8!\n");

    printf("Running student test 9...\n");
    if (test9() == FAILURE) {
        printf("You failed student test 9.\n");
        result = FAILURE;
    }
    else printf("You passed student test 9!\n");

    printf("Running student test 10...\n");
    if (test10() == FAILURE) {
        printf("You failed student test 10.\n");
        result = FAILURE;
    }
    else printf("You passed student test 10!\n");

    printf("Running student test 11...\n");
    if (test11() == FAILURE) {
        printf("You failed student test 11.\n");
        result = FAILURE;
    }
    else printf("You passed student test 11!\n");

    printf("Running student test 12...\n");
    if (test12() == FAILURE) {
        printf("You failed student test 12.\n");
        result = FAILURE;
    }
    else printf("You passed student test 12!\n");

    printf("Running student test 13...\n");
    if (test13() == FAILURE) {
        printf("You failed student test 13.\n");
        result = FAILURE;
    }
    else printf("You passed student test 13!\n");

   /****** Gathering memory checking info *****/
   stop_memory_check();
   /****** Gathering memory checking info *****/
   
   if (result == FAILURE) {
      printf("Dude. You didn't pass some tests, check again.\n");
      exit(EXIT_FAILURE);
   }
   printf("Your student tests for project4 were successful!\n");
   return EXIT_SUCCESS;
}
