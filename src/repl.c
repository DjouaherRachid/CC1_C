#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "btree.h"  

typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT, STATEMENT_DELETE } StatementType;

typedef struct {
  StatementType type;
  int id;           
  char name[32];    
} Statement;

typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

void print_prompt() { 
  printf("db > "); 
}

void read_input(InputBuffer* input_buffer) {
  ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
    }

    if (strncmp(input_buffer->buffer, ".save", 5) == 0) {
        char filename[256];
        sscanf(input_buffer->buffer, ".save %s", filename);
        save_table(filename);
        return META_COMMAND_SUCCESS;
    }

    if (strncmp(input_buffer->buffer, ".load", 5) == 0) {
        char filename[256];
        sscanf(input_buffer->buffer, ".load %s", filename);
        load_table(filename);
        return META_COMMAND_SUCCESS;
    }

    return META_COMMAND_UNRECOGNIZED_COMMAND;
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        int args_assigned = sscanf(input_buffer->buffer, "insert %d %s", &statement->id, statement->name);
        if (args_assigned < 2) {
            return PREPARE_UNRECOGNIZED_STATEMENT;
        }
        return PREPARE_SUCCESS;
    }

  if (strncmp(input_buffer->buffer, "delete", 6) == 0) {
    statement->type = STATEMENT_DELETE;
    int args_assigned = sscanf(input_buffer->buffer, "delete %d", &statement->id);
    if (args_assigned < 1) {
      return PREPARE_UNRECOGNIZED_STATEMENT;
    }
    return PREPARE_SUCCESS;
  }

    if (strncmp(input_buffer->buffer, "select", 6) == 0) {
        if (strcmp(input_buffer->buffer, "select *") == 0) {
            statement->type = STATEMENT_SELECT;
            statement->id = -1; // Indicate that we want all rows
            return PREPARE_SUCCESS;
        } else {
            statement->type = STATEMENT_SELECT;
            int args_assigned = sscanf(input_buffer->buffer, "select %d", &statement->id);
            if (args_assigned < 1) {
                return PREPARE_UNRECOGNIZED_STATEMENT;
            }
            return PREPARE_SUCCESS;
        }
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement) {
    switch (statement->type) {
        case STATEMENT_INSERT:
            printf("Insert statement executed. (ID: %d, Name: %s)\n", statement->id, statement->name);
            insert_row(&table, statement->id, statement->name);
            break;
        case STATEMENT_SELECT:
            if (statement->id == -1) {
                // Select all rows
                select_rows(&table);
            } else {
                // Select row by ID
                select_row_by_id(&table, statement->id);
            }
            break;
	case STATEMENT_DELETE:
      		printf("Delete statement executed. (ID: %d)\n", statement->id);
      		delete_row(&table, statement->id); 
      		break;

    }
}

void repl(void){
  InputBuffer* input_buffer = new_input_buffer();

  while (true) {
    print_prompt();
    read_input(input_buffer);
    
    if (input_buffer->buffer[0] == '.') {
      switch (do_meta_command(input_buffer)) {
        case META_COMMAND_SUCCESS:
          continue;
        case META_COMMAND_UNRECOGNIZED_COMMAND:
          printf("Unrecognized command '%s'\n", input_buffer->buffer);
          continue;
      }
    }

    Statement statement;
    switch (prepare_statement(input_buffer, &statement)) {
      case PREPARE_SUCCESS:
        printf("recognized statement\n");
        break;
      case PREPARE_UNRECOGNIZED_STATEMENT:
        printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
        continue;
    }

    execute_statement(&statement);
    printf("Executed.\n");
  }
}

