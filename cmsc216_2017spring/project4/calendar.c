/* CALENDAR by Anna Blendermann, ablender, 114474025 */
/* this program enables the user to build a calendar data structure and */
/* add, find, remove events as desired, then destroy the calendar */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"
#include "calendar.h"

/* INIT CALENDAR******************************************************************* */
/* initializes a Calendar structure based on the parameters provided */
int init_calendar(const char *name, int days,
		  int (*comp_func) (const void *ptr1, const void *ptr2),
		  void (*free_info_func) (void *ptr), Calendar ** calendar) {

    /* check that calendar and name aren't null, and days is valid */
    if ((*calendar) && name && days >= 1) {
        (*calendar) = malloc(sizeof(Calendar));

        /* check if return value of malloc was successful */
        if (calendar) {

            /* allocate memory for and initialize "name" */
            (*calendar)->name = malloc(sizeof(char) * (strlen(name) + 1));
            strcpy((*calendar)->name, name);

            /* allocate memory for Events array based on "days," and set to null */
            (*calendar)->events = calloc(days, sizeof(Event));

            /* initialize "days" and "total events" */
            (*calendar)->days = days;
            (*calendar)->total_events = 0;

            /* initialize the function pointers with our parameters */
            (*calendar)->comp_func = comp_func;
            (*calendar)->free_info_func = free_info_func;
            return SUCCESS;
        }
    }
    return FAILURE;
}

/* PRINT CALENDAR****************************************************************** */
/* prints, to the output stream, the calendar's name, days, and events */
int print_calendar(Calendar *calendar, FILE *output_stream, int print_all) {
    Event *event_ptr;
    int x = 0;

    /* check that calendar and output_stream aren't null */
    if (calendar && output_stream) {

        /* if "print_all" is true, the print calendar info */
        if (print_all) {
            fprintf(output_stream, "Calendar's Name: \"%s\"\n", calendar->name);
            fprintf(output_stream, "Days: %d\n", calendar->days);
            fprintf(output_stream, "Total Events: %d\n\n", calendar->total_events);
        }
        /* print Events header regardless of status of "print_all" */
        fprintf(output_stream, "**** Events ****\n");

        /* print Events info (if any) regardless of status of "print_all" */
        if (calendar->total_events > 0) {

            /* iterate through each day of the calendar */
            for (x = 0; x < calendar->days; x++) {
                printf("Day %d\n", x + 1);

                /* iterate through each event on that particular day */
                event_ptr = calendar->events[x];
                while (event_ptr) {
                    fprintf(output_stream, "Event's Name: \"%s\", ", event_ptr->name);
                    fprintf(output_stream, "Start_time: %d, ", event_ptr->start_time);
                    fprintf(output_stream, "Duration: %d\n", event_ptr->duration_minutes);
                    event_ptr = event_ptr->next;
                }
            }
        }
        return SUCCESS;
    }
    return FAILURE;
}

/* ADD EVENT******************************************************************** */
/* adds the specified event to the list associated with the day parameter */
int add_event(Calendar *calendar, const char *name, int start_time,
	      int duration_minutes, void *info, int day) {
    Event *new_event, *prev_ptr, *event_ptr;
    Event *event; /* temp event to use for find_event */

    /* check that calendar and name aren't null, and start_time is valid */
    if (calendar && name && (start_time >= 0 && start_time <= 2400)) {

        /* check that duration_minutes and day parameters have valid ranges */
        /* also fails if event exists or memory allocation fails */
        if (duration_minutes > 0 && day > 0 && day <= calendar->days) {
            if (find_event(calendar, name, &event) == FAILURE) {

                /* allocate memory for the new_event and the event's name */
                new_event = malloc(sizeof(Event));
                new_event->name = malloc(sizeof(char) * (strlen(name) + 1));

                /* create new_event based on given parameters */
                strcpy(new_event->name, name);
                new_event->duration_minutes = duration_minutes;
                new_event->start_time = start_time;
                new_event->info = info;

                /* add new_event in increasing order using comp_func */
                /* set event_ptr to linked list of Events to add new_event to */
                event_ptr = calendar->events[day - 1];

                /* no events = add event to start of the list */
                if (event_ptr == NULL) {
                    calendar->events[day - 1] = new_event;
                    new_event->next = NULL;
                }
                    /* events present = add event among other events */
                else if (event_ptr != NULL) {

                    /* event_ptr > target = add event to front of list */
                    if (calendar->comp_func(event_ptr, new_event) > 0) {
                        calendar->events[day - 1] = new_event;
                        new_event->next = event_ptr;
                    }
                        /* else = add event to the middle/end of list */
                    else {
                        prev_ptr = event_ptr;
                        event_ptr = event_ptr->next;
                        while (event_ptr && calendar->comp_func(event_ptr, new_event) <= 0) {
                            prev_ptr = event_ptr;
                            event_ptr = event_ptr->next;
                        }
                        new_event->next = event_ptr;
                        prev_ptr->next = new_event;
                    }
                } /* end of else statement */
                (calendar->total_events)++;
                return SUCCESS;
            }
        }
    }
    return FAILURE;
}

