#include "unit_tests.h"

START_TEST(test1) {
  char *dest1 = calloc(100, sizeof(char));
  char *dest2 = calloc(100, sizeof(char));
  char *str1 = "AbraCadabra";
  char *str2 = "Hello World";
  char *str3 = "Python sucks";
  for (s21_size_t i = 0; i < 15; i++) {
    dest1 = memcpy(dest1, str1, i);
    dest2 = s21_memcpy(dest2, str1, i);
    ck_assert_str_eq(dest1, dest2);

    dest1 = memcpy(dest1, str2, i);
    dest2 = s21_memcpy(dest2, str2, i);
    ck_assert_str_eq(dest1, dest2);

    dest1 = memcpy(dest1, str3, i);
    dest2 = s21_memcpy(dest2, str3, i);
    ck_assert_str_eq(dest1, dest2);
  }
  free(dest1);
  free(dest2);
}
END_TEST

Suite *s21_memcpy_suite() {
  Suite *suite = suite_create("s21_memcpy");
  TCase *tcase_core = tcase_create("memcpy");

  tcase_add_test(tcase_core, test1);
  suite_add_tcase(suite, tcase_core);

  return suite;
}