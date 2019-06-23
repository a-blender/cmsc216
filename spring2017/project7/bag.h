#if !defined(BAG_H)
#define BAG_H

/* (c) Larry Herman and Nelson Padua-Perez, 2015.  You are allowed to use
 * this code yourself, but not to provide it to anyone else.
 */

#include "bag-implementation.h"

#define CORRECT 1
#define FOUND_BUG 2

void init_bag(Bag *bag);
void add_to_bag(Bag *bag, const char *element);
size_t size(Bag bag);
int count(Bag bag, const char *element);
int remove_occurrence(Bag *bag, const char *element);
int remove_from_bag(Bag *bag, const char *element);
Bag bag_union(Bag bag1, Bag bag2);
int is_sub_bag(Bag bag1, Bag bag2);
void clear_bag(Bag *bag);

#endif
