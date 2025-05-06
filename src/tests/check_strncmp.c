#include "unit_tests.h"

START_TEST(s21_strncmp_test) {
  char str1[] = "abcg";
  char str2[] = "abch";
  int my = s21_strncmp(str1, str2, 3);
  int orig = strncmp(str1, str2, 3);
  int my1 = s21_strncmp(str1, str2, 2);
  int orig1 = strncmp(str1, str2, 2);
  int my2 = s21_strncmp(str1, str2, 4);
  int orig2 = strncmp(str1, str2, 4);

  ck_assert_int_eq(my, orig);
  ck_assert_int_eq(my1, orig1);
  ck_assert_int_eq(my2, orig2);
}
END_TEST

Suite *s21_strncmp_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strncmp");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strncmp_test);

  suite_add_tcase(s, tc_core);

  return s;
}