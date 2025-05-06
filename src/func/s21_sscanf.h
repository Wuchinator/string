#ifndef S21_SSCANF
#define S21_SSCANF

#include "../s21_string.h"

#define SHIFT 32
#define OCT_BASE 8
#define DEC_BASE 10
#define HEX_BASE 16

#define SKIP_WHITESPACE(x) \
  while (isspace(*(x))) {  \
    (x)++;                 \
  }
#define isodigit(c) ('0' <= (c) && (c) <= '7')

typedef struct {
  long int width;
  long int precision;
  int is_suppressed;
  char length;
  char specifier;
  int err;
} Token;

void assignment_int(va_list* args, s21_size_t num, char length);
void assignment_float(va_list* args, long double num, char length);

int router(const char** buffer, const char** buf_ptr, va_list* args, Token* t,
           int* isScanned);

int is_empty(const char* str);
void token_init(Token* token);
void token_setup(Token* token, const char** fmt_ptr);
void determinate_suppression(Token* t, const char** fmt_ptr);
void determinate_length(Token* t, const char** fmt_ptr);
void determinate_width(Token* t, const char** fmt_ptr);
int define_sign(const char** buffer, Token* token);
s21_size_t str_to_num(const char** buf, int base, Token* token);

int parse_base(const char** buf, int base, Token* t);
void parse_exponent(const char** b, Token* t, long double* e, int* d);
long double parse_inf_nan(char* subject, const char** buf, Token* t);

int processing_int(va_list* args, const char** buffer, Token* token, int base);
int processing_float(va_list* args, const char** buffer, Token* token);
void processing_char(va_list* args, const char** buffer, Token* token);
void processing_pointer(va_list* args, const char** buffer, Token* token);
void processing_string(va_list* args, const char** buffer, Token* token);
#endif