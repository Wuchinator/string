#include "../s21_string.h"

char* s21_strpbrk(const char* str1, const char* str2) {
  for (int i = 0; str1[i] != '\0'; i++) {
    for (int j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        const char* result = &str1[i];
        return (char*)result;
      }
    }
  }
  return s21_NULL;
}
