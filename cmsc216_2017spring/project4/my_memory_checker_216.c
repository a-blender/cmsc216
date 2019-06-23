#include <stdio.h>
#include <stdlib.h>
#include <mcheck.h>
#include <malloc.h>

#include "my_memory_checker_216.h"

int global_memory_checker_usage;

void start_memory_check() {
   mcheck_pedantic(NULL);
   global_memory_checker_usage = mallinfo().uordblks;
}

int stop_memory_check() {
   int ret = 0;

   global_memory_checker_usage = mallinfo().uordblks - global_memory_checker_usage;
   if (global_memory_checker_usage) { 
      printf("ERROR: memory leak detected (%d bytes)\n", global_memory_checker_usage);
      ret = -1;
   }
   mcheck_check_all();

   return ret;
}
