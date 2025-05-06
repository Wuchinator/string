#include "unit_tests.h"

START_TEST(test1) {
  char *dest1 = calloc(100, sizeof(char));
  char *dest2 = calloc(100, sizeof(char));
  for (s21_size_t i = 0; i < 100; i++) {
    char c = (char)((i * 7) % 127);
    dest1 = memset(dest1, c, i);
    dest2 = s21_memset(dest2, c, i);
    ck_assert_str_eq(dest1, dest2);
  }
  dest1 = memset(dest1, '\0', 15);
  dest2 = s21_memset(dest2, '\0', 15);
  ck_assert_str_eq(dest1, dest2);
  free(dest1);
  free(dest2);
}
END_TEST

Suite *s21_memset_suite() {
  Suite *suite = suite_create("s21_memset");
  TCase *tcase_core = tcase_create("memset");

  tcase_add_test(tcase_core, test1);
  suite_add_tcase(suite, tcase_core);

  return suite;
}