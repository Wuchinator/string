#include "../s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *lastToken = s21_NULL;

  if (str == s21_NULL) {
    str = lastToken;
  }

  if (str == s21_NULL || *str == '\0' || delim == s21_NULL) {
    return s21_NULL;
  }

  while (*str && s21_strchr(delim, *str) != s21_NULL) {
    str++;
  }

  if (*str == '\0') {
    lastToken = s21_NULL;
    return s21_NULL;
  }

  char *token = str;
  str = s21_strpbrk(token, delim);
  if (str != s21_NULL) {
    *str = '\0';
    lastToken = str + 1;
  } else {
    lastToken = s21_NULL;
  }

  return token;
}