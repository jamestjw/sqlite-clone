#ifndef __CURSOR_H__
#define __CURSOR_H__

#include "defs.h"
#include "table.h"

typedef struct {
  Table* table;
  uint32_t row_num;
  bool end_of_table;
} Cursor;

Cursor* table_start(Table* table);
Cursor* table_end(Table* table);
void* cursor_value(Cursor* cursor);
void cursor_advance(Cursor* cursor);

#endif
