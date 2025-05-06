#include "unit_tests.h"

START_TEST(test1) {
  char src[] = "синаааббоныы";
  char dest[] = "888899433";
  ck_assert(memcmp(dest, src, 7) == s21_memcmp(dest, src, 7));
}
END_TEST

START_TEST(test2) {
  char src[] = "999999999";
  char dest[] = "999999999";
  ck_assert(memcmp(src, dest, 7) == s21_memcmp(src, dest, 7));
}
END_TEST

Suite *s21_memcmp_suite() {
  Suite *suite = suite_create("s21_memcmp");
  TCase *tcase_core = tcase_create("memcmp");

  tcase_add_test(tcase_core, test1);
  tcase_add_test(tcase_core, test2);
  suite_add_tcase(suite, tcase_core);

  return suite;
}