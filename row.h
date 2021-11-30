#ifndef __ROW_H__
#define __ROW_H__

#include <stdint.h>

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

// Temporarily hardcoding the format of a row
typedef struct {
  uint32_t id;
  // +1 for space for null character
  char username[COLUMN_USERNAME_SIZE + 1]; 
  char email[COLUMN_EMAIL_SIZE + 1];
} Row;

static const uint32_t ID_SIZE = size_of_attribute(Row, id);
static const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
static const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
static const uint32_t ID_OFFSET = 0;
static const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
static const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
static const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

void print_row(Row* row);

// Serializes the data in the row to a sequence of bytes
// ┌───────────────┬─────────────────────┬───────────────────┐
// │  ID (4 bytes) │  Username (32 bytes)│ Email (255 bytes) │
// └───────────────┴─────────────────────┴───────────────────┘
void serialize_row(Row* source, void* destination);

// Copies packed bytes back into a Row struct
void deserialize_row(void* source, Row* destination);

#endif