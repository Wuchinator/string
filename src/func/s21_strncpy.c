#include "../s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  int Len = n > s21_strlen(src) ? (s21_strlen(src) + 1) : n;
  for (int i = 0; i < Len; i++) {
    dest[i] = src[i];
  }
  return dest;
}

char *s21_strcpy(char *dest, const char *src) {
  char *ptr = dest;
  while (*src) {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
  return ptr;
}