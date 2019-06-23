#include <stdio.h>

/* (c) Larry Herman, 2016.  You are allowed to use this code yourself, but
   not to provide it to anyone else. */

static int count(int max, int value, int from);

int arr[100], x, size, element, start;

int main() {
  scanf("%d", &x);

  while (x != 0) {
    if (size < 100) {
      arr[size]= x;
      size++;
    }

    scanf("%d", &x);
  }

  scanf("%d", &element);
  scanf("%d", &start);

  printf("%d\n", count(size, element, start));

  return 0;
}

static int count(int max, int value, int from) {
  int i, answer= 0;

  if (max < 0 || from < 0 || from >= max)
    answer= -1;
  else
    for (i= from; i < max; i++)
      if (arr[i] == value)
        answer++;

  return answer;
}
