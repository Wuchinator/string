#include "unit_tests.h"

START_TEST(s21_strpbrk_test) {
  char s1[] = "Hello, world!";
  char c1[] = "Hello, world!";
  char s2[] = "Hello, world!";
  char c2[] = "!";
  char s3[] = "";
  char c3[] = "He";
  char s4[] = "\0";
  char c4[] = "";
  char s5[] = "";
  char c5[] = "";
  char s6[] = "1234563468382";
  char c6[] = "346838";
  ck_assert_pstr_eq(strpbrk(s1, c1), s21_strpbrk(s1, c1));
  ck_assert_pstr_eq(strpbrk(s2, c2), s21_strpbrk(s2, c2));
  ck_assert_pstr_eq(strpbrk(s3, c3), s21_strpbrk(s3, s3));
  ck_assert_pstr_eq(strpbrk(s4, c4), s21_strpbrk(s4, c4));
  ck_assert_pstr_eq(strpbrk(s5, c2), s21_strpbrk(s5, c5));
  ck_assert_pstr_eq(strpbrk(s6, c6), s21_strpbrk(s6, c6));
}
END_TEST

Suite *s21_strpbrk_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strpbrk");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strpbrk_test);

  suite_add_tcase(s, tc_core);

  return s;
}