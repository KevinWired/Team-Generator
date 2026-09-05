#include <stdlib.h>

#include "shuffle.h"
#include "sort.h"

void shuffle(player a[], uint size)
{
    if (size < 2) {
        return;
    }

    for (uint i = size - 1; i > 0; i--) {
        uint j = (uint)rand() % (i + 1);
        swap(a, i, j);
    }
}