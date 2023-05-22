#include "handler_server.h"
#include "../Model/aquarium.h"

char *notFound = "-> NOK : commande introuvable\n";

void server_load_aquarium(aquarium *a, char argv[])
{

    char input[100] = "";
    char aquarium_file[20] = "";
    char extra_argument[100] = "";

    // get client arguments
    sscanf(argv, "%s %s %s", input, aquarium_file, extra_argument);

    if (strcmp(extra_argument, "") != 0)
    {
        printf("Error: too many arguments, the command should be : load "
               "[AQUARIUM_FILE]\n");
        return;
    }

    if (strcmp(aquarium_file, "") == 0)
    {
        printf("Error: aquarium file must be specified such as : load "
               "[AQUARIUM_FILE]\n");
        return;
    }
    int res = init_aquarium_from_file(a, aquarium_file);
    if (res == 1)
    {
        printf("Error: aquarium file not found\n");
        return;
    } else {
        printf("-> aquarium loaded (%d display view) !\n", a->nb_view);
    }

}



void server_show_aquarium(aquarium *a, char argv[])
{

    char input[100] = "";
    char aquarium[100] = "";

    // get client arguments
    sscanf(argv, "%s %s", input, aquarium);

    if (strcmp(aquarium, "") == 0)
    {
        printf("Error: no aquarium loaded\n");
        return;
    }

    if (strcmp(aquarium, "aquarium\0") != 0)
    {
        printf("aquarium argument must be specified such as : show aquarium\n");
    }
    else
    {
        show_aquarium(a);
        show_aquarium_views(a);
    }
}

void server_save_aquarium(aquarium *a, char argv[])
{

    char input[100] = "";
    char aquarium_file[100] = "";

    // get client arguments
    sscanf(argv, "%s %s", input, aquarium_file);

    if (strcmp(aquarium_file, "") == 0)
    {
        printf("Error: aquarium file must be specified such as : save "
               "[AQUARIUM_FILE]\n");
        return;
    }
    save_aquarium(a, aquarium_file);
}

void server_add_view(aquarium *a, char argv[])
{

    char input[100] = "";
    char view[100] = "";
    long int view_id = -1;
    long int long_vue_x = -1, long_vue_y = -1, long_width = -1, long_height = -1;
    sscanf(argv, "%s %s %ld %ldx%ld+%ld+%ld", input, view, &view_id, &long_vue_x,
           &long_vue_y, &long_width, &long_height);

    // check the arguments
    printf("view : %s\n", view);
    printf("view_id : %ld\n", view_id);
    printf("long_vue_x : %ld\n", long_vue_x);
    printf("long_vue_y : %ld\n", long_vue_y);
    printf("long_width : %ld\n", long_width);
    printf("long_height : %ld\n", long_height);

    // check that the view fits into the aquarium
    if (strcmp(view, "view") != 0)
    {
        printf("view must be specified as second parameter, such as : add view "
               "[VIEW_ID]\n");
    }
    // Check if the view arguments are valid
    if (view_id == -1 || long_vue_x == -1 || long_vue_y == -1 ||
        long_width == -1 || long_height == -1)
    {
        printf("Error : incorrect format, required format is : 'add view [VIEW_ID] "
               "[X]x[Y]+[WIDTH]+[HEIGHT]'\n");
        return;
    }

    int id = (int)view_id;
    int x = (int)long_vue_x;
    int y = (int)long_vue_y;
    int width = (int)long_width;
    int height = (int)long_height;

    // if conditions are fulfilled, create a view and add it to the aquarium
    struct view *v = init_view(id, x, y, width, height);
    add_view(a, v);
    printf("-> view added\n");
}

void server_del_view(aquarium *a, char argv[])
{
    // get arguments
    char input[100] = "";
    char view[100] = "";
    long int view_id = -1;

    sscanf(argv, "%s %s %ld", input, view, &view_id);

    if (strcmp(view, "view") == 0)
    {
        if (view_id == -1)
        {
            printf("view id must be specified\n");
        }
    }
    else
    {
        printf("bad arguments syntax\n");
    }

    // check that view exists
    int view_exists = 0;
    if (a->nb_view == 0)
    {
        printf("no view in the aquarium\n");
    }

    for (int i = 0; i < a->nb_view; i++)
    {
        if (view_id == a->views[i]->id)
        {
            view_exists = 1;
            struct view *v = a->views[i];
            delete_view(a, v);
            printf("-> view %ld deleted\n", view_id);
        }
    }
    if (view_exists == 0)
    {
        printf("NOK : view doesn't exist in the aquarium\n");
    }
}

void server_get_input(aquarium *a)
{
    int size_arg = 100;
    char arg[size_arg];
    if (fgets(arg, size_arg, stdin) != NULL)
    {
        arg[strcspn(arg, "\n")] = '\0'; // remplace '\n' par '\0'
        char input[100] = "";
        char input2[100] = "";

        sscanf(arg, "%s", input);
        if (strcmp(input, "load") == 0)
        {
            server_load_aquarium(a, arg);
        }
        else if (strcmp(input, "show") == 0)
        {
            server_show_aquarium(a, arg);
        }
        else if (strcmp(input, "add") == 0)
        {
            server_add_view(a, arg);
        }
        else if (strcmp(input, "del") == 0)
        {
            server_del_view(a, arg);
        }
        else if (strcmp(input, "save") == 0)
        {
            server_save_aquarium(a, arg);
        }
        else
        {
            printf("%s", notFound);
        }
    }
}