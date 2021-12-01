#ifndef __VM_H__
#define __VM_H__

#include "misc.h"
#include "table.h"

typedef enum { 
  EXECUTE_SUCCESS, 
  EXECUTE_TABLE_FULL,
  EXECUTE_DUPLICATE_KEY
} ExecuteResult;

ExecuteResult execute_insert(Statement *statement, Table *table);
ExecuteResult execute_select(Statement *statement, Table *table);
ExecuteResult execute_statement(Statement *statement, Table *table);

#endif
