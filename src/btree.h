#ifndef BTREE_H
#define BTREE_H

typedef struct {
    int id;
    char name[32];
} Row;

typedef struct {
    Row rows[1000];
    int row_count;
} Table;

extern Table table;

typedef struct {
    int current_row;
} DBState;

extern DBState db_state;

void insert_row(Table* table, int id, const char* name);

#endif
