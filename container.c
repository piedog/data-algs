#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


typedef struct _Container {
    size_t          size;
    void           *data;
    struct _Container *next;
    struct _Container *prev;
} Container_t;

Container_t* Container_create(void* data, size_t size, Container_t *prev, Container_t *next);
void Container_delete(Container_t *C);
void Container_setNext(Container_t *C, Container_t *next);
void Container_setPrev(Container_t *C, Container_t *prev);

void Insert(Container_t *C, Container_t *newC);
Container_t *GetByIndex(Container_t *C, size_t index);
void IterateAndShow(Container_t *first);
void ReverseIterateAndShow(Container_t *last);
size_t CountNodes(Container_t *C);

void Linklist_error(const char *const msg);

/** ===========================================================================
 **/

void Linklist_error(const char *const msg)
{
    fprintf(stderr, "Linklist error: %s\n", msg);
    exit(-1);
}
/** ===========================================================================
 **/

Container_t* Container_create(void* data, size_t size, Container_t *prev, Container_t *next)
{
    Container_t *C = malloc(sizeof(Container_t));
    if (!C) Linklist_error("could not allocate mem for Container_t");
    C->data = malloc(size);
    if (!C->data) Linklist_error("could not allocate mem for Container_t data");
    memcpy(C->data, data, size);
    C->prev = prev;
    C->next = next;
    C->size = size;
    return C;
}

void Container_delete(Container_t *C)
{
    Container_t *newNext = NULL;
    Container_t *newPrev = NULL;
    if (!C) return;

    if (C->prev) {
        newPrev = C->prev;
        newPrev->next = newNext;
    }

    if (C->next) {
        newNext = C->next;
        newNext->prev = newPrev;
    }

    free(C->data);
}


void Container_setNext(Container_t *C, Container_t *next)
{
    C->next = next;
}

void Container_setPrev(Container_t *C, Container_t *prev)
{
    C->prev = prev;
}


Container_t *GetByIndex(Container_t *C, size_t index)
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


void Insert(Container_t *C, Container_t *Cx)
{
    /**  Inserts containter Cx in front of container C
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



void IterateAndShow(Container_t *C)
{
    int n=0;
    while (C) {
        n++;
        fprintf(stdout, "%3d:(%3d) %s\n", n, C->size, (char*)C->data);
        C = C->next;
    }
}



void ReverseIterateAndShow(Container_t *C)
{
    int n=0;
    while (C) {
        n++;
        fprintf(stdout, "%3d:(%3d) %s\n", n, C->size, (char*)C->data);
        C = C->prev;
    }
}

size_t CountNodes(Container_t *C)
{
    int n=0;
    while (C) {
        n++;
        C = C->next;
    }
    return n;
}


void DeleteAllNodes(Container_t *C)
{
    Container_t *tmpC = C;
    while (C) {
        tmpC = C;
        C = C->next;
        Container_delete(tmpC);
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
    Container_t *curOne=NULL, *lstOne=NULL, *first=NULL;
    Container_t *container = NULL;
    Container_t *newOne = NULL;
    size_t numNodes;
    int i;


    /***  Load the list
     ***/
    while (*text) {
        fprintf(stdout, "adding [%s]\n", *text);
        curOne = Container_create(*text, strlen(*text)+1, lstOne, NULL);
        if (!first) first = curOne;
        if (lstOne) Container_setNext(lstOne, curOne);
        lstOne = curOne;
        *text++;
    }

    IterateAndShow(first);
    ReverseIterateAndShow(lstOne);

    fprintf(stdout,"number of nodes=%d\n", CountNodes(first));


    /*** create a new node and insert
         Note: first needs to be updated if we insert at beginning of list
     ***/
    newOne = Container_create(dataToInsert, strlen(dataToInsert)+1, NULL, NULL);
    container = GetByIndex(first, 3);
    fprintf(stdout,"get by index:[%s]\n", container->data);
    fprintf(stdout,"new one     :[%s]\n", newOne->data);
    Insert(container,newOne);
    IterateAndShow(first);
    ReverseIterateAndShow(lstOne);

    /*** Insert at beginning of list
     ***/
    newOne = Container_create(moreDataToInsert, strlen(moreDataToInsert)+1, NULL, first);
    Container_setPrev(first, newOne);
    first = newOne;
    IterateAndShow(first);
    ReverseIterateAndShow(lstOne);

    /*** Test GetByIndex.
     ***/
    numNodes = CountNodes(first);
    for (i=0; i<numNodes+2; i++) {
        if (container = GetByIndex(first, i)) {
            fprintf(stdout,"[%3d][%s]\n", i, container->data);
        }
        else {
            fprintf(stdout,"[%3d][%s]\n", i, "null");
        }
    }
        

    DeleteAllNodes(first);
    return 0;
}

