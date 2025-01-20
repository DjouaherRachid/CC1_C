#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[32];
} Row;

typedef struct {
    Row rows[1000]; 
    int row_count;
} Table;

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

