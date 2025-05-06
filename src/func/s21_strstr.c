#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  int flag = 0;
  if (haystack == NULL || needle == NULL) return NULL;
  if (*haystack == '\0' && *needle == '\0') {
    haystack = "";
    flag = 1;
  }
  int t = 0;
  if (flag == 0) {
    while (*haystack != '\0' && t == 0) {
      const char *h = haystack;
      const char *n = needle;

      while (*h != '\0' && *n != '\0' && *h == *n) {
        h++;
        n++;
      }

      if (*n == '\0') t = 1;
      if (t == 0) haystack++;
    }
    if (t == 0) haystack = s21_NULL;
  }
  return (char *)haystack;
}
