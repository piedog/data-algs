#ifndef __GDDNODE_H__
#define __GDDNODE_H__


typedef struct _GDDNode {
    void           *data;
    struct _GDDNode *next;
    struct _GDDNode *prev;
} GDDNode_t;

GDDNode_t* GDDNode_create(void *data, GDDNode_t *prev, GDDNode_t *next);
void GDDNode_delete(GDDNode_t *C);
void GDDNode_setNext(GDDNode_t *C, GDDNode_t *next);
void GDDNode_setPrev(GDDNode_t *C, GDDNode_t *prev);
GDDNode_t *GDDNode_getNext(GDDNode_t *C);
GDDNode_t *GDDNode_getPrev(GDDNode_t *C);

#endif    /****   __GDDNODE_H__    ***/
