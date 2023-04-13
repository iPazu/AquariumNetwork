#include <check.h>
#include <stdlib.h>
#include <time.h>
#include "../src/Modele/move.h"

START_TEST(test_RandomPointWay) {
    fish *f = init_fish("Nemo", 0, 0, 1, "RandomPointWay");
    RandomPointWay(f, 10, 10);
    ck_assert_int_ge(f->x, 0);
    ck_assert_int_le(f->x, 10);
    ck_assert_int_ge(f->y, 0);
    ck_assert_int_le(f->y, 10);
}
END_TEST

START_TEST(test_HorizontalWay) {
    srand(time(NULL));
    fish *f = init_fish("Nemo", 0, 0, 6, "HorizontalWay");
    HorizontalWay(f, 10, 10);
    ck_assert_int_ge(f->x, 0);
    ck_assert_int_le(f->x, 10);
    ck_assert_int_eq(f->y, 0);
    HorizontalWay(f, 10, 10);
    ck_assert_int_ge(f->x, 0);
    ck_assert_int_le(f->x, 10);
    ck_assert_int_eq(f->y, 0);
    HorizontalWay(f, 10, 10);
    ck_assert_int_ge(f->x, 0);
    ck_assert_int_le(f->x, 10);
    ck_assert_int_eq(f->y, 0);
}
END_TEST

START_TEST(test_VerticalWay) {
    srand(time(NULL));
    fish *f = init_fish("Nemo", 0, 0, 6, "VerticalWay");
    VerticalWay(f, 10, 10);
    ck_assert_int_eq(f->x, 0);
    ck_assert_int_ge(f->y, 0);
    ck_assert_int_le(f->y, 10);
    VerticalWay(f, 10, 10);
    ck_assert_int_eq(f->x, 0);
    ck_assert_int_ge(f->y, 0);
    ck_assert_int_le(f->y, 10);
    VerticalWay(f, 10, 10);
    ck_assert_int_eq(f->x, 0);
    ck_assert_int_ge(f->y, 0);
    ck_assert_int_le(f->y, 10);
}

int main(void)
{
    Suite *s;
    TCase *tc1, *tc2, *tc3;
    SRunner *sr;

    s = suite_create("Suite de test pour le fichier move.c");

    // Test case for RandomPointWay
    tc1 = tcase_create("Fonction RandomPointWay");
    tcase_add_test(tc1, test_RandomPointWay);
    suite_add_tcase(s, tc1);
    // Test case for HorizontalWay
    tc2 = tcase_create("Fonction HorizontalWay");
    tcase_add_test(tc2, test_HorizontalWay);
    suite_add_tcase(s, tc2);
    // Test case for VerticalWay
    tc3 = tcase_create("Fonction VerticalWay");
    tcase_add_test(tc3, test_VerticalWay);
    suite_add_tcase(s, tc3);



    sr = srunner_create(s);
    srunner_run_all(sr, CK_VERBOSE);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}