#if !defined(CALENDAR_H)
#define CALENDAR_H

#include "event.h"

#define SUCCESS 0
#define FAILURE -1

typedef struct calendar {
   char *name;
   Event **events;
   int days, total_events;
   int (*comp_func) (const void *ptr1, const void *ptr2);
   void (*free_info_func) (void *ptr);
} Calendar;

int init_calendar(const char *name, int days,
                  int (*comp_func) (const void *ptr1, const void *ptr2),
                  void (*free_info_func) (void *ptr), Calendar ** calendar);
int print_calendar(Calendar *calendar, FILE *output_stream, int print_all);
int add_event(Calendar *calendar, const char *name, int start_time,
              int duration_minutes, void *info, int day);
int find_event(Calendar *calendar, const char *name, Event **event);
int find_event_in_day(Calendar *calendar, const char *name, int day,
                      Event **event);
int remove_event(Calendar *calendar, const char *name);
void *get_event_info(Calendar *calendar, const char *name);
int clear_calendar(Calendar *calendar);
int clear_day(Calendar *calendar, int day);
int destroy_calendar(Calendar *calendar);

#endif
