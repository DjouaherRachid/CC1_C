#include <assert.h>
#include "btree.h"
#include <string.h>
#include <stdio.h>

void test_insert_row() {
    Table test_table = { .row_count = 0 };
    insert_row(&test_table, 1, "Rachid");
    assert(test_table.row_count == 1);
    assert(test_table.rows[0].id == 1);
    assert(strcmp(test_table.rows[0].name, "Rachid") == 0);
}

int main() {
    test_insert_row();
    printf("All tests passed.\n");
    return 0;
}
