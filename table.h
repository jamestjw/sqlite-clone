#ifndef __TABLE_H__
#define __TABLE_H__

#include <stdint.h>

#include "pager.h"

typedef struct {
  uint32_t root_page_num; // A table needs this to identify the root of its b+-tree
  Pager* pager;
} Table;

Table* db_open(const char* filename);
void db_close(Table* table) ;

#endif
