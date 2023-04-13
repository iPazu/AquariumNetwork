#include <check.h>
#include "../src/Modele/fish.h"

/**
 * @brief Test the init_fish function
 */
START_TEST(test_init_fish)
{
    fish *f = init_fish("Nemo", 0, 0, 1, "RandomPointWay");
    ck_assert_str_eq(f->name, "Nemo");
    ck_assert_int_eq(f->x, 0);
    ck_assert_int_eq(f->y, 0);
    ck_assert_int_eq(f->speed, 1);
}
END_TEST

/**
 * @brief Test the move_fish function
 */
START_TEST(test_move_fish)
{
    fish *f = init_fish("Nemo", 0, 0, 1, "RandomPointWay");
    move_fish(f, 10, 10);
    move_fish(f, 10, 10);
    move_fish(f, 10, 10);
    move_fish(f, 10, 10);
    move_fish(f, 10, 10);
    move_fish(f, 10, 10);
    ck_assert_int_ge(f->x, 0);
    ck_assert_int_le(f->x, 10);
    ck_assert_int_ge(f->y, 0);
    ck_assert_int_le(f->y, 10);
}

int main(void)
{
    Suite *s;
    TCase *tc1, *tc2;
    SRunner *sr;

    s = suite_create("Suite de test pour le fichier fish.c");

    // Cas de test pour la fonction init_fish
    tc1 = tcase_create("Fonction init_fish");
    tcase_add_test(tc1, test_init_fish);
    suite_add_tcase(s, tc1);
    // Cas de test pour la fonction move_fish
    tc2 = tcase_create("Fonction move_fish");
    tcase_add_test(tc2, test_move_fish);
    suite_add_tcase(s, tc2);


    sr = srunner_create(s);
    srunner_run_all(sr, CK_VERBOSE);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}