#include "s21_string.h"

/* ================= MEMORY ================= */

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *s = (const unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    if (s[i] == (unsigned char)c) return (void *)(s + i);
  }
  return S21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *a = (const unsigned char *)str1;
  const unsigned char *b = (const unsigned char *)str2;
  for (s21_size_t i = 0; i < n; i++) {
    if (a[i] != b[i]) return a[i] - b[i];
  }
  return 0;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;
  for (s21_size_t i = 0; i < n; i++) d[i] = s[i];
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *s = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) s[i] = (unsigned char)c;
  return str;
}

/* ================= STRING ================= */

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  while (str && str[len]) len++;
  return len;
}

char *s21_strchr(const char *str, int c) {
  while (*str) {
    if (*str == (char)c) return (char *)str;
    str++;
  }
  return (c == '\0') ? (char *)str : S21_NULL;
}

char *s21_strrchr(const char *str, int c) {
  char *res = S21_NULL;
  while (*str) {
    if (*str == (char)c) res = (char *)str;
    str++;
  }
  return (c == '\0') ? (char *)str : res;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i] || !str1[i] || !str2[i])
      return (unsigned char)str1[i] - (unsigned char)str2[i];
  }
  return 0;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  for (; i < n && src[i]; i++) dest[i] = src[i];
  for (; i < n; i++) dest[i] = '\0';
  return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t dlen = s21_strlen(dest);
  s21_size_t i = 0;
  while (i < n && src[i]) {
    dest[dlen + i] = src[i];
    i++;
  }
  dest[dlen + i] = '\0';
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t i = 0;
  while (str1[i]) {
    for (s21_size_t j = 0; str2[j]; j++) {
      if (str1[i] == str2[j]) return i;
    }
    i++;
  }
  return i;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  while (*str1) {
    for (const char *s = str2; *s; s++) {
      if (*str1 == *s) return (char *)str1;
    }
    str1++;
  }
  return S21_NULL;
}

char *s21_strstr(const char *haystack, const char *needle) {
  if (!*needle) return (char *)haystack;

  for (; *haystack; haystack++) {
    const char *h = haystack;
    const char *n = needle;
    while (*h && *n && *h == *n) {
      h++;
      n++;
    }
    if (!*n) return (char *)haystack;
  }
  return S21_NULL;
}

char *s21_strtok(char *str, const char *delim) {
  static char *next = S21_NULL;

  if (str) next = str;
  if (!next) return S21_NULL;

  while (*next && s21_strchr(delim, *next)) next++;

  if (!*next) return S21_NULL;

  char *start = next;
  while (*next && !s21_strchr(delim, *next)) next++;

  if (*next) *next++ = '\0';

  return start;
}

/* ================= STRERROR ================= */

#ifdef __linux__
static const char *s21_errlist[] = {"Success",
                                    "Operation not permitted",
                                    "No such file or directory",
                                    "No such process",
                                    "Interrupted system call",
                                    "Input/output error",
                                    "No such device or address",
                                    "Argument list too long",
                                    "Exec format error",
                                    "Bad file descriptor",
                                    "No child processes",
                                    "Resource temporarily unavailable",
                                    "Cannot allocate memory",
                                    "Permission denied",
                                    "Bad address",
                                    "Block device required",
                                    "Device or resource busy",
                                    "File exists",
                                    "Invalid cross-device link",
                                    "No such device",
                                    "Not a directory",
                                    "Is a directory",
                                    "Invalid argument",
                                    "Too many open files in system",
                                    "Too many open files",
                                    "Inappropriate ioctl for device",
                                    "Text file busy",
                                    "File too large",
                                    "No space left on device",
                                    "Illegal seek",
                                    "Read-only file system",
                                    "Too many links",
                                    "Broken pipe",
                                    "Numerical argument out of domain",
                                    "Numerical result out of range"};
#define S21_ERR_MAX 34
#endif

#ifdef __APPLE__
static const char *s21_errlist[] = {"Undefined error: 0",
                                    "Operation not permitted",
                                    "No such file or directory",
                                    "No such process",
                                    "Interrupted system call",
                                    "Input/output error",
                                    "Device not configured",
                                    "Argument list too long",
                                    "Exec format error",
                                    "Bad file descriptor",
                                    "No child processes",
                                    "Resource deadlock avoided",
                                    "Cannot allocate memory",
                                    "Permission denied",
                                    "Bad address",
                                    "Block device required",
                                    "Resource busy",
                                    "File exists",
                                    "Cross-device link",
                                    "Operation not supported by device",
                                    "Not a directory",
                                    "Is a directory",
                                    "Invalid argument",
                                    "Too many open files in system",
                                    "Too many open files",
                                    "Inappropriate ioctl for device",
                                    "Text file busy",
                                    "File too large",
                                    "No space left on device",
                                    "Illegal seek",
                                    "Read-only file system",
                                    "Too many links",
                                    "Broken pipe",
                                    "Numerical argument out of domain",
                                    "Result too large"};
#define S21_ERR_MAX 34
#endif

char *s21_strerror(int errnum) {
  static char buffer[128];

  if (errnum >= 0 && errnum <= S21_ERR_MAX) return (char *)s21_errlist[errnum];

#ifdef __linux__
  s21_sprintf(buffer, "Unknown error %d", errnum);
#endif

#ifdef __APPLE__
  s21_sprintf(buffer, "Unknown error: %d", errnum);
#endif

  return buffer;
}
