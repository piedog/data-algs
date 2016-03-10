#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gdd_node.h"
#include "gdd_errorhandling.h"


void Insert(GDDNode_t *C, GDDNode_t *newC);
GDDNode_t *GetByIndex(GDDNode_t *C, size_t index);
void IterateAndShow(GDDNode_t *first);
void ReverseIterateAndShow(GDDNode_t *last);
size_t CountNodes(GDDNode_t *C);



GDDNode_t *GetByIndex(GDDNode_t *C, size_t index)
{
    size_t idx = 0;
    if (!C) return NULL;
    while (C) {
        if (idx == index) return C;
        idx++;
        C = C->next;
    }
    return NULL;
}


void Insert(GDDNode_t *C, GDDNode_t *Cx)
{
    /**  Inserts node Cx in front of node C
                Inserts Cx between C1 and C
                             insert Cx here
                                   |
                                   v
           old list:        C0  C1    C   C3
                           C1.next = C, C1.prev = C0
                           C.next  = C3, C.prev = C1
           ---------------------------------------------------------------------------------
           new list:       C0  C1  Cx  C  C3
                           C1.next = Cx, C1.prev = C0     changed: C1.next = Cx
                           C.next = C3,  C.prev = Cx      changed: C.prev = Cx
                           Cx.next = C,  Cx.prev = C1     changed Cx.next = C, Cx.prev = C1

           fprintf(stdout,"insert [%s] before [%s]\n", Cx->data, C->data);
     **/
    
    if (!C || !Cx) return;
    C->prev->next = Cx;
    Cx->prev = C->prev;
    Cx->next = C;
    C->prev = Cx;
}



void IterateAndShow(GDDNode_t *C)
{
    int n=0;
    while (C) {
        n++;
        fprintf(stdout, "%3d:(%3d) %s\n", n, strlen((char*)C->data), (char*)C->data);
        C = C->next;
    }
}



void ReverseIterateAndShow(GDDNode_t *C)
{
    int n=0;
    while (C) {
        n++;
        fprintf(stdout, "%3d:(%3d) %s\n", n, strlen((char*)C->data), (char*)C->data);
        C = C->prev;
    }
}

size_t CountNodes(GDDNode_t *C)
{
    int n=0;
    while (C) {
        n++;
        C = C->next;
    }
    return n;
}


void DeleteAllNodes(GDDNode_t *C)
{
    GDDNode_t *tmpC = C;
    while (C) {
        tmpC = C;
        C = C->next;
        GDDNode_delete(tmpC);
    }
}


/**=============================================================================
 **/

    int main(int argc, char **argv)
{

    static char *textStrings[] = {
            "little white rocket"
           ,"can run very fast"
           ,"can dodge bullets"
           ,"Vatican spokesman said that the pope's words were merely meant to express"
           ,"his own views that migrants should not be kept behind walls."
           ,"and chases squirrels"
           ,NULL
         };
    char **text = textStrings;
    char dataToInsert[] = "data to be inserted";
    char moreDataToInsert[] = "insert this at beginning of list";
    GDDNode_t *curOne=NULL, *lstOne=NULL, *first=NULL;
    GDDNode_t *node = NULL;
    GDDNode_t *newOne = NULL;
    size_t numNodes;
    int i;


    /***  Load the list
     ***/
    while (*text) {
        fprintf(stdout, "adding [%s]\n", *text);
        curOne = GDDNode_create(*text, lstOne, NULL);
        if (!first) first = curOne;
        if (lstOne) GDDNode_setNext(lstOne, curOne);
        lstOne = curOne;
        *text++;
    }

    IterateAndShow(first);
    ReverseIterateAndShow(lstOne);

    fprintf(stdout,"number of nodes=%d\n", CountNodes(first));


    /*** create a new node and insert
         Note: first needs to be updated if we insert at beginning of list
     ***/
    newOne = GDDNode_create(dataToInsert, NULL, NULL);
    node = GetByIndex(first, 3);
    fprintf(stdout,"get by index:[%s]\n", node->data);
    fprintf(stdout,"new one     :[%s]\n", newOne->data);
    Insert(node,newOne);
    IterateAndShow(first);
    ReverseIterateAndShow(lstOne);

    /*** Insert at beginning of list
     ***/
    newOne = GDDNode_create(moreDataToInsert, NULL, first);
    GDDNode_setPrev(first, newOne);
    first = newOne;
    IterateAndShow(first);
    ReverseIterateAndShow(lstOne);

    /*** Test GetByIndex.
         The last two nodes should be null, since they do not exist
     ***/
    numNodes = CountNodes(first);
    for (i=0; i<numNodes+2; i++) {
        if (node = GetByIndex(first, i)) {
            fprintf(stdout,"[%3d][%s]\n", i, node->data);
        }
        else {
            fprintf(stdout,"[%3d][%s]\n", i, "null");
        }
    }
        

    DeleteAllNodes(first);
    return 0;
}

