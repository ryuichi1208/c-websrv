#include "route.h"

char *routing(char *uri)
{
    char *ret;

    if (strlen(uri) == 1) {
        ret = "index.html";
        return ret;
    }

    ret = uri + 1;
    return ret;
}
