#include "unit_tests.h"

START_TEST(s21_strncat_test) {
  char str1[9] = "abcd";
  char str2[9] = "abcd";
  char str3[] = "efg2";
  ck_assert_str_eq(strncat(str1, str3, 0), s21_strncat(str2, str3, 0));
  ck_assert_str_eq(strncat(str1, str3, 1), s21_strncat(str2, str3, 1));
  ck_assert_str_eq(strncat(str1, str3, 2), s21_strncat(str2, str3, 2));
}
END_TEST

Suite *s21_strncat_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strncat");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strncat_test);

  suite_add_tcase(s, tc_core);

  return s;
}