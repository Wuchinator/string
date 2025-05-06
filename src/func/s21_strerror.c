#include "s21_strerror.h"

char* s21_strerror(int errnum) {
  const char* messages[MAX_ERROR_NUM] = {ERROR_MESSAGES};
  static char buffer[60];
  char* result = buffer;

  if (errnum >= 0 && errnum < MAX_ERROR_NUM) {
    s21_sprintf(buffer, "%s", messages[errnum]);
  } else {
    s21_sprintf(buffer, "%s %d", UNKNOWN_ERROR, errnum);
  }

  return result;
}