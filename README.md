# 99¢

Single-header public domain libraries for C99.

## [buffer.h](buffer.h)

Simple dynamically allocated string buffers.

| SLoC | Category |
| ---- | -------- |
| 97   | Utils    |

```c
buffer_t buf = buffer_create(0);
buffer_extend(&buf, "bar", 3);
buffer_insert(&buf, 0, "foo", 3);
buffer_remove(&buf, 1, 3);
buffer_push(&buf, 't');

assert(strcmp(buf.bytes, "fart") == 0);
```

## License

These libraries are dedicated to the public domain. On situations where this is not possible, they
fall under the CC0 Public Domain Dedication.
