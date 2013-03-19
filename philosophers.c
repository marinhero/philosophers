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

int 	printf_thrds(FILE* f, const char *format, ...)
{
	va_list 	ap;
	int 		size;

	flockfile(f);
	va_start(ap, format);
	size = vfprintf(f, format, ap);
	va_end(ap);
	funlockfile(f);
	return (size);
}

void 	philosopher_eating(int i)
{

}

void 	philosopher_thinking(int i)
{
}

void 	philosopher_relax(int i)
{

}

void    *set_brain(void *p)
{
	t_philosopher 	*philo;

	philo = (t_philosopher*)p;
	printf_thrds(stdout, "Philosopher %d : Came to table!\n", philo->i);
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
    g_dudes[i].i = i;
    pthread_mutex_init(&g_chopsticks[i], NULL);
    pthread_create(&(g_dudes[i].handler), NULL, set_brain, &g_dudes[i]);
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
