#include <stdlib.h>
#include <stdio.h>

#include "input.h"
#include "pager.h"
#include "table.h"
#include "misc.h"
#include "vm.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Must supply a database filename.\n");
    exit(EXIT_FAILURE);
  }
  Table* table = db_open(argv[1]);
  InputBuffer *input_buffer = new_input_buffer();

  while (1) {
    print_prompt();
    read_input(input_buffer);
    
    // Check if we have a command
    if (input_buffer->buffer[0] == '.') {
      // Delegate command execution to `do_meta_command`
      switch (do_meta_command(input_buffer, table)) {
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
      case PREPARE_SYNTAX_ERROR:
        printf("Syntax error. Could not parse statement.\n");
        continue;
      case PREPARE_STRING_TOO_LONG:
        printf("String is too long.\n");
        continue;
      case PREPARE_NEGATIVE_ID:
        printf("ID must be positive.\n");
        continue;
    }

    switch (execute_statement(&statement, table)) {
      case EXECUTE_SUCCESS:
        printf("Executed.\n");
        break;
      case EXECUTE_TABLE_FULL:
        printf("Error: Table full.\n");
        break;
      case EXECUTE_DUPLICATE_KEY:
        printf("Error: Duplicate key.\n");
        break;
    }
  }
}
