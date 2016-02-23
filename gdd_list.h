#ifndef __GDD_LIST_H__
#define __GDD_LIST_H__


typedef struct _GDDList {
    GDDNode_t        *head;
    GDDNode_t        *tail;
    GDDNode_t        *current;
}  GDDList_t;


GDDList_t * GDDList_create();
void GDDList_destroy(GDDList_t *L);
void GDDList_addNode(GDDList_t *L, const void * const data, size_t size);
void GDDList_iterateAndShow(GDDList_t *L, void(*fnc)(GDDNode_t*, void*));

//void GDDList_insertBeforeCurrentNode(GDDList_t *L, const void * const data, size_t size);
//void GDDList_deleteCurrentNode(GDDList_t* list);
//void GDDList_setToHead(GDDList_t* list);

#endif     /**    __GDD_LIST_H__   **/
