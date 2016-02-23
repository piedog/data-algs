#include <stdio.h>
#include <stdlib.h>
#include "gdd_errorhandling.h"

/** ===========================================================================
 **/

void GDD_handleError(const char *const msg)
{
    fprintf(stderr, "Linklist error: %s\n", msg);
    exit(-1);
}
/** ===========================================================================
 **/

