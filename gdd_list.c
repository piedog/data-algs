#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gdd_node.h"
#include "gdd_errorhandling.h"
#include "testdata.h"
#include "gdd_list.h"


/** ===========================================================================
 **/

/**        example of user function to pass to GDD_iterateAndShow

                 void displayNode(GDDNode_t *N, void *user) {
                     int n = *(int*)user;
                     fprintf(stdout, "%3d:(%3d) %s\n", n, N->size, (char*)N->data);
                 }
 **/

/** ===========================================================================
 **/

void GDDList_iterateAndShow(GDDList_t *L, void(*fnc)(GDDNode_t*, void*))
{
    int n = 0;
    GDDNode_t *node = L->head;
    while (node) {
        n++;
        fnc(node, &n);     /**  past the node and a pointer to something. Can be any user data **/
        node = node->next;
    }
}


GDDList_t*  GDDList_create()
{
    GDDList_t *L = NULL;
    L = malloc(sizeof(GDDList_t));
    if (!L) GDD_handleError("could not alloc Linklist_t");
    L->head = NULL;
    L->tail = NULL;
    L->current = NULL;
    return L;
}

void GDDList_destroy(GDDList_t *L)
{
    if (!L) return;
    if (L->head) {
        GDDNode_t *node = L->head;
        GDDNode_t *tmp = NULL;

        while (node) {

            tmp = node;
            GDDNode_delete(node);
            node = tmp->next;
        }
    }
    L = NULL;
}

/*** xxxxxxxxxxxxxxxxxxx 
     TODO: rethink this

void GDDList_setToHead(GDDList_t *L)
{
    if (!L) return;
    L->current = L->head;
}

void GDDList_setToTail(GDDList_t *L)
{
    if (!L) return;
    L->current = L->tail;
}
*** xxxxxxxxxxxxxxxxxxxxxxx **/

void GDDList_addNode(GDDList_t *L, const void * const data, size_t size)
{
    GDDNode_t *lastNode = NULL;
    GDDNode_t *newNode  = NULL;
    if (!L) return;

 // lastNode = L->current;    /** note: L->current may be null, so lastNode needs to be tested below **/
 // L->current = GDDNode_create(data, size, L->current, NULL);
 // if (lastNode) GDDNode_setNext(lastNode, L->current);
 // L->tail = L->current;

    lastNode = L->tail;

    newNode = GDDNode_create(data, size, NULL, NULL);

    if (lastNode) lastNode->next = newNode;
    newNode->prev = lastNode;
    L->tail = newNode;
    if (!L->head) L->head = newNode;
}


/**   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx   **/
#if 0 
void GDDList_insertBeforeCurrentNode(GDDList_t *L, const void * const data, size_t size)
{
    GDDNode_t *newNode = NULL;
    if (!L) return;
    newNode = GDDNode_create(data, size, NULL, NULL);

    /** after creating the new node, assign current->prev->next to new node

    if (L->current) GDDNode_setPrev(L->current,newNode);   /** if list is empty, then there is no current node **/
    if (L->current) GDDNode_setNext(newNode, L->current);
    if (L->current && L->current->prev) GDDNode_setNext(L->current->prev, newNode);


    /**  assign next and prev for the new node
     **/
    if (L->current) newNode->prev = L->current->prev;
    if (L->current) newNode->next = L->current->next;

    /** assign next for the old prev node
     **/
    if (L->current && L->current->prev) L->current->prev->next = newNode;

    /** assign prev for the old next node
     **/
    if (L->current && L->current->next) L->current->next->prev = newNode;

    // L->current = newNode;


    /** assign head and tail if necessary
     **/
    if (!newNode->prev) L->head = newNode;
    if (!newNode->next) L->tail = newNode;
}
#endif
/**   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx   **/
