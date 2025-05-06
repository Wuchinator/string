#ifndef S21_SPRINTF
#define S21_SPRINTF

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

#include "../s21_string.h"

#define OR ||
#define AND &&
#define CURRENT format[i]
#define ELIF else if
#define endOfstr '\0'
#define WIDTH flag.width
#define start_cycle for (int i = 0; CURRENT != endOfstr; i++)
#define UINT64 unsigned long int
#define UINT8 unsigned short int
typedef struct flags {
  int Fformat;
  int sign;
  int width;
  int accuracy;
  int setAccuracy;
  int align;
  int length;
  int dot;
  int double_length;
  int spec;
  int isDigit;
  int zero_width;
} flags;

void trimZeroes(char* trim_zeroes);
void flagG(int* exp, struct flags flag, double* num, int* num_sign,
           double* num_copy);
void flagPercent(char* string, struct flags* flag);
void flagC(struct flags flag, va_list* vars, char* string, int* null_p,
           char* str, int* nulls);
void flagP(struct flags flag, char* string, va_list* vars);
void flagN(struct flags flag, va_list* vars, char* str);
void flagF(struct flags flag, va_list* vars, char* string);
void flagS(struct flags flag, char* string, va_list* vars);
void flagU(struct flags flag, char* string, va_list* vars);
void FlagDi(struct flags flag, va_list* vars, char* string);
void flagO(struct flags flag, char* string, va_list* vars, char current,
           int* radix);
void process(struct flags flag, char* string, char* str);
void splitting(double* num, int* num_sign, int* exp);
void flagEeGg(struct flags flag, va_list* vars, char current, char* string);

void* itoa(__int128 n, char* s, int radix, int sign, int precision);
void ftoa(long double n, char* s, int digits, int sign);

#endif