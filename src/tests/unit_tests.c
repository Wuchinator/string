#include "unit_tests.h"

int main() {
  int all = ALL_SUITES;
  int fail = 0;
  int success = 0;
  run_suite(s21_memchr_suite(), &fail);
  run_suite(s21_memcmp_suite(), &fail);
  run_suite(s21_memcpy_suite(), &fail);
  run_suite(s21_memset_suite(), &fail);
  run_suite(s21_insert_suite(), &fail);
  run_suite(s21_sscanf_suite(), &fail);
  run_suite(s21_strchr_suite(), &fail);
  run_suite(s21_strcspn_suite(), &fail);
  run_suite(s21_strerror_suite(), &fail);
  run_suite(s21_strlen_suite(), &fail);
  run_suite(s21_strncat_suite(), &fail);
  run_suite(s21_strncmp_suite(), &fail);
  run_suite(s21_strncpy_suite(), &fail);
  run_suite(s21_strpbrk_suite(), &fail);
  run_suite(s21_strrchr_suite(), &fail);
  run_suite(s21_strstr_suite(), &fail);
  run_suite(s21_strtok_suite(), &fail);
  run_suite(s21_tolower_suite(), &fail);
  run_suite(s21_toupper_suite(), &fail);
  run_suite(s21_trim_suite(), &fail);
  run_suite(s21_sprintf_suite(), &fail);
  success = all - fail;
  printf("ALL:%d\nSUCCESS:%d\nFAILED:%d\n", all, success, fail);
  return (fail) ? EXIT_FAILURE : EXIT_SUCCESS;
}

void run_suite(Suite* s, int* fail) {
  SRunner* runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  *fail += srunner_ntests_failed(runner);
  srunner_free(runner);
}