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

void 	philosopher_eating(t_philosopher *p)
{
	p->state = 'E';
	g_chopsticks[p->i] = 1;
	g_chopsticks[(p->i + 1) % 7] = 1;
	pthread_mutex_unlock(&g_choose);
	fprintf(stdout, "Philosopher %d : I'm eating now!\n", p->i);
	sleep(p->time_to_eat);
	p->rice -= p->hunger;
	if (p->rice < 0)
		p->rice = 0;
	fprintf(stdout, "Philosopher %d : I've finished eating %d rices (rest : %d rice)!\n", p->i, p->hunger, p->rice);
	pthread_mutex_lock(&g_choose);
	g_chopsticks[p->i] = 0;
	g_chopsticks[(p->i + 1) % 7] = 0;
	pthread_mutex_unlock(&g_choose);
}

void 	philosopher_thinking(t_philosopher *p)
{
	p->state = 'T';
	g_chopsticks[p->i] = 1;
	pthread_mutex_unlock(&g_choose);
	fprintf(stdout, "Philosopher %d : I'm thinking now!\n", p->i);
	sleep(p->time_to_think);
	fprintf(stdout, "Philosopher %d : I've finished thinking!\n", p->i);
	while (p->state != 'E')
	{
		pthread_mutex_lock(&g_choose);
		if (g_chopsticks[(p->i + 1) % 7] == 0)
			philosopher_eating(p);
		else
			pthread_mutex_unlock(&g_choose);
	}
}

void 	philosopher_relax(t_philosopher *p)
{
	pthread_mutex_unlock(&g_choose);
	if (p->state == 'R')
		return ;
	p->state = 'R';
	fprintf(stdout, "Philosopher %d : I'm going to relax\n", p->i);
	sleep(p->time_to_rest);
	fprintf(stdout, "Philosopher %d : My energy is full!\n", p->i);
}

void    *set_brain(void *arg)
{
	t_philosopher 	*p;
	int 		left;
	int 		right;
	char 		st;

	p = (t_philosopher*)arg;
	fprintf(stdout, "Philosopher %d : Came to the table!\n", p->i);
	while (p->rice > 0)
	{
		pthread_mutex_lock(&g_choose);
		left  = g_chopsticks[p->i];
		right  = g_chopsticks[(p->i + 1) % 7];
		if (left == 0 && right == 0 && p->state != 'E')
			philosopher_eating(p);
		else if (left == 0 && p->state != 'T' && p->state != 'E')
			philosopher_thinking(p);
		else
			philosopher_relax(p);
	}
	fprintf(stdout, "Philosopher %d : Left the table!\n", p->i);
	return (NULL);
}

void        init_resources()
{
  int       i;

  i = 0;
  while (i < 7)
  {
    g_dudes[i].state = 'R';
    g_dudes[i].time_to_think = rand() % 5;
    g_dudes[i].time_to_eat = rand() % 5;
    g_dudes[i].time_to_rest = rand() % 5;
    g_dudes[i].hunger = rand() % 50;
    g_dudes[i].rice = 100;
    g_dudes[i].i = i;
    g_chopsticks[i] = 0;
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
