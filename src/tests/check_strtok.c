#include "unit_tests.h"

START_TEST(s21_strtok_test) {
  char str[] = "hello world my hello name is";
  const char delimiters1[] = "a";
  const char delimiters2[] = "hello";
  const char delimiters3[] = " ";
  const char delimiters4[] = "";
  const char delimiters5[] = "qw";
  const char delimiters6[] = "ha";

  ck_assert_pstr_eq(s21_strtok(str, delimiters1), strtok(str, delimiters1));
  ck_assert_pstr_eq(s21_strtok(str, delimiters2), strtok(str, delimiters2));
  ck_assert_pstr_eq(s21_strtok(str, delimiters3), strtok(str, delimiters3));
  ck_assert_pstr_eq(s21_strtok(str, delimiters4), strtok(str, delimiters4));
  ck_assert_pstr_eq(s21_strtok(str, delimiters5), strtok(str, delimiters5));
  ck_assert_pstr_eq(s21_strtok(str, delimiters6), strtok(str, delimiters6));
}
END_TEST

Suite *s21_strtok_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strtok");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strtok_test);

  suite_add_tcase(s, tc_core);

  return s;
}