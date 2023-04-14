#include <check.h>
#include <stdlib.h>
#include <time.h>
#include "../src/Modele/aquarium.h"

START_TEST(test_init_aquarium) {
    aquarium *a = init_aquarium(100, 200, 10, 5);
    ck_assert_int_eq(a->width, 100);
    ck_assert_int_eq(a->height, 200);
    ck_assert_int_eq(a->nb_fish, 10);
    ck_assert_int_eq(a->nb_view, 5);
}
END_TEST

START_TEST(test_init_aquarium_from_file) {
    aquarium *a = init_aquarium_from_file("testaquarium.txt");
    ck_assert_int_eq(a->width, 1000);
    ck_assert_int_eq(a->height, 1000);
    ck_assert_int_eq(a->nb_fish, 0);
    ck_assert_int_eq(a->nb_view, 4);
}
END_TEST

START_TEST(test_add_fish) {
    aquarium *a = init_aquarium(100, 200, 0, 0);
    fish *f1 = init_fish("Nemo", 0, 0, 1, "RandomPointWay");
    add_fish(a, f1);
    ck_assert_int_eq(a->nb_fish, 1);
    ck_assert_str_eq(a->fishes[0]->name, "Nemo");
    ck_assert_int_eq(a->fishes[0]->x, 0);
    ck_assert_int_eq(a->fishes[0]->y, 0);
    ck_assert_int_eq(a->fishes[0]->speed, 1);
    fish *f2 = init_fish("Dory", 10, 10, 2, "RandomPointWay");
    add_fish(a, f2);
    ck_assert_int_eq(a->nb_fish, 2);
    ck_assert_str_eq(a->fishes[0]->name, "Nemo");
    ck_assert_str_eq(a->fishes[1]->name, "Dory");

}
END_TEST

START_TEST(test_delete_fish) {
    aquarium *a = init_aquarium(100, 200, 0, 0);
    fish *f1 = init_fish("Nemo", 0, 0, 1, "RandomPointWay");
    add_fish(a, f1);
    fish *f2 = init_fish("Dory", 10, 10, 2, "RandomPointWay");
    add_fish(a, f2);
    delete_fish(a, f1);
    ck_assert_int_eq(a->nb_fish, 1);
    ck_assert_str_eq(a->fishes[0]->name, "Dory");
    ck_assert_int_eq(a->fishes[0]->x, 10);
    ck_assert_int_eq(a->fishes[0]->y, 10);
    ck_assert_int_eq(a->fishes[0]->speed, 2);
    delete_fish(a, f2);
    ck_assert_int_eq(a->nb_fish, 0);
}
END_TEST

START_TEST(test_move_fishes) {
    aquarium *a = init_aquarium(100, 200, 0, 0);
    fish *f1 = init_fish("Nemo", 0, 0, 5, "RandomPointWay");
    add_fish(a, f1);
    fish *f2 = init_fish("Dory", 10, 10, 7, "RandomPointWay");
    add_fish(a, f2);
    fish *f3 = init_fish("Marlin", 20, 20, 3, "RandomPointWay");
    add_fish(a, f3);
    move_fishes(a);
    move_fishes(a);
    int moved = 0;
    if (a->fishes[0]->x   != 0  && a->fishes[0]->y != 0) {moved++;}
    if (a->fishes[1]->x   != 10  && a->fishes[1]->y != 10) {moved++;}
    if (a->fishes[2]->x   != 20  && a->fishes[2]->y != 20) {moved++;}

    ck_assert_int_ge(moved, 1);
}
END_TEST

START_TEST(test_add_view_id) {
    aquarium *a = init_aquarium(1000, 2000, 0, 0);
    view *v1 = init_view(1, 50, 50, 200, 200);
    view *v2 = init_view(2, 50, 50, 200, 200);
    add_view(a, v1);
    ck_assert_int_eq(a->nb_view, 1);
    add_view(a, v2);
    ck_assert_int_eq(a->nb_view, 2);

    view *v3 = init_view(1, 50, 50, 200, 200);
    add_view(a, v3);
    ck_assert_int_eq(a->nb_view, 2);

}
END_TEST

START_TEST(test__add_view__position) {
    aquarium *a = init_aquarium(100, 200, 0, 0);
    view *v1 = init_view(1, 50, 50, 200, 200);
    add_view(a, v1);
    ck_assert_int_eq(a->nb_view, 0);
}
END_TEST

START_TEST(test__delete_view) {
    aquarium *a = init_aquarium(100, 200, 0, 3);
    ck_assert_int_eq(a->nb_view, 3);
    view *v1 = init_view(1, 50, 50, 200, 200);
    add_view(a, v1);
    ck_assert_int_eq(a->nb_view, 3);
    delete_view(a, v1);
    ck_assert_int_eq(a->nb_view, 2);
}
END_TEST


int main(void)
{
    Suite *s;
    TCase *tc1, *tc2, *tc3, *tc4, *tc5, *tc6, *tc7, *tc8;
    SRunner *sr;

    s = suite_create("Suite de test pour le fichier aquarium.c");

    // Test case for init_aquarium
    tc1 = tcase_create("Fonction init_aquarium");
    tcase_add_test(tc1, test_init_aquarium);
    suite_add_tcase(s, tc1);

    // Test case for init_aquarium_from_file
    tc2 = tcase_create("Fonction init_aquarium_from_file");
    tcase_add_test(tc2, test_init_aquarium_from_file);
    suite_add_tcase(s, tc2);

    // Test case for add_fish
    tc3 = tcase_create("Fonction add_fish");
    tcase_add_test(tc3, test_add_fish);
    suite_add_tcase(s, tc3);

    // Test case for delete_fish
    tc4 = tcase_create("Fonction delete_fish");
    tcase_add_test(tc4, test_delete_fish);
    suite_add_tcase(s, tc4);

    // Test case for move_fishes
    tc5 = tcase_create("Fonction move_fishes");
    tcase_add_test(tc5, test_move_fishes);
    suite_add_tcase(s, tc5);

    // Test case for add_view_id
    tc6 = tcase_create("Fonction add_view");
    tcase_add_test(tc6, test_add_view_id);
    suite_add_tcase(s, tc6);

    // Test case for add_view_position
    tc7 = tcase_create("Fonction add_view");
    tcase_add_test(tc7, test__add_view__position);
    suite_add_tcase(s, tc7);

    // Test case for delete_view
    tc8 = tcase_create("Fonction delete_view");
    tcase_add_test(tc8, test__delete_view);
    suite_add_tcase(s, tc8);


    sr = srunner_create(s);
    srunner_run_all(sr, CK_VERBOSE);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}