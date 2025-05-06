#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  int len = (int)s21_strlen(str);
  char *last_occurrence = s21_NULL;
  for (int i = 0; i <= len; i++) {
    if (str[i] == c) {
      last_occurrence = (char *)&str[i];
    }
  }
  return last_occurrence;
}
