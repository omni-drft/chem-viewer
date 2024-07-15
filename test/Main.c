#include <stdbool.h>

#include "peBase.h"
#include "peRectangle.h"


int main()
{
    peState state;
    peInit(&state, "Testowe Okno", 400, 400);

    peRectangle testRec;
    pePoint x1 = {10, 10};
    testRec.x1 = x1;
    testRec.color = 0xFFFFFFFF;

    while (!state.quit)
    {
        peDetectClose(&state);
        peUpdateRenderer(&state);
        pePrintRec(&testRec, &state);
    }
    peCleanup(&state);
}
