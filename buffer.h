#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct buffer_t buffer_t;

/// Construct a new buffer with given capacity
static buffer_t buffer_create(size_t capacity);
/// Deallocate a buffer
static void buffer_destroy(buffer_t);

/// Reserve space for additional bytes, allocating more memory
static void buffer_reserve(buffer_t *, size_t additional);
/// Shrink the buffer, deallocating some memory
static void buffer_shrink_to(buffer_t *, size_t minimum);

/// Add a single byte to the end of the buffer
static void buffer_push(buffer_t *, char value);
/// Extend the buffer with given bytes
static void buffer_extend(buffer_t *, const char *value, size_t size);
/// Insert bytes at given index
static void buffer_insert(buffer_t *, size_t idx, const char *value,
                          size_t size);

/// Remove all data in the buffer
static void buffer_clear(buffer_t *);
/// Limit the buffer to a size, removing bytes after the index
static void buffer_truncate(buffer_t *, size_t size);
/// Remove bytes at given index
static void buffer_remove(buffer_t *, size_t idx, size_t size);

// -------- Implementation

#ifndef BUFFER_MIN
/// Minimum capacity for buffers, must be at least 1
#define BUFFER_MIN 32
#endif

struct buffer_t {
  size_t capacity;
  size_t length;
  char *bytes;
};

static inline buffer_t buffer_create(size_t capacity) {
  capacity = capacity < BUFFER_MIN ? BUFFER_MIN : capacity;
  char *data = malloc(capacity);
  data[0] = 0;
  return (buffer_t){capacity, 0, data};
}
static inline void buffer_destroy(buffer_t buf) { free(buf.bytes); }

static void buffer__resize(buffer_t *buf, size_t cap) {
  buf->bytes = realloc(buf->bytes, cap);
  buf->capacity = cap;
}
static void buffer_reserve(buffer_t *buf, size_t additional) {
  size_t req = buf->length + additional + 1;
  if (req <= buf->capacity)
    return;

  size_t cap = buf->capacity * 2;
  buffer__resize(buf, req > cap ? req : cap);
}
static void buffer_shrink_to(buffer_t *buf, size_t minimum) {
  if (buf->capacity <= minimum)
    return;
  minimum = minimum < BUFFER_MIN ? BUFFER_MIN : minimum;
  buffer__resize(buf, buf->length > minimum ? buf->length : minimum);
}

static void buffer_push(buffer_t *buf, char value) {
  buffer_reserve(buf, 1);
  buf->bytes[buf->length++] = value;
  buf->bytes[buf->length] = 0;
}
static void buffer_extend(buffer_t *buf, const char *value, size_t size) {
  buffer_reserve(buf, size);
  memcpy(buf->bytes + buf->length, value, size);
  buf->bytes[buf->length + size] = 0;
  buf->length += size;
}
static void buffer_insert(buffer_t *buf, size_t idx, const char *value,
                          size_t size) {
  if (idx > buf->length) {
    assert(0 && "index out of bounds");
    return;
  }
  buffer_reserve(buf, size);
  memmove(buf->bytes + idx + size, buf->bytes + idx, buf->length - idx);
  memcpy(buf->bytes + idx, value, size);
  buf->length += size;
}

static void buffer_clear(buffer_t *buf) { buf->length = 0; }
static void buffer_truncate(buffer_t *buf, size_t size) {
  if (size >= buf->length)
    return;
  buf->bytes[size] = 0;
  buf->length = size;
}
static void buffer_remove(buffer_t *buf, size_t idx, size_t size) {
  if (idx + size > buf->length) {
    assert(0 && "index out of bounds");
    return;
  }
  buf->length -= size;
  memcpy(buf->bytes + idx, buf->bytes + idx + size, size);
}
