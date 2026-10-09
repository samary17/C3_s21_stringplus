#include <check.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"

/* ================= strlen ================= */

START_TEST(test_strlen_basic) {
  ck_assert_int_eq(s21_strlen("hello"), strlen("hello"));
  ck_assert_int_eq(s21_strlen(""), strlen(""));
}
END_TEST

/* ================= memcpy ================= */

START_TEST(test_memcpy_basic) {
  char a[20] = {0};
  char b[20] = {0};
  s21_memcpy(a, "hello", 6);
  memcpy(b, "hello", 6);
  ck_assert_str_eq(a, b);
}
END_TEST

/* ================= memset ================= */

START_TEST(test_memset_basic) {
  char a[10];
  char b[10];
  s21_memset(a, 'A', 5);
  memset(b, 'A', 5);
  ck_assert_mem_eq(a, b, 5);
}
END_TEST

/* ================= memcmp ================= */

START_TEST(test_memcmp_basic) {
  ck_assert_int_eq(s21_memcmp("abc", "abc", 3), memcmp("abc", "abc", 3));
  ck_assert_int_eq(s21_memcmp("abc", "abd", 3), memcmp("abc", "abd", 3));
}
END_TEST

/* ================= strchr ================= */

START_TEST(test_strchr_basic) {
  ck_assert_ptr_eq(s21_strchr("hello", 'e'), strchr("hello", 'e'));
  ck_assert_ptr_eq(s21_strchr("hello", 'x'), strchr("hello", 'x'));
}
END_TEST

/* ================= strrchr ================= */

START_TEST(test_strrchr_basic) {
  ck_assert_ptr_eq(s21_strrchr("hello", 'l'), strrchr("hello", 'l'));
}
END_TEST

/* ================= strncmp ================= */

START_TEST(test_strncmp_basic) {
  ck_assert_int_eq(s21_strncmp("abc", "abc", 3), strncmp("abc", "abc", 3));
  ck_assert_int_eq(s21_strncmp("abc", "abd", 3), strncmp("abc", "abd", 3));
}
END_TEST

/* ================= strncpy ================= */

START_TEST(test_strncpy_basic) {
  char a[10], b[10];
  s21_strncpy(a, "hi", 5);
  strncpy(b, "hi", 5);
  ck_assert_mem_eq(a, b, 5);
}
END_TEST

/* ================= strncat ================= */

START_TEST(test_strncat_basic) {
  char a[20] = "hi ";
  char b[20] = "hi ";
  s21_strncat(a, "there", 3);
  strncat(b, "there", 3);
  ck_assert_str_eq(a, b);
}
END_TEST

/* ================= strcspn ================= */

START_TEST(test_strcspn_basic) {
  ck_assert_int_eq(s21_strcspn("hello", "l"), strcspn("hello", "l"));
}
END_TEST

/* ================= strpbrk ================= */

START_TEST(test_strpbrk_basic) {
  ck_assert_ptr_eq(s21_strpbrk("hello", "xol"), strpbrk("hello", "xol"));
}
END_TEST

/* ================= strstr ================= */

START_TEST(test_strstr_basic) {
  ck_assert_ptr_eq(s21_strstr("hello world", "world"),
                   strstr("hello world", "world"));
}
END_TEST

/* ================= strtok ================= */

START_TEST(test_strtok_basic) {
  char a1[50] = "a,b,c";
  char a2[50] = "a,b,c";

  char *t1 = s21_strtok(a1, ",");
  char *t2 = strtok(a2, ",");

  while (t1 && t2) {
    ck_assert_str_eq(t1, t2);
    t1 = s21_strtok(NULL, ",");
    t2 = strtok(NULL, ",");
  }
}
END_TEST

/* ================= strerror ================= */

START_TEST(test_strerror_basic) {
  ck_assert_str_eq(s21_strerror(0), strerror(0));
  ck_assert_str_eq(s21_strerror(1), strerror(1));
}
END_TEST

/* ================= sprintf ================= */

START_TEST(test_sprintf_basic) {
  char a[200];
  char b[200];

  s21_sprintf(a, "Hello %d %s %.2f", 10, "world", 3.14);
  sprintf(b, "Hello %d %s %.2f", 10, "world", 3.14);

  ck_assert_str_eq(a, b);
}
END_TEST

/* ================= SUITE ================= */

Suite *string_suite(void) {
  Suite *s = suite_create("s21_string");

  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_strlen_basic);
  tcase_add_test(tc, test_memcpy_basic);
  tcase_add_test(tc, test_memset_basic);
  tcase_add_test(tc, test_memcmp_basic);
  tcase_add_test(tc, test_strchr_basic);
  tcase_add_test(tc, test_strrchr_basic);
  tcase_add_test(tc, test_strncmp_basic);
  tcase_add_test(tc, test_strncpy_basic);
  tcase_add_test(tc, test_strncat_basic);
  tcase_add_test(tc, test_strcspn_basic);
  tcase_add_test(tc, test_strpbrk_basic);
  tcase_add_test(tc, test_strstr_basic);
  tcase_add_test(tc, test_strtok_basic);
  tcase_add_test(tc, test_strerror_basic);
  tcase_add_test(tc, test_sprintf_basic);

  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  Suite *s = string_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return failed == 0 ? 0 : 1;
}
