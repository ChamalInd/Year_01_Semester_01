// Program entry point
#include "functions.h"
#include "types.h"
#include <time.h>


int main(void) {
    Cell board[NO_OF_CELLS];
    srand(SEED);

    initialize_game(board);
    return 0;
}