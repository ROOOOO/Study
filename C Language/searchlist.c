#include <stdio.h>
#include <stdlib.h>
#include "elem.h"
struct Elem *searchlist(struct Elem *list, int k)
{
    struct Elem *p = NULL;
    if ((list -> tag == 0) && (list -> value.i == k))
    p = list;
    else if ((list -> tag == 2) && (list -> value.list != NULL)){
        p = searchlist((list -> value.list), k);
        if (p == NULL)if (p == NULL){
            if ((list -> tag == 0) && (list -> value.i == k))
            p = list;
            else if (list -> tail != NULL)
            p = searchlist((list -> tail), k);
        }
    }
    else if (list -> tail != NULL)
    p = searchlist((list -> tail), k);
    return p;
}