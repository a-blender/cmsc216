#if !defined(MY_MEMORY_CHECKER_216)
#define MY_MEMORY_CHECKER_216

void start_memory_check(); 
int stop_memory_check();   /* returns 0 if no leaks. -1 if leaks. */

#endif
