#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gdd_node.h"
#include "gdd_errorhandling.h"

/** ===========================================================================
 **/
/* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

GDDNode_t* GDDNode_create(const void* const data, size_t size, GDDNode_t *prev, GDDNode_t *next)
{
    GDDNode_t *C = malloc(sizeof(GDDNode_t));
    if (!C) GDD_handleError("could not allocate mem for GDDNode_t");
    C->data = malloc(size);
    if (!C->data) GDD_handleError("could not allocate mem for GDDNode_t data");
    memcpy(C->data, data, size);
    C->prev = prev;
    C->next = next;
    C->size = size;
    return C;
}

void GDDNode_delete(GDDNode_t *C)
{
    GDDNode_t *newNext = NULL;
    GDDNode_t *newPrev = NULL;
    if (!C) return;

    if (C->prev) {
        newPrev = C->prev;
        newPrev->next = newNext;
    }

    if (C->next) {
        newNext = C->next;
        newNext->prev = newPrev;
    }

    // free(C->data);
    free(C);
}
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */


GDDNode_t* GDDNode_create(void *data, size_t size, GDDNode_t *prev, GDDNode_t *next)
{
    GDDNode_t *C = malloc(sizeof(GDDNode_t));
    if (!C) GDD_handleError("could not allocate mem for GDDNode_t");
 // C->data = malloc(size);
 // if (!C->data) GDD_handleError("could not allocate mem for GDDNode_t data");
 // memcpy(C->data, data, size);

    /** Note: the payload should be allocated and freed by the caller  **/
    C->data = data;      /**   pointer to payload **/
    C->prev = prev;
    C->next = next;
    C->size = size;
    return C;
}

void GDDNode_delete(GDDNode_t *C)
{
    GDDNode_t *newNext = NULL;
    GDDNode_t *newPrev = NULL;
    if (!C) return;

    if (C->prev) {
        newPrev = C->prev;
        newPrev->next = newNext;
    }

    if (C->next) {
        newNext = C->next;
        newNext->prev = newPrev;
    }

    //free(C->data);
}


void GDDNode_setNext(GDDNode_t *C, GDDNode_t *next)
{
    C->next = next;
}

void GDDNode_setPrev(GDDNode_t *C, GDDNode_t *prev)
{
    C->prev = prev;
}

GDDNode_t *GDDNode_getNext(GDDNode_t *C)
{
    if (!C) return NULL;
    return C->next;
}

GDDNode_t *GDDNode_getPrev(GDDNode_t *C)
{
    if (!C) return NULL;
    return C->prev;
}


