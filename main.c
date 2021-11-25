#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  char* buffer;
  size_t buffer_length; // Size of the buffer
  ssize_t input_length; // Size of the input contained in the buffer
} InputBuffer;

InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = (InputBuffer*) malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

void read_input(InputBuffer* input_buffer) {
  ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  // Ignore trailing \n
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer) {
  free(input_buffer->buffer);
  free(input_buffer);
}

void print_prompt() { printf("db > "); }

int main(int argc, char* argv[]) {
  InputBuffer *input_buffer = new_input_buffer();

  while (1) {
    print_prompt();
    read_input(input_buffer);

    if (strcmp(input_buffer->buffer, ".exit") == 0) {
      close_input_buffer(input_buffer);
      exit(EXIT_SUCCESS);
    } else {
      printf("Unrecognised command '%s'.\n", input_buffer->buffer);
    }
  }
}
