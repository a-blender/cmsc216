#include <stdio.h>

#define MAX_CHARACTERS 20

char array[MAX_CHARACTERS];

int main() {
   int data_length, i;

   for (i = 0; i < MAX_CHARACTERS; i++) {
      scanf("%c", &array[i]);
      if (array[i] == '\n') {
         break;
      }
   }
   data_length = i;

   for (i = 0; i < data_length / 2; i++) {
      if (array[i] != array[data_length - i - 1]) {
         printf("N\n");
         return 0;
      }
   }

   printf("Y\n");

   return 0;
}
