#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  char* buffer;
  size_t buffer_length; // Size of the buffer
  ssize_t input_length; // Size of the input contained in the buffer
} InputBuffer;

InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = (InputBuffer*) malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

// Result of the execution of a meta command
typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

// Result of the conversion of a user input to
// our internal representation of a statement
typedef enum {
  PREPARE_SUCCESS,
  PREPARE_UNRECOGNIZED_STATEMENT,
} PrepareResult;

typedef enum {
  STATEMENT_INSERT,
  STATEMENT_SELECT
} StatementType;

typedef struct {
  StatementType type;
} Statement;

// This is the front-end of our database, where we convert 
// user input into our internal representation of a Statement
PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement) {
  if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
    statement->type = STATEMENT_INSERT;
    return PREPARE_SUCCESS;
  }

  if (strcmp(input_buffer->buffer, "select") == 0) {
    statement->type = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  }

  return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement *statement) {
  switch (statement->type) {
    case STATEMENT_INSERT: {
      printf("This is where we would do an insert.\n");
      break;
    }
    case STATEMENT_SELECT: {
      printf("This is where we would do a select.\n");
      break;
    }
  }
}

void read_input(InputBuffer* input_buffer) {
  ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  // Ignore trailing \n
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer) {
  free(input_buffer->buffer);
  free(input_buffer);
}

void print_prompt() { printf("db > "); }

MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    exit(EXIT_SUCCESS);
  } else {
    return META_COMMAND_UNRECOGNIZED_COMMAND;
  }
}

int main(int argc, char* argv[]) {
  InputBuffer *input_buffer = new_input_buffer();

  while (1) {
    print_prompt();
    read_input(input_buffer);
    
    // Check if we have a command
    if (input_buffer->buffer[0] == '.') {
      // Delegate command execution to `do_meta_command`
      switch (do_meta_command(input_buffer)) {
        case META_COMMAND_SUCCESS:
          continue;
        case META_COMMAND_UNRECOGNIZED_COMMAND:
          printf("Unrecognised command '%s'.\n", input_buffer->buffer);
          continue;
      }
    }
    // If we had a command, the rest of the code below will not
    // be executed.
    Statement statement;

    // This is the 'front-end' 
    switch (prepare_statement(input_buffer, &statement)) {
      case PREPARE_SUCCESS:
        break;
      case PREPARE_UNRECOGNIZED_STATEMENT:
        printf("Unrecognised keyword at start of '%s'.\n", input_buffer->buffer);
        continue;
    }

    execute_statement(&statement);
    printf("Executed.\n");
  }
}
