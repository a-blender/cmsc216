#if !defined(EVENT_H)
#define EVENT_H

typedef struct event {
   char *name;
   int start_time, duration_minutes;
   void *info;
   struct event *next;
} Event;

#endif
