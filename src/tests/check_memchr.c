#include "unit_tests.h"

START_TEST(test1) {
  const char *s = "sommmmetesstp";
  const char *empty = "";
  ck_assert_ptr_eq(memchr(s, 's', strlen(s)), s21_memchr(s, 's', strlen(s)));
  ck_assert_ptr_eq(memchr(s, 'o', strlen(s)), s21_memchr(s, 'o', strlen(s)));
  ck_assert_ptr_eq(memchr(s, 'A', strlen(s)), s21_memchr(s, 'A', strlen(s)));
  ck_assert_ptr_eq(memchr(empty, 'A', strlen(s)),
                   s21_memchr(empty, 'A', strlen(s)));
}
END_TEST

Suite *s21_memchr_suite() {
  Suite *suite = suite_create("s21_memchr");
  TCase *tcase_core = tcase_create("memchr");

  tcase_add_test(tcase_core, test1);
  suite_add_tcase(suite, tcase_core);

  return suite;
}