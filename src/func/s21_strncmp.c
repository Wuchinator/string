#include "../s21_string.h"

int s21_strncmp(const char *string1, const char *string2, s21_size_t n) {
  int diffr = 0;
  for (s21_size_t i = 0; i < n && string1[i] != '\0' && string2[i] != '\0';
       i++) {
    if (string1[i] != string2[i]) {
      diffr = string1[i] - string2[i];
      break;
    }
    // если один из символов является '\0'
    if (!(*string1 && *string2)) diffr = *string1 - *string2;
  }
  return diffr;
}