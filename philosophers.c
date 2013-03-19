/*
** philosophers.c for philosophers in /home/hero/Dropbox/EPITECH/II/UNIX System/philosophers
** 
** Made by Marin Alcaraz
** Login   <alcara_m@epitech.net>
** 
** Started on  Mon Mar 18 18:42:04 2013 Marin Alcaraz
** Last update Mon Mar 18 23:20:22 2013 Marin Alcaraz
*/

#include "philosophers.h"


void    *set_brain(void *index)
{

    return (NULL);
}

void        init_resources()
{
  int     i;

  i = 0;
  while (i < 7)
  {
    g_dudes[i].state = 'R';
    g_dudes[i].time_to_think = rand() % 10;
    g_dudes[i].time_to_eat = rand() % 10;
    g_dudes[i].time_to_rest = rand() % 10;
    g_dudes[i].hunger = rand() % 10;
    g_dudes[i].rice = 100;
    pthread_mutex_init(&g_chopsticks[i], NULL);
    pthread_create(&(g_dudes[i].handler), NULL, set_brain, &i);
    i = i + 1;
  }
}

void        wait_for()
{
  int     i;

  i = 0;
  while (i < 7)
  {
    pthread_join((g_dudes[i].handler), NULL);
    i = i + 1;
  }
}

int         main()
{
  srand(0);
  init_resources();
  wait_for();
  return (0);
}
