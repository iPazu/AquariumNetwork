#include "aquarium.h"
#include "../main.h"

aquarium *init_aquarium(int x_max, int y_max, int nb_fish, int nb_view)
{
  aquarium *a = malloc(sizeof(aquarium));
  a->width = x_max;
  a->height = y_max;
  a->nb_fish = nb_fish;
  a->nb_view = nb_view;
  return a;
}

int init_aquarium_from_file(aquarium *a, char *file_name)
{
  a->nb_fish = 0;
  a->nb_view = 0;
  FILE *file = fopen(file_name, "r");
  if (file == NULL)
  {
    printf("Error while opening the file %s.txt\n", file_name);
    return 1;
  }

  char buffer[1024];
  // Read the first line for aquarium size
  fgets(buffer, sizeof(buffer), file);
  sscanf(buffer, "%dx%d", &a->width, &a->height);

  // Read and create the views
  while (fgets(buffer, 100, file))
  {
    view *v = malloc(sizeof(view));
    if (!v)
    {
      printf("Error: impossible to allocate the view\n");
      return 1;
    }
    sscanf(buffer, "N%d %dx%d+%d+%d", &v->id, &v->x, &v->y, &v->width,
           &v->height);
    a->views[a->nb_view++] = v;
  }

  fclose(file);
  return 0;
}

void add_fish(aquarium *a, fish *f)
{
  if (f == NULL)
  {
    printf("Error: fish is NULL\n");
    return;
  }
  if (a->nb_fish >= MAX_FISHES)
  {
    printf("Error: too many fishes\n");
    free(f);
    return;
  }
  a->fishes[a->nb_fish] = f;
  a->nb_fish++;
}

void move_fishes(aquarium *a)
{
  for (int i = 0; i < a->nb_fish; i++)
  {
    if (a->fishes[i]->is_started != 0)
    {
      a->fishes[i]->move(a->fishes[i], a->width, a->height);
    }
  }
}

void delete_fish(aquarium *a, fish *f)
{
  for (int i = 0; i < a->nb_fish; i++)
  {
    if (a->fishes[i] == f)
    {
      a->fishes[i] = a->fishes[a->nb_fish - 1];
      a->nb_fish--;
      break;
    }
  }
  free(f);
}

void show_aquarium(aquarium *a)
{
  printf("Aquarium:\n\tWidth: %d\n\tHeight: %d\n\tNumber of fishes: "
         "%d\n\tNumber of views: %d\n",
         a->width, a->height, a->nb_fish, a->nb_view);
}

void show_aquarium_fishes(aquarium *a)
{
  char *buf =
      malloc(sizeof(char) * 1024); // A ENLEVER ET PASSER EN PARAMETRE !!!
  printf("--------------\n");
  for (int i = 0; i < a->nb_fish; i++)
  {
    show_fish(a->fishes[i], buf);
    printf("%s\n", buf);
  }
  printf("--------------\n");
}

void show_aquarium_views(aquarium *a)
{
  printf("--------------\n");
  for (int i = 0; i < a->nb_view; i++)
  {
    show_view(a->views[i]);
  }
  printf("--------------\n");
}

void add_view(aquarium *a, view *v)
{
  int error = 0;
  if (a->nb_view >= MAX_VIEW)
  {
    error++;
    printf("Error: too many views\n");
  }

  for (int i = 0; i < a->nb_view; i++)
  {
    if (a->views[i]->id == v->id)
    {
      error++;
      printf("Error: view ID already exists\n");
    }
  }

  if (v->x < 0 || v->y < 0)
  {
    error++;
    printf("Error: view out of aquarium\n");
  }
  if (v->x + v->width > a->width || v->y + v->height > a->height)
  {
    error++;
    printf("Error: view out of aquarium\n");
  }
  if (error == 0)
  {
    a->views[a->nb_view] = v;
    a->nb_view++;
  }
}

void delete_view(aquarium *a, view *v)
{
  for (int i = 0; i < a->nb_view; i++)
  {
    if (a->views[i] == v)
    {
      a->views[i] = a->views[a->nb_view - 1];
      a->nb_view--;
      break;
    }
  }
  // free(v);
}

