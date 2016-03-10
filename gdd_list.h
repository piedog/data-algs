#ifndef __GDD_LIST_H__
#define __GDD_LIST_H__

typedef void* (*GDDFncCreate)(const void *const, void*);
typedef void (*GDDFncDestroy)(void*);
typedef void (*GDDFncShow)(void*, void*);  /** pointers to:  payload, user data  **/

typedef struct _GDDList {
    GDDNode_t        *head;
    GDDNode_t        *tail;
    GDDNode_t        *current;
    GDDFncCreate      fnCreate;
    GDDFncDestroy     fnDestroy;
    GDDFncShow        fnShow;
}  GDDList_t;


/** supply a create and destroy function for the payload carried by each node
 ** These functions will be used by GDDList_addNode and GDDList_destroy
*/
GDDList_t * GDDList_create(GDDFncCreate fnCreate, GDDFncDestroy fnDestroy);

void GDDList_destroy(GDDList_t *L);
void GDDList_addNode(GDDList_t *L, const void * const data);
void GDDList_iterateAndShow(GDDList_t *L, void *userdata);
void GDDList_setShowFunction(GDDList_t *L, GDDFncShow fnc);
void GDDList_showList(GDDList_t *L);

//void GDDList_insertBeforeCurrentNode(GDDList_t *L, const void * const data, size_t size);
//void GDDList_deleteCurrentNode(GDDList_t* list);
//void GDDList_setToHead(GDDList_t* list);

#endif     /**    __GDD_LIST_H__   **/
