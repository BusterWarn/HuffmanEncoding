#include <stdlib.h>
#include <assert.h>

#include "list.h"


struct node
{
    struct node *next;
    struct node *prev;
    void* value;
};


static struct node *make_node(void* value)
{
    struct node *n = malloc(sizeof *n);
    n->next = NULL;
    n->prev = NULL;
    n->value = value;
    return n;
}


struct list
{
    struct node *first;
    struct node *end;
    mem_func mfunc;
};


void list_set_memhandler(list* l, mem_func mfunc){
    l->mfunc = mfunc;
}

void list_kill(list *l)
{
    while (l->first != NULL) {
        struct node *n = l->first;
        l->first = n->next;
        if(l->mfunc != NULL)
            l->mfunc(n->value);
        free(n);
    }
    free(l);
}


list *list_empty(void)
{
    list *l = malloc(sizeof *l);
    l->first = NULL;
    l->end = NULL;
    l->mfunc = NULL;
    return l;
}


bool list_is_empty(list *l)
{
    return l->first == NULL;
}


list_pos list_first(list *l)
{
    if (l->first == NULL) {
        return (list_pos) { &l->first, &l->end };
    } else {
        return (list_pos) { &l->first, &l->first->prev };
    }
}


list_pos list_end(list *l)
{
    if (l->first == NULL) {
        return (list_pos) { &l->first, &l->end };
    } else {
        return (list_pos) { &l->end->next, &l->end };
    }
}


list_pos list_next(list *l, list_pos pos)
{
    if ((*pos.forward)->next == NULL) {
        return (list_pos) { &(*pos.forward)->next, &l->end };
    } else {
        return (list_pos) { &(*pos.forward)->next, &(*pos.forward)->next->prev };
    }
}


list_pos list_previous(list *l, list_pos pos)
{
    if ((*pos.backward)->prev == NULL) {
        return (list_pos) { &l->first, &(*pos.backward)->prev };
    } else {
        return (list_pos) { &(*pos.backward)->prev->next, &(*pos.backward)->prev };
    }
}


bool list_is_end(list *l, list_pos pos)
{
    assert(l != NULL);
    return *pos.forward == NULL;
}


bool list_is_first(list *l, list_pos pos)
{
    assert(l != NULL);
    return *pos.backward == NULL;
}


void* list_inspect(list *l, list_pos pos)
{
    assert(l != NULL);
    return (*pos.forward)->value;
}


list_pos list_insert(list *l, list_pos pos, void* v)
{
    assert(l != NULL);

    struct node *n = make_node(v);
    n->next = *pos.forward;
    n->prev = *pos.backward;
    *pos.forward = n;
    *pos.backward = n;
    return (list_pos) { pos.forward, &n->prev };
}


list_pos list_remove(list *l, list_pos pos)
{
    struct node *n = *pos.forward;
    *pos.forward = n->next;
    if (*pos.forward) {
        pos.backward = &(*pos.forward)->prev;
    } else {
        pos.backward = &l->end;
    }
    *pos.backward = n->prev;
    if(l->mfunc != NULL)
        l->mfunc(n->value);
    free(n);
    return pos;
}
