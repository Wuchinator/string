#include "unit_tests.h"

START_TEST(s21_toupper_test) {
  char str1[] = "hello world!!!";
  char str2[] = "HeLlo WoRlD!!!";
  char str3[] = "hhhHHHhhh";
  char str4[] = " ";
  char str5[] = "";
  char str6[] = "!@#$%^^&*&*(()__++";
  char *r1 = s21_to_upper(str1);
  ck_assert_str_eq(r1, "HELLO WORLD!!!");
  char *r2 = s21_to_upper(str2);
  ck_assert_str_eq(r2, "HELLO WORLD!!!");
  char *r3 = s21_to_upper(str3);
  ck_assert_str_eq(r3, "HHHHHHHHH");
  char *r4 = s21_to_upper(str4);
  ck_assert_str_eq(r4, " ");
  char *r5 = s21_to_upper(str5);
  ck_assert_str_eq(r5, "");
  char *r6 = s21_to_upper(str6);
  ck_assert_str_eq(r6, "!@#$%^^&*&*(()__++");
  if (r1 != NULL) free(r1);
  if (r2 != NULL) free(r2);
  if (r3 != NULL) free(r3);
  if (r4 != NULL) free(r4);
  if (r5 != NULL) free(r5);
  if (r6 != NULL) free(r6);
}
END_TEST

Suite *s21_toupper_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_toupper");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_toupper_test);

  suite_add_tcase(s, tc_core);

  return s;
}