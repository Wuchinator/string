#include "../s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *memptr = (unsigned char *)str;
  void *out = s21_NULL;
  for (s21_size_t i = 0; i < n && memptr; i++) {
    if ((*memptr) == (unsigned char)c) {
      out = memptr;
      break;
    }
    memptr++;
  }
  return out;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  unsigned char *memptr1 = (unsigned char *)str1;
  unsigned char *memptr2 = (unsigned char *)str2;
  int result, flag = 0;
  for (s21_size_t i = 0; flag != 1 && i < n; i++) {
    result = *memptr1 - *memptr2;
    if (*memptr1 != *memptr2) {
      flag = 1;
    }
    memptr1++;
    memptr2++;
  }
  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *destination = (unsigned char *)dest;
  unsigned char *source = (unsigned char *)src;
  for (s21_size_t i = 0; i < n; i++) destination[i] = source[i];
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *string = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) string[i] = c;
  return str;
}