#include "unit_tests.h"

START_TEST(s21_insert_test) {
  char src[] = "hello";
  char str[] = "hello";
  int n1 = 5;
  int n2 = 4;
  int n3 = 3;
  ck_assert_str_eq(s21_insert(src, str, n1), "hellohello");
  ck_assert_str_eq(s21_insert(src, str, n2), "hellhelloo");
  ck_assert_str_eq(s21_insert(src, str, n3), "helhellolo");
}
END_TEST

Suite *s21_insert_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_insert");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_insert_test);

  suite_add_tcase(s, tc_core);

  return s;
}