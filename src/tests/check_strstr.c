#include "unit_tests.h"

START_TEST(s21_strstr_test) {
  const char *haystack = "hello world my hello name is";
  const char *needle = "h";
  const char *needle2 = "hello";
  const char *needle3 = " ";
  const char *needle4 = "";
  const char *needle5 = "qw";
  const char *needle6 = "ha";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
  ck_assert_pstr_eq(s21_strstr(haystack, needle2), strstr(haystack, needle2));
  ck_assert_pstr_eq(s21_strstr(haystack, needle3), strstr(haystack, needle3));
  ck_assert_pstr_eq(s21_strstr(needle3, haystack), strstr(needle3, haystack));
  ck_assert_pstr_eq(s21_strstr(haystack, needle4), strstr(haystack, needle4));
  ck_assert_pstr_eq(s21_strstr(needle4, haystack), strstr(needle4, haystack));
  ck_assert_pstr_eq(s21_strstr(needle2, needle), strstr(needle2, needle));
  ck_assert_pstr_eq(s21_strstr(haystack, needle5), strstr(haystack, needle5));
  ck_assert_pstr_eq(s21_strstr(haystack, needle6), strstr(haystack, needle6));
  ck_assert_pstr_eq(s21_strstr(needle, haystack), strstr(needle, haystack));
}
END_TEST

Suite *s21_strstr_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strstr");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strstr_test);

  suite_add_tcase(s, tc_core);

  return s;
}