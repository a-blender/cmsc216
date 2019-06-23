/* GRADES by Anna Blendermann, 114474025, ablender */

/* this program computes the numeric score for one student based upon */
/* assign scores, weights, late penalties, and assigns dropped */

/* data structure: data is scanned into a single-array where every four */
/* indexes represents one line (id, score, weight, days late) */

/* program function: array is traversed using for loops, incremented */
/* using x = x+4 to grab/organize data and compute the numeric score, */
/* mean, and standard deviation of the scores */

#include <stdio.h>
#include <math.h>
#define MAX_ASSIGNS 50

static double compute_score(int array[], int num, int late, int drop);
static void drop_scores(int array[], int num, int drop);
static double compute_mean(int array[], int num_assigns, int late);
static double compute_sd(int array[], int num_assigns, int late);
static void print_output(int arr[], int num, int late, int drop, char stats);

/* SCORE METHOD************************************************************ */
/* computes the numeric score by dropping assignments first, and then */
/* calculates the course grade based on assigns/weights/late penalties */
static double compute_score(int array[], int num, int late, int drop) {
   int x, assign_late;
   double weight_sum = 0, score = 0;

   /* drop "x number" of lower scores, if drop > 0 */
   if (drop > 0) {
      drop_scores(array, num, drop);
   }

   /* get the weight sum, in case assignments were dropped */
   for (x = 0; x < (num*4); x+=4) {
	 weight_sum += array[x+2];
   }

   /* check that the weight sum isn't over 100 */
   if (weight_sum > 100.0) {
      printf("ERROR: Invalid values provided\n");
      return -1;
   }
   else {
      /* calculate each numeric score */
      for (x = 0; x < (num*4); x+=4) {

	 assign_late = array[x+1] - array[x+3] * late;
	 if (assign_late > 0) {
	    score += assign_late * (array[x+2] / weight_sum);
	 }
      }
   }
   return score;
}

/* DROP SCORES************************************************************ */
/* drops assigns from the copy array by setting weights to 0 */
void drop_scores(int array[], int num, int drop) {
   int x, min, value, count = 0, drop_index = 0;

   /* drop number of lowest assignments given */
   while (count++ < drop) {

      /* find the lowest assignment score */
      min = array[1] * array[2];
      for (x = 0; x < (num * 4); x += 4) {
	 
	 value = array[x+1] * array[x+2];

	 /* check to make sure the assign weight isn't already 0 */
	 if (value != 0) {

	    /* find lower assign or same assign with lower id */
	    if (value < min || (value == min && x < drop_index)) {
	       min = value;
	       drop_index = x;
	    }
	 }
      }
      /* set the weight equal to 0 (so the value will drop) */
      array[drop_index + 2] = 0;
   }
}

/* COMPUTE MEAN************************************************************ */
/* computes the mean of assign values where (value = score * weight), */
/* and takes late penalties into account */
static double compute_mean(int array[], int num_assigns, int late) {
   int x;
   double mean, sum_scores = 0;

   /* compute the mean of all assign scores */
   for (x = 0; x < (num_assigns * 4); x += 4) {
      sum_scores += (array[x+1] - (array[x+3])*late);
   }
   mean = (sum_scores / num_assigns);
   return mean;
}

/* COMPUTE SD************************************************************* */
/* computes the standard deviation of assign values where (value = */
/* score * weight), takes late penalties into account */
static double compute_sd(int array[], int num_assigns, int late) {
   int x, score;
   double mean, sum = 0, variance, standard_dev;
   mean = compute_mean(array, num_assigns, late);

   /* compute variance and standard deviation */
   for (x = 0; x < (num_assigns * 4); x += 4) {
      score = array[x+1] - (array[x+3] * late);
      sum += pow((score - mean), 2);
   }
   variance = sum / (float) num_assigns;
   standard_dev = sqrt(variance);
   
   return standard_dev;
}

/* PRINT OUTPUT*********************************************************** */
/* prints program output in the following order -> numeric score, late */
/* penalties, assigns dropped, assign list, stats (optional) */
static void print_output(int arr[], int num, int late, int drop, char stats) {
   int x, count = 1, arr2[MAX_ASSIGNS * 4] = {0};
   double score, mean = 0, sd = 0;
   
   /* compute numeric score using a copy of the original array */
   for (x = 0; x < (num * 4); x++) {
      arr2[x] = arr[x];
   }
   if (drop >= 0 && drop < num)
      score = compute_score(arr2, num, late, drop);
   else score = 0;

   /* print Numeric Score, Late Penalty Points, and Assigns Dropped */
   printf("Numeric Score: %5.4f\n", score);
   printf("Points Penalty Per Day Late: %d\n", late);
   printf("Number of Assignments Dropped: %d\n", drop);

   /* print log of assignments submitted */
   printf("Values Provided:\nAssignment, Score, Weight, Days Late\n");

   /* print in groups of four from the next largest num */
   while (count <= num) {

      for (x = 0; x < (num * 4); x += 4) {
	 if (arr[x] == count) {
	    printf("%d, %d, %d, %d\n", arr[x], arr[x+1], arr[x+2], arr[x+3]);
	 }
      }
      count = count + 1;
   }
   
   /* print extra stats if the input character was yes (Y or y */
   if (stats == 'Y' || stats == 'y') {
      mean = compute_mean(arr, num, late);
      sd = compute_sd(arr, num, late);
      printf("Mean: %5.4f, Standard Deviation: %5.4f\n", mean, sd);
   }
}

/* MAIN METHOD************************************************************* */
/* driver for the grades.c program, scans stdin/user input and calls the */
/* print_output function */
int main(void) {
   int x = 0, penalty, dropped, num_assigns;
   int arr[MAX_ASSIGNS * 4] = {0};
   char stats;

   /* 1. scan and store the assignment info from stdin */
   scanf("%d %d %c\n", &penalty, &dropped, &stats);
   scanf("%d\n", &num_assigns);

   while (x < (num_assigns * 4)) {
      scanf("%d,%d,%d,%d\n", &arr[x], &arr[x+1], &arr[x+2], &arr[x+3]);
      x = x + 4;
   }
   
   /* 2. compute and print the numeric score, assigns, and stats */
   if (num_assigns >= 0 && penalty >= 0 && dropped >= 0) {
      print_output(arr, num_assigns, penalty, dropped, stats);
   }
   return 0;
}


