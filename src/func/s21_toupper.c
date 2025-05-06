#include "../s21_string.h"

void *s21_to_upper(const char *str) {
  s21_size_t length = s21_strlen(str) + 1;
  char *result = malloc((length) * sizeof(char));
  for (s21_size_t i = 0; i <= length; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      result[i] = str[i] - 32;
    } else {
      result[i] = str[i];
    }
  }
  return result;
}