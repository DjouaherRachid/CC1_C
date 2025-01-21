#include "btree.h"
#include <stdio.h>
#include <string.h>

Table table = { .row_count = 0 };

void insert_row(Table* table, int id, const char* name) {
    if (table->row_count >= 1000) {
        printf("Table is full.\n");
        return;
    }
    Row* row = &table->rows[table->row_count++];
    row->id = id;
    strncpy(row->name, name, sizeof(row->name));
}

void select_rows(Table* table) {
    if (table->row_count == 0) {
        printf("No rows found.\n");
        return;
    }

    for (int i = 0; i < table->row_count; i++) {
        Row* row = &table->rows[i];
        printf("Row ID: %d, Name: %s\n", row->id, row->name);
    }
}

void select_row_by_id(Table* table, int id) {
    for (int i = 0; i < table->row_count; i++) {
        if (table->rows[i].id == id) {
            printf("Row ID: %d, Name: %s\n", table->rows[i].id, table->rows[i].name);
            return;
        }
    }
    printf("Row with ID %d not found.\n", id);
}
