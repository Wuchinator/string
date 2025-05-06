#include "s21_sscanf.h"

int s21_sscanf(const char* buffer, const char* format, ...) {
  int err = 0;
  int matches = is_empty(buffer) ? -1 : 0;
  int isScanned = 0;
  const char* fmt_ptr = format;
  const char* buf_ptr = buffer;
  va_list args;
  va_start(args, format);

  while (*fmt_ptr && !err && matches != -1) {
    if (*fmt_ptr == '%' && *(fmt_ptr + 1) != '%') {
      fmt_ptr++;

      Token token;
      token_init(&token);
      token_setup(&token, &fmt_ptr);
      const char spec = token.specifier;
      if (!spec) {
        err = 1;
        continue;
      }
      matches += router(&buffer, &buf_ptr, &args, &token, &isScanned);
      err = token.err;
    } else if (*fmt_ptr == '%' && *(fmt_ptr + 1) == '%') {
      buf_ptr++;
      fmt_ptr += 2;
    } else if (isspace(*fmt_ptr)) {
      SKIP_WHITESPACE(buf_ptr);
      SKIP_WHITESPACE(fmt_ptr);
    } else {
      buf_ptr++;
      fmt_ptr++;
    }
  }

  va_end(args);
  return matches;
}

void token_init(Token* t) {
  t->width = -1;
  t->precision = -1;
  t->is_suppressed = 0;
  t->length = '\0';
  t->specifier = '\0';
  t->err = 0;
}
void token_setup(Token* t, const char** fmt_ptr) {
  determinate_suppression(t, fmt_ptr);
  determinate_width(t, fmt_ptr);
  determinate_length(t, fmt_ptr);

  if (s21_strchr("udioxXgGeEfnpcs", **fmt_ptr)) t->specifier = **fmt_ptr;
  (*fmt_ptr)++;
}

int router(const char** buffer, const char** buf_ptr, va_list* args, Token* t,
           int* isScanned) {
  int matches = 0;
  const char spec = t->specifier;
  int base = (spec == 'o') * OCT_BASE +
             (spec == 'd' || spec == 'i' || spec == 'u') * DEC_BASE +
             (spec == 'x' || spec == 'X') * HEX_BASE;

  int isfloat = s21_strchr("efgEG", spec) != NULL;

  if (base && processing_int(args, buf_ptr, t, base)) {
    if (!t->is_suppressed) matches++;
    *isScanned = 1;
  } else if (isfloat && processing_float(args, buf_ptr, t)) {
    if (!t->is_suppressed) matches++;
    *isScanned = 1;
  } else if (spec == 's' && **buf_ptr) {
    processing_string(args, buf_ptr, t);
    if (!t->is_suppressed) matches++;
    *isScanned = 1;
  } else if (spec == 'c' && **buf_ptr) {
    processing_char(args, buf_ptr, t);
    if (!t->is_suppressed && !t->err) matches++;
    *isScanned = 1;
  } else if (spec == 'p' && **buf_ptr) {
    processing_pointer(args, buf_ptr, t);
    if (!t->is_suppressed && !t->err) matches++;
    *isScanned = 1;
  } else if (spec == 'n') {
    int* n_ptr = va_arg(*args, int*);
    *n_ptr = (*isScanned) ? (int)(*buf_ptr - *buffer) : 0;
  }

  return matches;
}

int processing_int(va_list* args, const char** buffer, Token* t, int base) {
  int status = 0;
  int sign = define_sign(buffer, t);
  s21_size_t num = 0;

  SKIP_WHITESPACE(*buffer);

  if ((isdigit(**buffer) || (isxdigit(**buffer) && base == HEX_BASE)) &&
      t->width) {
    num = str_to_num(buffer, base, t);
    num *= sign;
    status = 1;

    if (!t->is_suppressed) assignment_int(args, num, t->length);
  } else {
    t->err = 1;
  }

  return status;
}

