#include <stdio.h>
#include <string.h>

#include "row.h"

void print_row(Row* row) {
  printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}

// Serializes the data in the row to a sequence of bytes
// ┌───────────────┬─────────────────────┬───────────────────┐
// │  ID (4 bytes) │  Username (32 bytes)│ Email (255 bytes) │
// └───────────────┴─────────────────────┴───────────────────┘
void serialize_row(Row* source, void* destination) {
  memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
  strncpy(destination + USERNAME_OFFSET, source->username, USERNAME_SIZE);
  strncpy(destination + EMAIL_OFFSET, source->email, EMAIL_SIZE);
}

// Copies packed bytes back into a Row struct
void deserialize_row(void* source, Row* destination) {
  memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
  memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
  memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}