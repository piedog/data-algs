#ifndef __GDD_LIST_H__
#define __GDD_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include "gdd_node.h"

typedef void* (*GDDFncCreate)(const void *const, void*);
typedef void  (*GDDFncDestroy)(void*);
typedef void  (*GDDFncShow)(void*, void*);  /** pointers to:  payload, user data  **/
typedef int   (*GDDFncFilter)(void *payload, void *userdata);

typedef struct _GDDList {
    GDDNode_t        *head;
    GDDNode_t        *tail;
    GDDNode_t        *current;
    GDDFncCreate      fnCreate;
    GDDFncDestroy     fnDestroy;
    GDDFncShow        fnShow;
}  GDDList_t;

typedef struct _GDDListIterator {
    GDDNode_t  *next;
    int         firstTime;
} GDDListIterator_t;

/** supply a create and destroy function for the payload carried by each node
 ** These functions will be used by GDDList_addNode and GDDList_destroy
*/
GDDList_t * GDDList_create(GDDFncCreate fnCreate, GDDFncDestroy fnDestroy);

void GDDList_destroy(GDDList_t *L);
void GDDList_addNode(GDDList_t *L, const void * const data);
void GDDList_iterateAndShow(GDDList_t *L, void *userdata);
void GDDList_setShowFunction(GDDList_t *L, GDDFncShow fnc);
void GDDList_showList(GDDList_t *L);

void *GDDList_iterate(GDDList_t *L, GDDListIterator_t *II);   /**  initialize to this: II.next elem=NULL, II.firstTime=TRUE   **/
void *GDDList_iterateWithFilter(GDDList_t *L, GDDFncFilter fnc, void *userdata, GDDListIterator_t *II);
//void GDDList_insertBeforeCurrentNode(GDDList_t *L, const void * const data, size_t size);
//void GDDList_deleteCurrentNode(GDDList_t* list);
//void GDDList_setToHead(GDDList_t* list);

#endif     /**    __GDD_LIST_H__   **/