int view_superposition(aquarium *a)
{
  if (a->nb_view < 2)
  {
    printf("there's less than two views in the aquarium\n");
  }
  view *current_view = a->views[0];
  for (int i = 1; i < a->nb_view; i++)
  {
    view *explored_view = a->views[i];
    if ((explored_view->x + explored_view->width > current_view->x &&
         explored_view->y + explored_view->height > current_view->y) ||
        (current_view->x + current_view->width > explored_view->x &&
         current_view->y + current_view->height > explored_view->y))
    {
      printf("%d\n", explored_view->id);
      return explored_view->id;
    }
  }
  // case where there is no view intersection
  return -1;
}

int available_views(aquarium *a)
{
  char *buf = malloc(sizeof(char) * 100);

  int views_are_available = 0;
  if (a->nb_view == 0)
  {
    return 0;
  }
  for (int i = 0; i < a->nb_view; i++)
  {
    if (a->views[i]->is_assigned == -1)
    {
      char *tmp = malloc(sizeof(char) * 10);
      a->nb_available_views += 1;
      a->id_available_views[i] = a->views[i]->id;
      sprintf(tmp, "%d", a->id_available_views[i]);
      strcat(buf, tmp);
      strcat(buf, " ");
      free(tmp);
      views_are_available = 1;
    }
  }
  free(buf);
  return views_are_available;
}

void save_aquarium(aquarium *a, char *file_name)
{
  FILE *file = fopen(file_name, "w");
  if (file == NULL)
  {
    printf("Error while opening the file %s\n", file_name);
    exit(1);
  }
  fprintf(file, "%dx%d\n", a->width, a->height);
  for (int i = 0; i < a->nb_view; i++)
  {
    show_view(a->views[i]);
    fprintf(file, "N%d %dx%d+%d+%d\n", a->views[i]->id, a->views[i]->x,
            a->views[i]->y, a->views[i]->width, a->views[i]->height);
  }
  fclose(file);
  printf("Aquarium saved in %s\n", file_name);
}

void free_aquarium(aquarium *a)
{
  for (int i = 0; i < a->nb_fish; i++)
  {
    free(a->fishes[i]);
  }
  for (int i = 0; i < a->nb_view; i++)
  {
    free(a->views[i]);
  }
  free(a);
}

void fish_behaviors(aquarium *a)
{
  int current_nb_fish = a->nb_fish;
  for (int i = 0; i < current_nb_fish - 1; i++)
  {
    for (int j = i + 1; j < current_nb_fish; j++)
    {
      // Reproduction
      fish *baby_fish = a->fishes[i]->reproduction(a->fishes[i], a->fishes[j]);
      if (baby_fish != NULL)
      {
        add_fish(a, baby_fish);
      }
      // Hunting
      fish *eaten_fish = a->fishes[i]->hunting(a->fishes[i], a->fishes[j]);
      if (eaten_fish != NULL)
      {
        delete_fish(a, eaten_fish);
      }
    }
  }
}

void handle_aquarium(aquarium *a)
{
  while (1)
  {
    move_fishes(a);
    //fish_behaviors(a);
    //show_aquarium_fishes(a);
    sleep(1);
  }
}

/* int main() {
    aquarium *a = malloc(sizeof(aquarium));
    init_aquarium_from_file(a, "../loader.txt");
    fish *f1 = init_fish_from_client("Fish1", 0, 0, 3, 1, 0, "Espece1",
                                     "RandomPointWay", "Classic", "Classic");
    fish *f2 = init_fish_from_client("Fish2", 1, 1, 3, 2, 1, "Espece1",
                                     "RandomPointWay", "Classic", "Classic");
    fish *f3 = init_fish_from_client("Fish3", 2, 2, 3, 3, 0, "Espece1",
                                     "RandomPointWay", "Classic", "Classic");
    fish *f4 = init_fish_from_client("Fish4", 3, 3, 3, 4, 1, "Espece1",
                                     "RandomPointWay", "Classic", "Classic");

    add_fish(a, f1);
    add_fish(a, f2);
    add_fish(a, f3);
    add_fish(a, f4);

    move_fishes(a);
    fish_behaviors(a);
    move_fishes(a);
    fish_behaviors(a);
    show_aquarium(a);

    free_aquarium(a);

    return 0;
} */