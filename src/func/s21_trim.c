#include "../s21_string.h"
void *s21_trim(const char *src, const char *trim_chars) {
  if (src == NULL || trim_chars == NULL) {
    return NULL;
  }
  int length = s21_strlen(src);
  int length2 = s21_strlen(trim_chars);
  int b = 0, found = 0;
  for (int i = 0; i < length && b == 0; i++) {
    for_trim(length2, &b, &found, src, trim_chars, i);
  }
  char *result = (char *)malloc((length - found + 1) * sizeof(char));
  for (int i = 0; i < length - found; i++) {
    result[i] = src[i + found];
  }
  int c = 0, found2 = 0;

  for (int i = length - 1; i >= 0 && c == 0; i--) {
    for_trim(length2, &c, &found, src, trim_chars, i);
  }
  char *result2 = (char *)malloc((length - found - found2 + 1) * sizeof(char));
  for (int i = 0; i < length - found - found2; i++) {
    result2[i] = result[i];
  }
  free(result);
  return result2;
}

void for_trim(int length2, int *b, int *found, const char *src,
              const char *trim_chars, int i) {
  int flag = 0;
  for (int j = 0; j < length2 && *b == 0 && flag == 0; j++) {
    if (src[i] == trim_chars[j]) {
      flag = 1;
      (*found)++;
    } else if (j == length2 - 1 && flag == 0)
      *b = 1;
  }
}

// int main(){
//     const char *src = "?!?!?hellohello world my hell hello name is
//     hello!?!?!?!?"; const char *trim_chars = "!?!"; char *trimmed_string =
//     s21_trim(src, trim_chars); printf("%s\n", trimmed_string);
//
//     free(trimmed_string);
//
//     return 0;
// }
