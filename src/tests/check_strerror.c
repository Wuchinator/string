#include "unit_tests.h"

START_TEST(s21_strerror_test) {
  for (int i = 0; i < 135; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

Suite *s21_strerror_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strerror");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strerror_test);

  suite_add_tcase(s, tc_core);

  return s;
}