/* FIND EVENT******************************************************************** */
/* returns a pointer to the event with the specified name */
int find_event(Calendar *calendar, const char *name, Event **event) {
    Event *event_ptr;
    int x = 0;

    /* check that calendar and name aren't null */
    if (calendar && name) {
        /* find the event in the calendar based on name */
        for (x = 0; x < calendar->days; x++) {

            event_ptr = calendar->events[x];
            while (event_ptr && strcmp(event_ptr->name, name) != 0) {
                event_ptr = event_ptr->next;
            }
            /* if event_ptr isn't null = event was found, return success */
            if (event_ptr && event) {
                *event = event_ptr;
                return SUCCESS;
            }
        }
    }
    return FAILURE;
}

/* FIND EVENT IN DAY************************************************************** */
/* returns a pointer to the event with the specified name in the specified day */
int find_event_in_day(Calendar *calendar, const char *name, int day,
		      Event **event) {
    Event *event_ptr;
    int x = 0;

    /* check that calendar and name aren't null, and day is valid */
    if (calendar && name && day > 0 && day <= calendar->days) {

        /* find the fucking event in the specified day based on name */
        for (x = 0; x < calendar->days; x++) {
            if ((x + 1) == day) {

                event_ptr = calendar->events[x];
                while (event_ptr && strcmp(event_ptr->name, name) != 0) {
                    event_ptr = event_ptr->next;
                }
                /* if event_ptr isn't null = Event was found, return success */
                if (event_ptr && event) {
                    *event = event_ptr;
                    return SUCCESS;
                }
            }
        } /* end of while loop */
    }
    return FAILURE;
}

/* REMOVE EVENT****************************************************************** */
/* removes the specified event from the calendar and frees allocated memory */
int remove_event(Calendar *calendar, const char *name) {
    Event **event = NULL, *prev_ptr, *event_ptr;
    int x = 0;

    /* check if calendar and name aren't null, and the event exists */
    if (calendar && name && find_event(calendar, name, event) == FAILURE) {

        /* iterate through Event lists in the calendar */
        for (x = 0; x < calendar->days; x++) {
            event_ptr = calendar->events[x];

            /* events present = search for target Event in this list */
            if (event_ptr != NULL) {
                /* event_ptr = target - remove event from front of list */
                if (strcmp(event_ptr->name, name) == 0) {
                    calendar->events[x] = event_ptr->next;
                    event_ptr->next = NULL;
                }
                    /* event_ptr != target - remove event from middle/end of list */
                else {
                    while (event_ptr && strcmp(event_ptr->name, name) != 0) {
                        prev_ptr = event_ptr;
                        event_ptr = event_ptr->next;
                    }
                    /* move previous pointer to event_ptr->next, skip target */
                    prev_ptr->next = event_ptr->next;
                    event_ptr->next = NULL;
                }

                /* remove target Event and free dynamically allocated memory */
                free(event_ptr->name);
                if (calendar->free_info_func) {
                    calendar->free_info_func(event_ptr->info);
                }
                free(event_ptr);

                /* adjust number of total_events and return success */
                (calendar->total_events)--;
                return SUCCESS;
            }
        } /* end of for loop */
    }
    return FAILURE;
}

/* GET EVENT INFO***************************************************************** */
/* returns the info pointer associated with the specified event */
void *get_event_info(Calendar *calendar, const char *name) {
   Event *event;

   /* assume that calendar and name aren't null */
   /* if event is found, return info pointer from that event */
   if (find_event(calendar, name, &event) == FAILURE) {
      return NULL;
   }
   return event->info;
}

/* CLEAR CALENDAR***************************************************************** */
/* removes all event lists associated with the calendar by setting them to empty */
int clear_calendar(Calendar *calendar) {
    int x = 0;

    /* check that calendar isn't null */
    if (calendar) {
        /* clear dynamically allocated events in the calendar */
        for (x = 0; x < calendar->days; x++) {
            clear_day(calendar, (x + 1));
        }
        return SUCCESS;
    }
    return FAILURE;
}

/* CLEAR DAY********************************************************************** */
/* removes all events for the specified day by setting the event list to empty */
int clear_day(Calendar *calendar, int day) {
    Event *temp, *event_ptr;

    /* check that calendar isn't null and day is valid */
    if (calendar && day > 0 && day <= calendar->days) {

        /* run clear_day if there are events to be cleared */
        if (calendar->total_events > 0) {

            /* clear dynamically allocated events on the specified day */
            event_ptr = calendar->events[day - 1];
            while (event_ptr) {
                /* set temp to the current and move event_ptr */
                temp = event_ptr;
                event_ptr = event_ptr->next;

                /* free everything from the previous Event */
                free(temp->name);
                if (calendar->free_info_func && temp->info) {
                    calendar->free_info_func(temp->info);
                }
                free(temp);
                (calendar->total_events)--;
            }
	    calendar->events[day - 1] = NULL;
            return SUCCESS;
        }
    }
    return FAILURE;
}

/* DESTROY CALENDAR************************************************************* */
/* returns memory that was dynamically-allocated for the calendar */
int destroy_calendar(Calendar *calendar) {

    /* check that calendar isn't null */
    if (calendar) {
        /* free the calendar name and Events array */
        free(calendar->name);
        clear_calendar(calendar);
        free(calendar->events);

        /* free the calendar and then return success */
        free(calendar);
        return SUCCESS;
    }
    return FAILURE;
}
