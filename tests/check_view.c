#include <check.h>
#include <stdlib.h>
#include <time.h>
#include "../src/Modele/view.h"

START_TEST(test__init_view) {
    view *v1 = init_view(1, 0, 0, 100, 200);
    ck_assert_int_eq(v1->id, 1);
    ck_assert_int_eq(v1->x, 0);
    ck_assert_int_eq(v1->y, 0);
    ck_assert_int_eq(v1->width, 100);
    ck_assert_int_eq(v1->height, 200);
    view *v2 = init_view(2, -10, 10, 100, 200);
    ck_assert_ptr_null(v2);
    view *v3 = init_view(3, 10, -10, 100, 200);
    ck_assert_ptr_null(v3);
    view *v4 = init_view(4, 10, 10, -100, 200);
    ck_assert_ptr_null(v4);
    view *v5 = init_view(5, 10, 10, 100, -200);
    ck_assert_ptr_null(v5);
}
END_TEST


int main(void)
{
    Suite *s;
    TCase *tc1;
    SRunner *sr;

    s = suite_create("Suite de test pour le fichier view.c");

    // Test case for init_view
    tc1 = tcase_create("Fonction init_view");
    tcase_add_test(tc1, test__init_view);
    suite_add_tcase(s, tc1);




    sr = srunner_create(s);
    srunner_run_all(sr, CK_VERBOSE);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}