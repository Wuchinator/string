#include "unit_tests.h"

START_TEST(s21_strlen_test) {
  char str1[] = "Hello, world!";
  char str2[] =
      "213145346758697808-9704=3524-1309876289403-5=6576=432=-31044253=60931 "
      "21";
  char str3[] = "Hello, world!";
  char str4[] = "\0";
  char str6[] = "";
  char str7[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
  char str8[] = "          00000000           ......  ";
  char str9[] = "\n\n\n\n\n\n\n\n\nlololol\n\n\n\n\n";
  char str10[] = "\0\0\0\0\n";
  char str11[] = "";
  char str12[] = "\t\t";
  char str13[] = "\0test";
  ck_assert_int_eq(strlen(str1), s21_strlen(str1));
  ck_assert_int_eq(strlen(str2), s21_strlen(str2));
  ck_assert_int_eq(strlen(str3), s21_strlen(str3));
  ck_assert_int_eq(strlen(str4), s21_strlen(str4));
  ck_assert_int_eq(strlen(str6), s21_strlen(str6));
  ck_assert_int_eq(strlen(str7), s21_strlen(str7));
  ck_assert_int_eq(strlen(str8), s21_strlen(str8));
  ck_assert_int_eq(strlen(str9), s21_strlen(str9));
  ck_assert_int_eq(strlen(str10), s21_strlen(str10));
  ck_assert_int_eq(strlen(str11), s21_strlen(str11));
  ck_assert_int_eq(strlen(str12), s21_strlen(str12));
  ck_assert_int_eq(strlen(str13), s21_strlen(str13));
}
END_TEST

Suite *s21_strlen_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_strlen");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_strlen_test);

  suite_add_tcase(s, tc_core);

  return s;
}