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

void GDDList_iterateAndShow(GDDList_t *L, void *userdata)
{
    int n = 0;
    GDDNode_t *node = L->head;
    if (!node || !L->fnShow) return;
    while (node) {
        n++;
        L->fnShow(node->data, userdata);     /**  past the node and a pointer to something. Can be any user data **/
        node = node->next;
    }
}


GDDList_t * GDDList_create(GDDFncCreate fnCreate, GDDFncDestroy fnDestroy)
{
    GDDList_t *L = NULL;
    L = malloc(sizeof(GDDList_t));
    if (!L) GDD_handleError("could not alloc Linklist_t");
    L->head = NULL;
    L->tail = NULL;
    L->current = NULL;
    L->fnCreate = fnCreate;
    L->fnDestroy = fnDestroy;
    L->fnShow = NULL;
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
            if (L->fnDestroy) L->fnDestroy(node->data); /** this deletes memory for the data in the node **/
            GDDNode_delete(node);     /** this deletes memory for the node info, but not the data  **/
            node = tmp->next;
        }
    }
    L = NULL;
}


void GDDList_setShowFunction(GDDList_t *L, GDDFncShow fnc)
{
    L->fnShow = fnc;
}


void GDDList_addNode(GDDList_t *L, const void * const data)
{
    GDDNode_t *lastNode = NULL;
    GDDNode_t *newNode  = NULL;
    void *newData = NULL;
    if (!L) return;

    lastNode = L->tail;

    newData = L->fnCreate(data, NULL);   /** create new memory for the payload data, user data is null   **/
    newNode = GDDNode_create(newData, NULL, NULL);

    if (lastNode) lastNode->next = newNode;
    newNode->prev = lastNode;
    L->tail = newNode;
    if (!L->head) L->head = newNode;
}
