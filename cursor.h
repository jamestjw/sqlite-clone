#ifndef __CURSOR_H__
#define __CURSOR_H__

#include "defs.h"
#include "table.h"

// Identifies a position in the table
// by pointing to a particular cell in
// a node (page) of a b+ tree
typedef struct {
  Table* table;
  uint32_t page_num;
  uint32_t cell_num;
  bool end_of_table;
} Cursor;

Cursor* table_start(Table* table);
// Returns a cursor to the position of the given key
// or if the key is absent, return the position 
// where it should be inserted
Cursor* table_find(Table* table, uint32_t key);
void* cursor_value(Cursor* cursor);
void cursor_advance(Cursor* cursor);

#endif