int processing_float(va_list* args, const char** buffer, Token* t) {
  int status = 0;
  int degree = 0;
  int sign = define_sign(buffer, t);
  long double num = 0;
  long double mantissa = 0;
  long double exponent = 0;

  SKIP_WHITESPACE(*buffer);

  if (t->width &&
      (isdigit(**buffer) || (**buffer == '.' && isdigit(*(*buffer + 1))) ||
       s21_strchr("iInN", **buffer))) {
    if (isdigit(**buffer) || (**buffer == '.' && isdigit(*(*buffer + 1)))) {
      mantissa = (long double)str_to_num(buffer, DEC_BASE, t);
      parse_exponent(buffer, t, &exponent, &degree);
      num = sign * (mantissa + exponent) * pow(10, degree);
    } else {
      char* subj;
      if (**buffer == 'i' || **buffer == 'I')
        subj = "inf";
      else if (**buffer == 'n' || **buffer == 'N')
        subj = "nan";
      num = parse_inf_nan(subj, buffer, t);
    }
    if (!t->err) status = 1;

    if (!t->is_suppressed && !t->err) assignment_float(args, num, t->length);
  } else {
    t->err = 1;
  }

  return status;
}

void processing_string(va_list* args, const char** buffer, Token* t) {
  SKIP_WHITESPACE(*buffer);
  if (t->is_suppressed) {
    while (**buffer && !isspace(**buffer)) (*buffer)++;

  } else {
    char* str_ptr = NULL;
    wchar_t* wstr_ptr = NULL;
    if (t->length == '\0')
      str_ptr = va_arg(*args, char*);
    else if (t->length == 'l')
      wstr_ptr = va_arg(*args, wchar_t*);

    SKIP_WHITESPACE(*buffer);

    while (**buffer && !isspace(**buffer) && t->width != 0) {
      if (str_ptr != NULL)
        *str_ptr++ = *(*buffer)++;
      else
        *wstr_ptr++ = *(*buffer)++;
      t->width--;
    }

    if (str_ptr != NULL)
      *str_ptr = '\0';
    else
      *wstr_ptr = L'\0';
  }
}

void processing_char(va_list* args, const char** buffer, Token* t) {
  if (t->is_suppressed) {
    (*buffer)++;

  } else {
    if (t->length == '\0') {
      char* ch_ptr = va_arg(*args, char*);
      *ch_ptr = **buffer;
    } else if (t->length == 'l') {
      wchar_t* wch_ptr = va_arg(*args, wchar_t*);
      *wch_ptr = **buffer;
    }

    (*buffer)++;
  }
}

void processing_pointer(va_list* args, const char** buffer, Token* t) {
  SKIP_WHITESPACE(*buffer);
  if (!isxdigit(**buffer)) t->err = 1;
  long decimal = str_to_num(buffer, HEX_BASE, t);
  if (!t->is_suppressed) {
    void** dest = va_arg(*args, void**);
    *dest = (void*)(0x0 + decimal);
  }
}

