#ifndef __PAGER_H__
#define __PAGER_H__

#include "defs.h"

// Responsible for the reading and writing of pages to a file
typedef struct {
  int file_descriptor;
  uint32_t file_length;
  uint32_t num_pages;
  void* pages[TABLE_MAX_PAGES];
} Pager;

Pager* pager_open(const char* filename);
void pager_flush(Pager* pager, uint32_t page_num);
void* get_page(Pager* pager, uint32_t page_num);

#endif
