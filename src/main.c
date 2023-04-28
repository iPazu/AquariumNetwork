#include "Controler/tcp_server.h"
#include "Modele/aquarium.h"
#include "Modele/fish.h"
#include "Controler/input_handler.h"
#include <assert.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t thread;
void *arg;
char *notFound = "-> NOK : commande introuvable\n";
char *valid_command = "-> OK\n";
char *too_arg = "Too many arguments\n";
char *fish_arg = "Fish argument missing\n";
char *aq_arg = "Aquarium argument missing\n";
char *pos_arg = "Position argument missing\n";
char *unexistant_fish = "-> NOK : Poisson inexistant dans l'aquarium\n";
char *view_arg = "View argument missing\n";

void clean() {} // to use in case of dynamic allocation

void get_option(aquarium *a) {
    int size_arg = 100;
    char arg[size_arg];
    if (fgets(arg, size_arg, stdin) != NULL) {
        arg[strcspn(arg, "\n")] = '\0'; // remplace '\n' par '\0'
        char input[100] = "";
        sscanf(arg, "%s", input);

        if (strcmp(input, "status") == 0) {
            get_status(a);
        }
        if (strcmp(input, "addFish") == 0) {
            client_add_fish(a, arg, size_arg);
        }
        if (strcmp(input, "delFish") == 0) {
            client_del_fish(a, arg, size_arg);
        }
        if (strcmp(input, "getFishes") == 0) {
            client_get_fishes(a, arg, size_arg);
        }
        if (strcmp(input, "startFish") == 0) {
            printf("startFish\n");
        }
        if (strcmp(input, "getFishesContinuously") == 0) {
            printf("getFishesContinuously\n");
        }
        if (strcmp(input, "ls") == 0) {
            printf("ls\n");
        }
        if (strcmp(input, "hello") == 0) {
            printf("hello\n");
        }
        if (strcmp(input, "log") == 0) {
            client_quit(a, arg, size_arg);
        }
        if (strcmp(input, "ping") == 0) {
            client_ping(a, arg, size_arg);
        }

    }









//
//    // gestion des arguments
//    char arg[100];
//    int size_arg = 100;
//    int nb_tokens = 0;
//    int total_tokens = 0;
//    const char s[3] = " ,";
//    char *fishname;
//    if (fgets(arg, size_arg, stdin) != NULL) {
//        char *split = strtok(arg, s);
//        // parcours de la liste des arguments
//        while (split != NULL) {
//            nb_tokens++;
//            total_tokens++;
//
//            /*
//              Programme affichage
//            */
//
//            // Get status
//            if (strcmp(split, "status\n") == 0 && nb_tokens == 1) {
//                // s'assurer que la connexion est bien faite
//                printf("-> OK : Connecté au contrôleur, %d  poisson(s) trouvé(s)\n",
//                       a->nb_fish);
//                // return list of fishes
//                for (int i = 0; i < a->nb_fish; i++) {
//                    show_fish(a->fishes[i]);
//                }
//            }
//                // Add a fish
//            else if (strcmp(split, "addFish\n") == 0 && nb_tokens == 1) {
//                printf("%s", fish_arg);
//            } else if (strcmp(split, "addFish") == 0 && nb_tokens == 1) {
//                char *fish_name = strtok(NULL, s);
//                char *at = strtok(NULL, s);
//                char *coords = strtok(NULL, s);
//                char *view = strtok(NULL, s);
//                char *mobility = strtok(NULL, s);
//                printf("%s ", fish_name);
//                printf("%s ", at);
//                printf("%s ", coords);
//                printf("%s ", view);
//                printf("%s\n", mobility);
//                client_add_fish(a, fish_name, 0, 0, 0, 0, "random");
//            }
//
//                // Delete a fish
//            else if (strcmp(split, "delFish\n") == 0 && nb_tokens == 1) {
//                printf("%s", fish_arg);
//
//            } else if (strcmp(split, "delFish") == 0 && nb_tokens == 1) {
//                char *name = strtok(NULL, s);
//                printf("%s", name);
//                // check if fish exists
//                int fish_exists = 0;
//                for (int i = 0; i < a->nb_fish; i++) {
//                    if (strcmp(
//                            name,
//                            a->fishes[i]->name)) { // creation of a table of fish names ?
//                        fish_exists = 1;
//                        delete_fish(a, a->fishes[i]);
//                    }
//                }
//                printf("OK\n");
//                if (fish_exists == 0)
//                    printf("%s", unexistant_fish);
//            }
//                // Get fishes list
//            else if (strcmp(split, "getFishes\n") == 0 && nb_tokens == 1) {
//                printf("list\n");
//                for (int i = 0; i < a->nb_fish; i++) {
//                    show_fish(a->fishes[i]);
//                }
//            }
//                // start a fish
//            else if (strcmp(split, "startFish\n") == 0 && nb_tokens == 1) {
//                printf("%s", fish_arg);
//            } else if (strcmp(split, "startFish") == 0 && nb_tokens == 1) {
//                // check that fish is in fish list
//                split = strtok(NULL, s);
//
//                // check if fish exists in fish list
//                int fish_exists = 0;
//                for (int i = 0; i < a->nb_fish; i++) {
//                    if (strcmp(split, a->fishes[i]->name)) {
//                        fish_exists = 1;
//                        // start fish
//                        move_fish(a->fishes[i], a->width, a->height);
//                        printf("%s", valid_command);
//                        printf("fish started\n");
//                    }
//                }
//                if (fish_exists == 0) {
//                    printf("%s", unexistant_fish);
//                    printf("%s\n", "NOK\n");
//                }
//            }
//                // getFishesContinuously
//            else if (strcmp(split, "getFishesContinuously") == 0 && nb_tokens == 1) {
//                printf("%s", too_arg);
//            } else if (strcmp(split, "getFishesContinuously\n") == 0 &&
//                       nb_tokens == 1) {
//                printf("list ");
//                // gérer avec la connexion tcp, définir la fréquence d'affichage de la
//                // liste
//                for (int i = 0; i < a->nb_fish; i++) {
//                    show_fish(a->fishes[i]);
//                }
//            }
//                // ls
//            else if (strcmp(split, "ls\n") == 0 && nb_tokens == 1) {
//                if (a->nb_fish == 0)
//                    printf("no fish in the aquarium\n");
//                for (int i = 0; i < a->nb_fish; i++) {
//                    printf("list\n");
//                    show_fish(a->fishes[i]);
//                }
//            }
//                // hello
//            else if (strcmp(split, "hello\n") == 0 && nb_tokens == 1) {
//                // attribution aléatoire si que hello (parcourir la liste des vues
//                // dispo)
//                printf("greeting random\n");
//            } else if (strcmp(split, "hello") == 0 && nb_tokens == 1) {
//                // attribution non aléatoire
//                split = strtok(NULL, s);
//                // check that split is "in"
//                assert(strcmp(split, "in") == 0);
//
//                split = strtok(NULL, s);
//                // check that split is "as"
//                assert(strcmp(split, "as") == 0);
//
//                char *id = strtok(NULL, s);
//                // check that ID exists in the aquarium
//                int id_exists = 0;
//                for (int i = 0; i < a->nb_view; i++) {
//                    char buf_num_view[32];
//                    sprintf(buf_num_view, "N%d", a->views[i]->id);
//                    if (strcmp(split, buf_num_view)) {
//                        id_exists = 1;
//                        printf("greeting %s\n", id);
//
//                        printf("%s", valid_command);
//                    }
//                }
//                if (id_exists == 0) {
//                    printf("no greeting\n");
//                }
//            }
//                // log out
//            else if (strcmp(split, "log") == 0 && nb_tokens == 1) {
//                split = strtok(NULL, s);
//                if (strcmp(split, "out\n") == 0) {
//                    printf("bye\n");
//                }
//            }
//                // ping
//            else if (strcmp(split, "ping") == 0 && nb_tokens == 1) {
//                // define a time to delete a display program if it is not pinged
//                // check that connection is still done
//                split = strtok(NULL, s);
//                printf("pong %s\n", split);
//            }
//
//                /*
//                  Programme contrôleur
//                */
//
//                // load an aquarium
//            else if (strcmp(split, "load\n") == 0 && nb_tokens == 1) {
//                printf("%s", aq_arg);
//            } else if (strcmp(split, "load") == 0 && nb_tokens == 1) {
//                char *file_name = strtok(NULL, s);
//                // check that file exists
//                if (access(file_name, F_OK) == 0) {
//                    a = init_aquarium_from_file(file_name);
//                    printf("aquarium loaded (%d display view) !\n", a->nb_view);
//                } else {
//                    printf("Error : file not found\n");
//                }
//            }
//                // show an aquarium
//            else if (strcmp(split, "show\n") == 0 && nb_tokens == 1) {
//                printf("%s", aq_arg);
//            } else if (strcmp(split, "show") == 0 && nb_tokens == 1) {
//                split = strtok(NULL, s);
//
//                if (strcmp(split, "aquarium\n") == 0 && nb_tokens == 1) {
//                    show_aquarium(a);
//                    show_aquarium_views(a);
//                }
//            }
//                // save an aquarium in a file
//            else if (strcmp(split, "save\n") == 0 && nb_tokens == 1) {
//                printf("%s", aq_arg);
//            } else if (strcmp(split, "save") == 0 && nb_tokens == 1) {
//                char *file_name = strtok(NULL, s);
//
//                // check that file exists
//                if (access(file_name, F_OK) == 0) {
//                    a = init_aquarium_from_file(file_name);
//                    printf("Aquarium saved ! (%d display view)\n", a->nb_view);
//                } else {
//                    printf("Error : file not found\n");
//                }
//            }
//                // delete a view
//            else if (strcmp(split, "del\n") == 0 && nb_tokens == 1) {
//                printf("view and view number arguments missing\n");
//            } else if (strcmp(split, "del") == 0 && nb_tokens == 1) {
//                // printf("aquarium\n");
//                split = strtok(NULL, s);
//                if (strcmp(split, "view") == 0) {
//                    char *num_view = strtok(NULL, s);
//
//                    // check if view exists in the aquarium
//                    int view_exists = 0;
//                    for (int i = 0; i < a->nb_view; i++) {
//                        int n_view = a->views[i]->id;
//                        char buf_num_view[32];
//                        sprintf(buf_num_view, "N%d", n_view);
//                        if (strcmp(num_view, buf_num_view) == 0) {
//                            view_exists = 1;
//                            view *view_to_delete = a->views[n_view];
//                            delete_view(a, view_to_delete);
//                            printf("-> view %s deleted\n", buf_num_view);
//                        }
//                    }
//                    if (view_exists == 0) {
//                        printf("can't delete the view, it doesn't exist\n");
//
//                    } else {
//                        printf("%s", view_arg);
//                    }
//                }
//                    // add a view
//                else if (strcmp(split, "add") == 0 && nb_tokens == 1) {
//                    // printf("aquarium\n");
//                    split = strtok(NULL, s);
//                    if (strcmp(split, "view") == 0) {
//                        char *num_view = strtok(NULL, s);
//                        // add view number to view file
//                        char *id = strtok(NULL, s);
//                        // décomposer la chaîne de caractères dim pour récupérer
//                        // N{num_view}
//                        char *vue_x = strtok(NULL, s);
//                        char *vue_y = strtok(NULL, "x");
//                        char *vue_width = strtok(NULL, "+");
//                        char *vue_height = strtok(NULL, "+");
//                        int num_id = sscanf(vue_x, "%d", &num_id);
//                        int x = sscanf(vue_x, "%d", &x);
//                        int y = sscanf(vue_y, "%d", &y);
//                        int width = sscanf(vue_width, "%d", &width);
//                        int height = sscanf(vue_height, "%d", &height);
//                        printf("-> view analyzed\n");
//
//                        //  add view dimensions to view file
//                        view *v = init_view(num_id, x, y, width, height);
//                        add_view(a, v);
//                        printf("-> view added\n");
//                    } else {
//                        printf("view argument missing\n");
//                    }
//                }
//                    // invalid command
//                else if (nb_tokens == 1) {
//                    printf("%s", notFound);
//                }
//                split = strtok(NULL, s);
//            }
//
//            split = strtok(NULL, s);
//        }
//        // printf("%d\n", nb_tokens);
//        // nb_tokens = 0;
//    }
}

int main(int argc, char const *argv[]) {
    // gestion de la mémoire (en cas d'allocation dynamique)
    struct sigaction sa, old;
    sa.sa_handler = clean;
    sigset_t mask;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGKILL, &sa, &old);
    //aquarium *a = init_aquarium_from_file("../loader.txt");
    aquarium *a = malloc(sizeof(aquarium));
    pthread_create(&thread, NULL, (void *) start_server, arg);
    show_aquarium(a);
    while (1) {
        get_option(a);
    }
    free(a);
    printf("free");
    return 0;
}
