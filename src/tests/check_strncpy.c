#include "unit_tests.h"

START_TEST(s21_strncpy_test) {
  char str1[] = "a1a2a3a4a5a6a7a8";
  char str2[] = "Abcdefghigklm";

  ck_assert_int_eq(s21_strncmp(str1, str2, 1), strncmp(str1, str2, 1));
  ck_assert_int_eq(s21_strncmp(str1, str2, 3), strncmp(str1, str2, 3));
  ck_assert_int_eq(s21_strncmp(str1, str2, 14), strncmp(str1, str2, 14));
}
END_TEST

Suite *s21_strncpy_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strncpy");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strncpy_test);

  suite_add_tcase(s, tc_core);

  return s;
}