#include <assert.h>
#include "btree.h"
#include <string.h>
#include <stdio.h>

void test_insert_row() {
    Table test_table = { .row_count = 0 }; // Initialize the table
    insert_row(&test_table, 1, "Rachid");
    assert(test_table.row_count == 1);
    assert(test_table.rows[0].id == 1);
    assert(strcmp(test_table.rows[0].name, "Rachid") == 0);
    printf("test_insert_row passed.\n");
}

void test_position_tracking() {
    Table test_table = { .row_count = 0 }; // Initialize the table
    int current_index = -1; // Track position externally

    // Insert rows and update current_index
    insert_row(&test_table, 1, "Alice");
    current_index = 0;
    assert(test_table.row_count == 1);
    assert(test_table.rows[current_index].id == 1);
    assert(strcmp(test_table.rows[current_index].name, "Alice") == 0);

    insert_row(&test_table, 2, "Bob");
    current_index = 1;
    assert(test_table.row_count == 2);
    assert(test_table.rows[current_index].id == 2);
    assert(strcmp(test_table.rows[current_index].name, "Bob") == 0);

    // Test bounds by simulating navigation
    if (current_index < test_table.row_count - 1) {
        current_index++;
    }
    assert(current_index == 1); // Should not go out of bounds

    printf("test_position_tracking passed.\n");
}

int main() {
    test_insert_row();
    test_position_tracking();
    printf("All tests passed.\n");
    return 0;
}
