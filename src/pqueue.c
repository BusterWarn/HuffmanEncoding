/**
 * Prio queue with double linked list as internal representation.
 * Takes a compare function when creating a new queue that is used 
 * to determine prio within the queue.
 *
 * @author: Sebastian Sandberg <cass@cs.umu.se>
 * @since:  2017-12-11
 */

#include <stdlib.h>
#include "list.h"
#include "pqueue.h"

struct pqueue {
    list* pq;
    cmp_func cmp;
};

/*
 * Create a new empty queue.
 *
 * \param [in] cmp   - the compare function used to determine 
 *                     prio within queue
 * \return a new prio queue
 */
pqueue* pqueue_empty(cmp_func cmp){

    pqueue* q = malloc(sizeof *q);
    if(!q)
        return NULL;
    q->pq = list_empty();
    q->cmp = cmp;

    return q;
}

/*
 * Set memhandler for queue.
 *
 * \param [in] q     - the queue
 * \param [in] mfunc - free function 
 */
void pqueue_set_memhandler(pqueue* q, mem_func mfunc){

    list_set_memhandler(q->pq, mfunc);
}

/*
 * Remove element from queue.
 *
 * \param [in] q     - the queue
 */
void pqueue_delete_first(pqueue* q){

    if(!list_is_empty(q->pq)){
        list_remove(q->pq, list_first(q->pq));
    }
}

/*
 * Insert element in queue based on prio defined in cmp_func (se h-file for details).
 *
 * \param [in] q     - the queue
 * \param [in] value - value to insert
 */
void pqueue_insert(pqueue* q, void* value){

    if(list_is_empty(q->pq)){
        list_insert(q->pq, list_first(q->pq), value);
    } else {

        list_pos pos = list_first(q->pq);
        while(!list_is_end(q->pq, pos)){
            if(q->cmp != NULL){
                if(q->cmp(value, list_inspect(q->pq, pos)) < 0){
                    list_insert(q->pq, pos, value);
                    return;
                }
            }
            pos = list_next(q->pq, pos);
        }
        list_insert(q->pq, pos, value);
    }
}

/*
 * Get value at front of queue.
 *
 * \param [in] q     - the queue
 * \return value at front of queue
 */
void* pqueue_inspect_first(pqueue* q){

    return list_inspect(q->pq, list_first(q->pq));
}

/*
 * Check if queue is empty.
 *
 * \param [in] q     - the queue
 * \return true if empty, else false
 */
bool pqueue_is_empty(pqueue* q){
	return list_is_empty(q->pq);
}

/*
 * Deallocate resources for queue.
 *
 * \param [in] q     - the queue
 */
void pqueue_kill(pqueue* q){

    list_kill(q->pq);
    free(q);
}

/* HELP FUNC - Not part of API */
void pqueue_print(pqueue* q, print_func pf){

    list_pos pos = list_first(q->pq);
    while(!list_is_end(q->pq, pos)){
        pf(list_inspect(q->pq, pos));
        pos = list_next(q->pq, pos);
    }
}