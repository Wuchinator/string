#include "unit_tests.h"

START_TEST(s21_strrchr_test) {
  char s1[] = "Hello, world!";
  int ch1 = 'h';
  char s2[] = "Hello, world!";
  int ch2 = '\0';
  char s3[] = "Hello, world!";
  int ch3 = ',';
  char s4[] = "Hello, world!";
  int ch4 = 33;
  char s5[] = "Hello, My friends!";
  int ch5 = 'M';
  char s6[] = "Hello, world!";
  int ch6 = 'w';
  char s7[] = "Hello, world!";
  int ch7 = '0';
  char s8[] = "Hello, world!";
  int ch8 = 'm';
  ck_assert_pstr_eq(strrchr(s1, ch1), s21_strrchr(s1, ch1));
  ck_assert_pstr_eq(strrchr(s2, ch2), s21_strrchr(s2, ch2));
  ck_assert_pstr_eq(strrchr(s3, ch3), s21_strrchr(s3, ch3));
  ck_assert_pstr_eq(strrchr(s4, ch4), s21_strrchr(s4, ch4));
  ck_assert_pstr_eq(strrchr(s5, ch5), s21_strrchr(s5, ch5));
  ck_assert_pstr_eq(strrchr(s6, ch6), s21_strrchr(s6, ch6));
  ck_assert_pstr_eq(strrchr(s7, ch7), s21_strrchr(s7, ch7));
  ck_assert_pstr_eq(strrchr(s8, ch8), s21_strrchr(s8, ch8));
}
END_TEST

Suite *s21_strrchr_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strrchr");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strrchr_test);

  suite_add_tcase(s, tc_core);

  return s;
}