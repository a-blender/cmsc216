#include <stdio.h>

#define MAX_LEN 20

int data[MAX_LEN];

void reverse_prefix_sum(int *a, int size, int total) {
   if (size != 0)  {
      *a += total;
      reverse_prefix_sum(a - 1, size - 1, *a);  
   }
}

void print_array(int *a) {
   while (*a != -1) {
      printf("%d ", *a);
      a++;
   }
   printf("\n");
}

int read_array(int *a) {
   /* You must define and use size as a local variable  */ 
   /* (similar to what you did in main).                */
   int size = 0; 

   scanf("%d", a);  
   while (*a++ != -1) {
      size++;
      scanf("%d", a);  
   }

   return size;
}

int main() {
   /* You must implement a main function that defines and makes use */
   /* of two local variables (array_size and start_point). That     */
   /* means that the beginning of main will reserve space on the    */
   /* on the stack for these two variables.                         */

   int array_size = read_array(data);
   int *start_point = data + array_size - 1; 

   reverse_prefix_sum(start_point, array_size, 0);
   print_array(data);

   return 0; 
}
