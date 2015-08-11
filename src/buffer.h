#ifndef CMARK_BUFFER_H
#define CMARK_BUFFER_H

#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int bufsize_t;

typedef struct {
  unsigned char *ptr;
  bufsize_t asize, size;
} cmark_strbuf;

extern unsigned char cmark_strbuf__initbuf[];

#define GH_BUF_INIT                                                            \
  { cmark_strbuf__initbuf, 0, 0 }
#define BUFSIZE_MAX INT_MAX

/**
 * Initialize a cmark_strbuf structure.
 *
 * For the cases where GH_BUF_INIT cannot be used to do static
 * initialization.
 */
void cmark_strbuf_init(cmark_strbuf *buf, bufsize_t initial_size);

/**
 * Grow the buffer to hold at least `target_size` bytes.
 */
void cmark_strbuf_grow(cmark_strbuf *buf, bufsize_t target_size);

void cmark_strbuf_free(cmark_strbuf *buf);
void cmark_strbuf_swap(cmark_strbuf *buf_a, cmark_strbuf *buf_b);

bufsize_t cmark_strbuf_len(const cmark_strbuf *buf);

int cmark_strbuf_cmp(const cmark_strbuf *a, const cmark_strbuf *b);

unsigned char *cmark_strbuf_detach(cmark_strbuf *buf);
void cmark_strbuf_copy_cstr(char *data, bufsize_t datasize,
                            const cmark_strbuf *buf);

CMARK_INLINE const char *cmark_strbuf_cstr(const cmark_strbuf *buf) {
  return (char *)buf->ptr;
}

#define cmark_strbuf_at(buf, n) ((buf)->ptr[n])

void cmark_strbuf_set(cmark_strbuf *buf, const unsigned char *data,
                      bufsize_t len);
void cmark_strbuf_sets(cmark_strbuf *buf, const char *string);
void cmark_strbuf_putc(cmark_strbuf *buf, int c);
void cmark_strbuf_put(cmark_strbuf *buf, const unsigned char *data,
                      bufsize_t len);
void cmark_strbuf_puts(cmark_strbuf *buf, const char *string);
void cmark_strbuf_clear(cmark_strbuf *buf);

bufsize_t cmark_strbuf_strchr(const cmark_strbuf *buf, int c, bufsize_t pos);
bufsize_t cmark_strbuf_strrchr(const cmark_strbuf *buf, int c, bufsize_t pos);
void cmark_strbuf_drop(cmark_strbuf *buf, bufsize_t n);
void cmark_strbuf_truncate(cmark_strbuf *buf, bufsize_t len);
void cmark_strbuf_rtrim(cmark_strbuf *buf);
void cmark_strbuf_trim(cmark_strbuf *buf);
void cmark_strbuf_normalize_whitespace(cmark_strbuf *s);
void cmark_strbuf_unescape(cmark_strbuf *s);

/* Print error and abort. */
void cmark_strbuf_overflow_err(void);

CMARK_INLINE bufsize_t cmark_strbuf_check_bufsize(size_t size) {
  if (size > BUFSIZE_MAX) {
    cmark_strbuf_overflow_err();
  }
  return (bufsize_t)size;
}

CMARK_INLINE bufsize_t cmark_strbuf_safe_strlen(const char *str) {
  return cmark_strbuf_check_bufsize(strlen(str));
}

#ifdef __cplusplus
}
#endif

#endif