int is_empty(const char* str) {
  int empty = 1;
  for (; *str && empty; str++)
    if (!isspace(*str)) empty = 0;
  return empty;
}
void determinate_suppression(Token* t, const char** fmt_ptr) {
  if (**fmt_ptr == '*') {
    (*fmt_ptr)++;
    t->is_suppressed = 1;
  }
}
void determinate_length(Token* t, const char** fmt_ptr) {
  if (**fmt_ptr == 'h' || **fmt_ptr == 'l' || **fmt_ptr == 'L') {
    t->length = **fmt_ptr;
    if (**fmt_ptr == 'l' && *(*fmt_ptr + 1) == 'l') {
      t->length = 'L';
      (*fmt_ptr)++;
    }
    (*fmt_ptr)++;
  }
}
void determinate_width(Token* t, const char** fmt_ptr) {
  if (isdigit(**fmt_ptr)) {
    for (t->width = 0; isdigit(**fmt_ptr); (*fmt_ptr)++) {
      t->width = t->width * 10 + (**fmt_ptr - '0');
    }
    // если ширина = 0, ставим значение по дефолту
    t->width = (!t->width) ? -1 : t->width;
  }
}
int define_sign(const char** buffer, Token* t) {
  int sign = 1;
  if (**buffer == '-' || **buffer == '+') {
    sign = (**buffer == '-') ? -1 : 1;
    (*buffer)++;
    if (t->width == 1) t->err = 1;
    t->width--;
  }

  return sign;
}
int parse_base(const char** buf, int base, Token* t) {
  int result = base;
  if ((base == HEX_BASE || t->specifier == 'i') && **buf == '0' &&
      (*((*buf) + 1) == 'x' || *((*buf) + 1) == 'X')) {
    (*buf) += 2;
    t->width -= 2;
    result = HEX_BASE;
  } else if ((base == OCT_BASE || t->specifier == 'i') && **buf == '0') {
    (*buf)++;
    t->width--;
    result = OCT_BASE;
  }
  return result;
}
s21_size_t str_to_num(const char** buf, int base, Token* t) {
  s21_size_t num = 0;
  int isFloat = s21_strchr("efgEG", t->specifier) != NULL;
  base = parse_base(buf, base, t);

  while (t->width != 0 && ((base == DEC_BASE && isdigit(**buf)) ||
                           (base == HEX_BASE && isxdigit(**buf)) ||
                           (base == OCT_BASE && isodigit(**buf)))) {
    char digit = ('A' <= **buf && **buf <= 'Z') ? (**buf + SHIFT) : **buf;
    num = num * base + (isdigit(digit) ? (digit - '0') : (digit - 'a' + 10));
    (*buf)++;
    t->width--;
    if (isFloat) t->precision++;
  }

  return num;
}
void assignment_int(va_list* args, s21_size_t num, char length) {
  if (length == '\0') {
    int* int_ptr = va_arg(*args, int*);
    *int_ptr = (int)num;
  } else if (length == 'h') {
    short int* short_int_ptr = va_arg(*args, short int*);
    *short_int_ptr = (short int)num;
  } else if (length == 'l') {
    long int* long_int_ptr = va_arg(*args, long int*);
    *long_int_ptr = (long int)num;
  } else if (length == 'L') {
    long long* long_long_ptr = va_arg(*args, long long*);
    *long_long_ptr = (long long)num;
  }
}

void assignment_float(va_list* args, long double num, char length) {
  if (length == '\0') {
    float* float_ptr = va_arg(*args, float*);
    *float_ptr = (float)num;
  } else if (length == 'l') {
    double* double_ptr = va_arg(*args, double*);
    *double_ptr = (double)num;
  } else if (length == 'L') {
    long double* long_double_ptr = va_arg(*args, long double*);
    *long_double_ptr = (long double)num;
  }
}

void parse_exponent(const char** buf, Token* t, long double* exponent,
                    int* degree) {
  if (**buf == '.' && isdigit(*(*buf + 1)) && t->width != 0) {
    (*buf)++;
    t->width--;
    if (t->width != 0) {
      t->precision = 0;
      *exponent = (long double)str_to_num(buf, DEC_BASE, t);

      for (; t->precision > 0; t->precision--) {
        *exponent *= 0.1;
      }
    } else {
      t->err = 1;
    }
  }

  if ((**buf == 'E' || **buf == 'e') && (t->width != 0)) {
    (*buf)++;
    int exp_sign = define_sign(buf, t);
    *degree = exp_sign * (int)str_to_num(buf, DEC_BASE, t);
  }
}
long double parse_inf_nan(char* subject, const char** buf, Token* t) {
  long double num = 0;
  char content[4] = "ooo";
  for (int i = 0; i < 3 && t->width != 0 && **buf; i++) {
    if (**buf == subject[i] || **buf == subject[i] - SHIFT) {
      content[i] = subject[i];
      t->width--;
      (*buf)++;
    }
  }

  if (s21_strncmp(subject, content, 3) == 0) {
    num = (content[0] == 'i') ? INFINITY : NAN;
  } else {
    t->err = 1;
  }

  return num;
}