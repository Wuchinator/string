#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  int flag = 0;
  const char *res = NULL;
  const char *str2 = str;
  while (*str2 != '\0' && flag == 0) {
    if (*str2 == c) {
      res = str2;
      flag = 1;
    }
    str2++;
  }

  if (c == '\0') {
    res = str2;
  }

  return (char *)res;
}
