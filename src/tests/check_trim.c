#include "unit_tests.h"

START_TEST(s21_trim_test) {
  const char *src = "hellohello world my hell hello name is hello";
  const char *src1 =
      "!?!?!?hellohello world my !?!hell hello name is hello!?!?!?!";
  const char *src2 =
      "?!?!?hellohello world my hell hello name is hello!?!?!?!?";
  const char *trim_chars1 = ".";
  const char *trim_chars2 = "he";
  const char *trim_chars3 = "hello";
  const char *trim_chars4 = "!";
  const char *trim_chars5 = "!?";
  const char *trim_chars6 = "!?!";
  const char *trim_chars7 = "";
  const char *trim_chars8 = " ";

  char *r1 = s21_trim(src, trim_chars1);
  char *r2 = s21_trim(src, trim_chars2);
  char *r3 = s21_trim(src, trim_chars3);
  char *r4 = s21_trim(src, trim_chars7);
  char *r5 = s21_trim(src, trim_chars8);
  char *r6 = s21_trim(src1, trim_chars4);
  char *r7 = s21_trim(src1, trim_chars5);
  char *r8 = s21_trim(src1, trim_chars6);
  char *r9 = s21_trim(src2, trim_chars4);
  char *r10 = s21_trim(src2, trim_chars5);
  char *r11 = s21_trim(src2, trim_chars6);

  ck_assert_str_eq(r1, "hellohello world my hell hello name is hello");
  ck_assert_str_eq(r2, "llohello world my hell hello name is hello");
  ck_assert_str_eq(r3, " world my hell hello name is ");
  ck_assert_str_eq(r4, "hellohello world my hell hello name is hello");
  ck_assert_str_eq(r5, "hellohello world my hell hello name is hello");
  ck_assert_str_eq(
      r6, "?!?!?hellohello world my !?!hell hello name is hello!?!?!?");
  ck_assert_str_eq(r7, "hellohello world my !?!hell hello name is hello");
  ck_assert_str_eq(r8, "hellohello world my !?!hell hello name is hello");
  ck_assert_str_eq(r9,
                   "?!?!?hellohello world my hell hello name is hello!?!?!?!?");
  ck_assert_str_eq(r10, "hellohello world my hell hello name is hello");
  ck_assert_str_eq(r11, "hellohello world my hell hello name is hello");

  if (r1 != NULL) free(r1);
  if (r2 != NULL) free(r2);
  if (r3 != NULL) free(r3);
  if (r4 != NULL) free(r4);
  if (r5 != NULL) free(r5);
  if (r6 != NULL) free(r6);
  if (r7 != NULL) free(r7);
  if (r8 != NULL) free(r8);
  if (r9 != NULL) free(r9);
  if (r10 != NULL) free(r10);
  if (r11 != NULL) free(r11);
}
END_TEST

Suite *s21_trim_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_trim");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_trim_test);

  suite_add_tcase(s, tc_core);

  return s;
}