#include "unit_tests.h"

START_TEST(s21_sprintf_test) {
  char buffer[100];
  char buffer21[100];
  int a = 392;
  unsigned int b = 7235;
  unsigned int c = 93921;
  unsigned int d = 0x7fa;
  float e = 3.4563745;
  float f = 3.1234e+3;
  char h = 'a';
  char str[] = "Hello World";

  sprintf(buffer, "%%d или %%i: %d\n", a);
  s21_sprintf(buffer21, "%%d или %%i: %d\n", a);
  ck_assert_str_eq(buffer, buffer21);

  sprintf(buffer, "%%u: %u\n", b);
  s21_sprintf(buffer21, "%%u: %u\n", b);
  ck_assert_str_eq(buffer, buffer21);

  sprintf(buffer, "%%o: %o\n", c);
  s21_sprintf(buffer21, "%%o: %o\n", c);
  ck_assert_str_eq(buffer, buffer21);

  sprintf(buffer, "%%x: %x\n", d);
  s21_sprintf(buffer21, "%%x: %x\n", d);
  ck_assert_str_eq(buffer, buffer21);

  sprintf(buffer, "%%X: %X\n", d);
  s21_sprintf(buffer21, "%%X: %X\n", d);
  ck_assert_str_eq(buffer, buffer21);

  sprintf(buffer, "%%f или %%F: %f\n", e);
  s21_sprintf(buffer21, "%%f или %%F: %f\n", e);
  ck_assert_str_eq(buffer, buffer21);

  sprintf(buffer, "%%e: %e\n", f);
  s21_sprintf(buffer21, "%%e: %e\n", f);
  ck_assert_str_eq(buffer, buffer21);

  sprintf(buffer, "%%E: %E\n", f);
  s21_sprintf(buffer21, "%%E: %E\n", f);
  ck_assert_str_eq(buffer, buffer21);

  sprintf(buffer, "%%c: %c\n", h);
  s21_sprintf(buffer21, "%%c: %c\n", h);
  ck_assert_str_eq(buffer, buffer21);

  sprintf(buffer, "%%s: %s\n", str);
  s21_sprintf(buffer21, "%%s: %s\n", str);
  ck_assert_str_eq(buffer, buffer21);

  sprintf(buffer, "%%%%: %%\n");
  s21_sprintf(buffer21, "%%%%: %%\n");
  ck_assert_str_eq(buffer, buffer21);
}
END_TEST

Suite *s21_sprintf_suite() {
  Suite *suite = suite_create("s21_sprintf");
  TCase *tcase_core = tcase_create("sprintf");

  tcase_add_test(tcase_core, s21_sprintf_test);
  suite_add_tcase(suite, tcase_core);

  return suite;
}