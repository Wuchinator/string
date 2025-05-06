#include "unit_tests.h"

START_TEST(s21_sscanf_test) {
  int result = 0, result21 = 0;
  int i = 0, d = 0, x = 0, n = 0, i21 = 0, d21 = 0, x21 = 0, n21 = 0;
  long int ld = 0, ld21 = 0;
  unsigned int u = 0, u21 = 0;
  double lf = 0.0, lf21 = 0.0;
  char s[20], s21[20];
  char c = '\0', c21 = '\0', h = '\0', h21 = '\0';

  // RETURN 0
  result = sscanf("-6.3214E-01", "%1lf%x", &lf, &x);
  result21 = s21_sscanf("-6.3214E-01", "%1lf%x", &lf21, &x21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(x, x21);
  ck_assert_double_eq(lf, lf21);

  result = sscanf("--85254", "%d", &d);
  result21 = s21_sscanf("--85254", "%d", &d21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(d, d21);

  result = sscanf("85254", "%d", &d);
  result21 = s21_sscanf("85254", "%d", &d21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(d, d21);

  result = sscanf("-1", "%u", &u);
  result21 = s21_sscanf("-1", "%u", &u21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(u, u21);

  result = sscanf("4294967298", "%u", &u);
  result21 = s21_sscanf("4294967298", "%u", &u21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(u, u21);

  result = sscanf("7ff", "%x", &d);
  result21 = s21_sscanf("7ff", "%x", &d21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(d, d21);

  result = sscanf("213.412", "%3lf.%d", &lf, &d);
  result21 = s21_sscanf("213.412", "%3lf.%d", &lf21, &d21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(d, d21);
  ck_assert_double_eq(lf, lf21);

  result = sscanf("-6.3214E-01", "%7lfE%d", &lf, &d);
  result21 = s21_sscanf("-6.3214E-01", "%7lfE%d", &lf21, &d21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(d, d21);
  ck_assert_double_eq(lf, lf21);

  result = sscanf("-6.3214E-01", "%7lf%x%d", &lf, &x, &d);
  result21 = s21_sscanf("-6.3214E-01", "%7lf%x%d", &lf21, &x21, &d21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(d, d21);
  ck_assert_int_eq(x, x21);
  ck_assert_double_eq(lf, lf21);

  result = sscanf("--24313", "%ld", &ld);
  result21 = s21_sscanf("--24313", "%ld", &ld21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(ld, ld21);

  result = sscanf("--24313", "%u", &u);
  result21 = s21_sscanf("--24313", "%u", &u21);
  ck_assert_int_eq(result, result21);
  ck_assert_uint_eq(u, u21);

  result = sscanf("This is just a 2nd test", "This is just a%d", &d);
  result21 = s21_sscanf("This is just a 2nd test", "This is just a%d", &d21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(d, d21);

  // несмотря на * n должна содержать 17
  result = sscanf("This is just a\t 2nd test", "This is just a%*d%n", &n);
  result21 =
      s21_sscanf("This is just a\t 2nd test", "This is just a%*d%n", &n21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(d, d21);
  ck_assert_int_eq(n, n21);

  //  т.к. присутствует префикс 0x результат будет 2047
  result = sscanf("0x7ff", "%i %n", &i, &n);
  result21 = s21_sscanf("0x7ff", "%i %n", &i21, &n21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(i, i21);
  ck_assert_int_eq(n, n21);

  result = sscanf("7ff", "%x%n", &d, &n);
  result21 = s21_sscanf("7ff", "%x%n", &d21, &n21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(d, d21);
  ck_assert_int_eq(n, n21);

  // lasciate ogni speranza voi ch'entrate
  result = sscanf("62", "%d%n", &d, &n);
  result21 = s21_sscanf("62", "%d%n", &d21, &n21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(d, d21);
  ck_assert_int_eq(n, n21);

  result = sscanf("6.2", "%lf%n", &lf, &n);
  result21 = s21_sscanf("6.2", "%lf%n", &lf21, &n21);
  ck_assert_int_eq(result, result21);
  ck_assert_double_eq(lf, lf21);
  ck_assert_int_eq(n, n21);

  result = sscanf("Hello World 123", "%s %lf %c", s, &lf, &c);
  result21 = s21_sscanf("Hello World 123", "%s %lf %c", s21, &lf21, &c21);
  ck_assert_int_eq(result, result21);
  ck_assert_str_eq(s, s21);
  ck_assert_double_eq(lf, lf21);
  ck_assert_int_eq(c, c21);

  result = sscanf("%%", "%%%c%c", &c, &h);
  result21 = s21_sscanf("%%", "%%%c%c", &c21, &h21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(c, c21);
  ck_assert_int_eq(h, h21);

  result = sscanf("%%", "%c%c", &c, &h);
  result21 = s21_sscanf("%%", "%c%c", &c21, &h21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(c, c21);
  ck_assert_int_eq(h, h21);

  // RETURN 0
  result = sscanf("24313", "%ld %%", &ld);
  result21 = sscanf("24313", "%ld %%", &ld21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(ld, ld21);

  result = sscanf("-85254", "%1d", &d);
  result21 = s21_sscanf("-85254", "%1d", &d21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(ld, ld21);

  result = sscanf("+85254", "%1d", &d);
  result21 = s21_sscanf("+85254", "%1d", &d21);
  ck_assert_int_eq(result, result21);
  ck_assert_int_eq(ld, ld21);
}
END_TEST

Suite *s21_sscanf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sscanf");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_sscanf_test);

  suite_add_tcase(s, tc_core);

  return s;
}
