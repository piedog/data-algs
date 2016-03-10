#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gdd_node.h"
#include "gdd_errorhandling.h"
#include "testdata.h"
#include "gdd_list.h"



/** ===========================================================================
 **/

/**    Create, destroy, and show functions to pass to List object for operations
       on node objects
 **/

void* constructNode(const void *const data, void *userdata)
{
    /** userdata not used  **/
    char *payload = strdup(data);
    return payload;
}


void destructNode(void *data)
{
    free(data);
}


void displayNode(void *data, void *userdata)
{
    int n = 0;
    if (userdata) n = ++(*(int*)userdata);
    if (!data) return;
    fprintf(stdout, "(%3d)(%3d) [%s]\n", n, strlen((char*)data), (char*)data);
}


int main(int argc, char** argv)
{
    int counter = 0;   /** counter for displayNode function, passed in as userdata   **/
    const char * const *text = textStrings;
    GDDList_t *L = GDDList_create((GDDFncCreate)constructNode, (GDDFncDestroy)destructNode);
    GDDList_setShowFunction(L, (GDDFncShow)displayNode);
    while (*text) {
        fprintf(stdout, "adding to list: [%s]\n",*text);
        GDDList_addNode(L, *text);
        *text++;
    }

    GDDList_iterateAndShow(L, &counter);

    GDDList_destroy(L);
    return 0;
}
