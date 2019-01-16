#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef void (*mem_func)(void*);
typedef struct list list;

typedef struct list_pos
{
    struct node **forward;
    struct node **backward;
} list_pos;

// Deallocate a list after killing all the cells it contains.
void list_kill(list *l);

// Set memhandler for list
void list_set_memhandler(list* l, mem_func mfunc);

// Dynamically allocate an empty list.
list *list_empty(void);

// Returns true iff the list is empty.
bool list_is_empty(list *l);

// Return the position of the first element.
list_pos list_first(list *l);

// Return the position past the end of the list.
list_pos list_end(list *l);

// Return the next position in the list.
list_pos list_next(list *l, list_pos pos);

// Return the previous position in the list.
list_pos list_previous(list *l, list_pos pos);

// Return true iff the position points to the end of the list.
bool list_is_end(list *l, list_pos pos);

// Return true iff the position points to the beginning of the list.
bool list_is_first(list *l, list_pos pos);

// Return the value at the given position.
void* list_inspect(list *l, list_pos pos);

// Insert a value immediately before a given position.
// Return the position of the new element.
list_pos list_insert(list *l, list_pos pos, void* v);

// Remove (and kill) the element at the given position.
// Return the position of the element immediately after the removed element.
list_pos list_remove(list *l, list_pos pos);

#endif
