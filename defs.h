#ifndef __DEFS_H__
#define __DEFS_H__

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include "row.h"

#define TABLE_MAX_PAGES 100

static const uint32_t PAGE_SIZE = 4096;

// Result of the execution of a meta command
typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

// Result of the conversion of a user input to
// our internal representation of a statement
typedef enum {
  PREPARE_SUCCESS,
  PREPARE_SYNTAX_ERROR,
  PREPARE_STRING_TOO_LONG,
  PREPARE_NEGATIVE_ID,
  PREPARE_UNRECOGNIZED_STATEMENT,
} PrepareResult;

#endif
