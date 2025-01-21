#include "btree.h"

void repl(void);

DBState db_state = { .current_row = -1 };

int main(int argc, char* argv[], char* envp[]) {
    (void)argc;
    (void)argv;
    (void)envp;

    repl();
    return 0;
}

