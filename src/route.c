#include "route.h"

char *routing(char *uri)
{
    char *ret;

    if (!strcmp(uri, "/")) {
        ret = "index.html";
        return ret;
    }

    ret = uri + 1;
    return ret;
}
