#include "../s21_string.h"

void* s21_insert(const char* src, const char* str, s21_size_t start_index) {
  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);
  char* result = (char*)malloc(src_len + str_len + 1);
  for (s21_size_t i = 0; i < start_index; i++) {
    result[i] = src[i];
  }
  for (s21_size_t i = 0; i < str_len; i++) {
    result[start_index + i] = str[i];
  }

  for (s21_size_t i = start_index; i < src_len; i++) {
    result[i + str_len] = src[i];
  }
  result[src_len + str_len] = '\0';
  return result;
}
