#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gdd_node.h"
#include "gdd_errorhandling.h"
#include "testdata.h"
#include "gdd_list.h"



/** ===========================================================================
 **/

/** a user function to pass to the iterate function
 **/
void displayNode(GDDNode_t *N, void *user) {
    int n = *(int*)user;
    fprintf(stdout, "%3d:(%3d) %s\n", n, N->size, (char*)N->data);
}


int main(int argc, char** argv)
{
    const char * const *text = textStrings;
    GDDList_t *L = GDDList_create();
    while (*text) {
        fprintf(stdout, "adding to list: [%s]\n",*text);
        GDDList_addNode(L, *text, strlen(*text)+1);
        *text++;
    }

    GDDList_iterateAndShow(L, displayNode);

    GDDList_destroy(L);
    return 0;
}
