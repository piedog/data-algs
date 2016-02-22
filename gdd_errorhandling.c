#include <stdio.h>
#include <stdlib.h>
#include "gdd_errorhandling.h"

/** ===========================================================================
 **/

void Linklist_error(const char *const msg)
{
    fprintf(stderr, "Linklist error: %s\n", msg);
    exit(-1);
}
/** ===========================================================================
 **/

