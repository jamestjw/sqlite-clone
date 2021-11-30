#ifndef __MISC_H__
#define __MISC_H__

#include "input.h"
#include "row.h"
#include "table.h"

typedef enum {
  STATEMENT_INSERT,
  STATEMENT_SELECT
} StatementType;

typedef struct {
  StatementType type;
  Row row_to_insert;
} Statement;


void print_prompt();
MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table);
PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement);
PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement);
void print_constants();
void print_leaf_node(void* node);

#endif
