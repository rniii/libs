#include "buffer.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
  buffer_t buf = buffer_create(0);
  buffer_extend(&buf, "bar", 3);
  buffer_insert(&buf, 0, "foo", 3);

  assert(strcmp(buf.bytes, "foobar") == 0);
  assert(buf.length == 6);

  buffer_remove(&buf, 1, 3);
  buffer_push(&buf, 't');
  assert(strcmp(buf.bytes, "fart") == 0);

  buffer_truncate(&buf, 1);
  assert(strcmp(buf.bytes, "f") == 0);

  buffer_clear(&buf);
  assert(buf.length == 0);

  buffer_reserve(&buf, 32);
  assert(buf.capacity >= buf.length + 32);

  buffer_shrink_to(&buf, 16);
  assert(buf.capacity >= 16);

  buffer_destroy(buf);
}
