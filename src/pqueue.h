/**
 * Prio queue with double linked list as internal representation.
 * Takes a compare function when creating a new queue that is used
 * to determine prio within the queue.
 *
 * @author: Sebastian Sandberg <cass@cs.umu.se>
 * @since:  2017-12-11
 */

#ifndef PQUEUE_H
#define PQUEUE_H

#include <stdbool.h>
#include <stddef.h>

#ifndef __MEMFUNC
#define __MEMFUNC
typedef void (*mem_func)(void*);
#endif

/* Pointer to a function that is called for comparing two priorities. If
 * val1 is the first value and val2 the second, the following must be
 * returned:
 *   > 0   if val1 > val2
 *   < 0   if val1 < val2
 *   0     if val1 = val2
 */
typedef int (*cmp_func)(void*, void*);
typedef void (*print_func)(void*);

typedef struct pqueue pqueue;

/*
 * Create a new empty queue.
 *
 * \param [in] cmp   - the compare function used to determine
 *                     prio within queue
 * \return a new prio queue
 */
pqueue* pqueue_empty(cmp_func cmp);

/*
 * Set memhandler for queue.
 *
 * \param [in] q     - the queue
 * \param [in] mfunc - free function
 */
void pqueue_set_memhandler(pqueue* q, mem_func mfunc);

/*
 * Remove element from queue.
 *
 * \param [in] q     - the queue
 */
void pqueue_delete_first(pqueue* q);

/*
 * Insert element in queue based on prio defined in cmp_func.
 *
 * \param [in] q     - the queue
 * \param [in] value - value to insert
 */
void pqueue_insert(pqueue* q, void* value);

/*
 * Get value at front of queue.
 *
 * \param [in] q     - the queue
 * \return value at front of queue
 */
void* pqueue_inspect_first(pqueue* q);

/*
 * Check if queue is empty.
 *
 * \param [in] q     - the queue
 * \return true if empty, else false
 */
bool pqueue_is_empty(pqueue* q);

/*
 * Deallocate resources for queue.
 *
 * \param [in] q     - the queue
 */
void pqueue_kill(pqueue* q);

/* HELP FUNC - Not part of API */
void pqueue_print(pqueue* q, print_func pf);

#endif
