#include "unit_tests.h"

START_TEST(s21_strchr_test) {
  char str1[] = "abcdefg";
  int c = 'a';
  int c1 = '8';
  int c2 = 'g';

  ck_assert_ptr_eq(s21_strchr(str1, c), strchr(str1, c));
  ck_assert_ptr_eq(s21_strchr(str1, c1), strchr(str1, c1));
  ck_assert_ptr_eq(s21_strchr(str1, c2), strchr(str1, c2));
}
END_TEST

Suite *s21_strchr_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strchr");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strchr_test);

  suite_add_tcase(s, tc_core);

  return s;
}