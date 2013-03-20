/*
** philosophers.c for philosophers in /home/hero/Dropbox/EPITECH/II/UNIX System/philosophers
** 
** Made by Marin Alcaraz
** Login   <alcara_m@epitech.net>
** 
** Started on  Mon Mar 18 18:42:04 2013 Marin Alcaraz
** Last update Wed Mar 20 05:26:58 2013 Marin Alcaraz
*/

#include "philosophers.h"

int 	philosopher_eating(t_philosopher *p)
{
	fprintf(stdout, "Philosopher %d : I'm eating now!\n", p->i);
	sleep(p->time_to_eat);
	p->rice -= p->hunger;
	if (p->rice <= 0)
	{
		fprintf(stdout, "Philosopher %d : I'm fulll\n", p->i);
		return (0);
	}
	fprintf(stdout, "Philosopher %d : I'm finish eating %d rices (rest : %d rice)!\n", p->i, p->hunger, p->rice);
	return (1);
}

void 	philosopher_thinking(t_philosopher *p)
{
	fprintf(stdout, "Philosopher %d : I'm thinking now!\n", p->i);
	sleep(p->time_to_think);
	fprintf(stdout, "Philosopher %d : I'm finish thinking!\n", p->i);
}

void 	philosopher_relax(t_philosopher *p)
{
	fprintf(stdout, "Philosopher %d : I'm going to relax\n", p->i);
	sleep(p->time_to_rest);
	fprintf(stdout, "Philosopher %d : My energy is full!\n", p->i);
}

void    *set_brain(void *arg)
{
	t_philosopher 	*p;

	p = (t_philosopher*)arg;
	fprintf(stdout, "Philosopher %d : Came to the table!\n", p->i);
	while (philosopher_eating(p))
	{
		philosopher_relax(p);
		philosopher_thinking(p);
	}
	fprintf(stdout, "Philosopher %d : Left the table!\n", p->i);
	return (NULL);
}

void        init_resources()
{
  int       i;
  int       t;

  i = 0;
  t = rand() % 5;
  while (i < 7)
  {
    g_dudes[i].state = 'R';
    g_dudes[i].time_to_think = t;
    g_dudes[i].time_to_eat = t / 2;
    g_dudes[i].time_to_rest = 1;
    g_dudes[i].hunger = rand() % 50;
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
