#include "unit_tests.h"

START_TEST(s21_strcspn_test) {
  char s1[] = "0123456789";
  char c1[] = "0123";
  char s2[] = "w";
  char c2[] = "world";
  char s3[] = "";
  char c3[] = "Hello, world!";
  char s4[] = "Hello, world!";
  char c4[] = "";
  char s5[] = "6";
  char c5[] = "67";
  char s6[] = "69917020";
  char c6[] = "69917020";
  char s7[] = "";
  char c7[] = "";
  char s8[] = "69917020";
  char c8[] = "6991702H";
  ck_assert_int_eq(strcspn(s1, c1), s21_strcspn(s1, c1));
  ck_assert_int_eq(strcspn(s2, c2), s21_strcspn(s2, c2));
  ck_assert_int_eq(strcspn(s3, c3), s21_strcspn(s3, c3));
  ck_assert_int_eq(strcspn(s4, c4), s21_strcspn(s4, c4));
  ck_assert_int_eq(strcspn(s5, c5), s21_strcspn(s5, c5));
  ck_assert_int_eq(strcspn(s6, c6), s21_strcspn(s6, c6));
  ck_assert_int_eq(strcspn(s7, c7), s21_strcspn(s7, c7));
  ck_assert_int_eq(strcspn(s8, c8), s21_strcspn(s8, c8));
}
END_TEST

Suite *s21_strcspn_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strcspn");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strcspn_test);

  suite_add_tcase(s, tc_core);

  return s;
}