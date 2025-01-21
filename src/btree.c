#include "btree.h"
#include <stdio.h>
#include <string.h>

Table table = { .row_count = 0 };

void insert_row(Table* table, int id, const char* name) {
    if (row_exists(table, id)) {
        printf("Error: Row with ID %d already exists.\n", id);
        return;  
    }

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

// Function to check if a row with the given ID already exists in the table
int row_exists(Table* table, int id) {
    for (int i = 0; i < table->row_count; i++) {
        if (table->rows[i].id == id) {
            return 1;  // ID already exists
        }
    }
    return 0;  // ID does not exist
}

void delete_row(Table* table, int id) {
    int row_index = -1;
    for (int i = 0; i < table->row_count; i++) {
        if (table->rows[i].id == id) {
            row_index = i;
            break;
        }
    }

    if (row_index == -1) {
        printf("Error: Row with ID %d does not exist.\n", id);
        return;
    }

    for (int i = row_index; i < table->row_count - 1; i++) {
        table->rows[i] = table->rows[i + 1];
    }

    table->row_count--;

    printf("Row with ID %d deleted.\n", id);
}

void save_table(const char* filename) {
    FILE* file = fopen(filename, "wb");  
    if (file == NULL) {
        printf("Error opening file for writing: %s\n", filename);
        return;
    }

    fwrite(&table, sizeof(Table), 1, file);

    fclose(file);
    printf("Table saved to %s\n", filename);
}

#include <stdio.h>

void load_table(const char* filename) {
    FILE* file = fopen(filename, "rb");  
    if (file == NULL) {
        printf("Error opening file for reading: %s\n", filename);
        return;
    }

    fread(&table, sizeof(Table), 1, file);

    fclose(file);
    printf("Table loaded from %s\n", filename);
}
