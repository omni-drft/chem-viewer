#include <stdbool.h>

#include "peBase.h"


int main()
{
    peState state;
    peInit(&state, "Testowe Okno", 400, 400);

    while (!state.quit)
    {
        peDetectClose(&state);
        peUpdateRenderer(&state);
    }
    peCleanup(&state);
}
