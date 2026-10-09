#include "s21_string.h"

/* ================= HELPERS ================= */

static int s21_is_digit(char c) { return c >= '0' && c <= '9'; }

static void s21_reverse(char *str) {
  int i = 0;
  int j = s21_strlen(str) - 1;
  while (i < j) {
    char t = str[i];
    str[i++] = str[j];
    str[j--] = t;
  }
}

static void s21_lltoa(long long val, char *buf) {
  int i = 0;
  int neg = val < 0;
  if (neg) val = -val;

  do {
    buf[i++] = (char)(val % 10 + '0');
    val /= 10;
  } while (val);

  if (neg) buf[i++] = '-';
  buf[i] = '\0';
  s21_reverse(buf);
}

static void s21_ulltoa(unsigned long long val, char *buf) {
  int i = 0;
  do {
    buf[i++] = (char)(val % 10 + '0');
    val /= 10;
  } while (val);

  buf[i] = '\0';
  s21_reverse(buf);
}

static void s21_ftoa(double val, char *buf, int precision) {
  if (precision < 0) precision = 6;

  long long ip = (long long)val;
  double frac = val - (double)ip;
  if (frac < 0) frac = -frac;

  s21_lltoa(ip, buf);
  int len = s21_strlen(buf);
  buf[len++] = '.';

  for (int i = 0; i < precision; i++) {
    frac *= 10;
    buf[len++] = (char)((int)frac + '0');
    frac -= (int)frac;
  }
  buf[len] = '\0';
}

/* ================= FORMAT ================= */

typedef struct {
  int minus;
  int plus;
  int space;
  int width;
  int precision;
  char length;
  char spec;
} s21_fmt;

static const char *s21_parse(const char *f, s21_fmt *fmt) {
  while (*f == '-' || *f == '+' || *f == ' ') {
    if (*f == '-') fmt->minus = 1;
    if (*f == '+') fmt->plus = 1;
    if (*f == ' ') fmt->space = 1;
    f++;
  }

  if (s21_is_digit(*f)) {
    fmt->width = 0;
    while (s21_is_digit(*f)) fmt->width = fmt->width * 10 + (*f++ - '0');
  }

  if (*f == '.') {
    f++;
    fmt->precision = 0;
    while (s21_is_digit(*f))
      fmt->precision = fmt->precision * 10 + (*f++ - '0');
  }

  if (*f == 'h' || *f == 'l') fmt->length = *f++;

  fmt->spec = *f++;
  return f;
}

static void s21_write(char **out, const char *s, s21_fmt *fmt) {
  int len = s21_strlen(s);
  int pad = fmt->width > len ? fmt->width - len : 0;

  if (!fmt->minus)
    while (pad--) *(*out)++ = ' ';

  while (*s) *(*out)++ = *s++;

  if (fmt->minus)
    while (pad--) *(*out)++ = ' ';
}

/* ================= SPRINTF ================= */

int s21_sprintf(char *str, const char *format, ...) {
  va_list ap;
  va_start(ap, format);

  char *out = str;

  while (*format) {
    if (*format != '%') {
      *out++ = *format++;
      continue;
    }

    format++;
    s21_fmt fmt = {0, 0, 0, 0, -1, 0, 0};
    format = s21_parse(format, &fmt);

    char buf[256] = {0};

    if (fmt.spec == 'd') {
      long long v = (fmt.length == 'l') ? va_arg(ap, long) : va_arg(ap, int);
      s21_lltoa(v, buf);
      s21_write(&out, buf, &fmt);

    } else if (fmt.spec == 'u') {
      unsigned long long v = (fmt.length == 'l') ? va_arg(ap, unsigned long)
                                                 : va_arg(ap, unsigned int);
      s21_ulltoa(v, buf);
      s21_write(&out, buf, &fmt);

    } else if (fmt.spec == 'f') {
      double v = va_arg(ap, double);
      s21_ftoa(v, buf, fmt.precision);
      s21_write(&out, buf, &fmt);

    } else if (fmt.spec == 's') {
      char *v = va_arg(ap, char *);
      s21_write(&out, v ? v : "(null)", &fmt);

    } else if (fmt.spec == 'c') {
      buf[0] = (char)va_arg(ap, int);
      buf[1] = '\0';
      s21_write(&out, buf, &fmt);

    } else if (fmt.spec == '%') {
      *out++ = '%';
    }
  }

  *out = '\0';
  va_end(ap);
  return out - str;
}
