#ifndef __INPUT_H__
#define __INPUT_H__

#include "defs.h"

typedef struct {
  char* buffer;
  size_t buffer_length; // Size of the buffer
  ssize_t input_length; // Size of the input contained in the buffer
} InputBuffer;

InputBuffer* new_input_buffer();
void close_input_buffer(InputBuffer* input_buffer);
void read_input(InputBuffer* input_buffer);

#endif