#define BUFFER_IMPLEMENTATION
#include "buffer.h"
#include <stdio.h>

int main(void) {
  buffer_t history = buffer_create(0);

  for (int i = 10; i--;) {
    buffer_t entry = buffer_create(0);
    buffer_extend(&entry, "abc", 3);
    buffer_extend(&history, &entry, sizeof(buffer_t));
  }

  for (size_t i = 0; i < history.length / sizeof(buffer_t); i++) {
    buffer_t *entry = &((buffer_t *)history.bytes)[i];
    printf("%s\n", entry->bytes);
  }

  return 0;
}
