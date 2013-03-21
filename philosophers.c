/*
** philosophers.c for philosophers in /home/hero/Dropbox/EPITECH/II/UNIX System/philosophers
** 
** Made by Marin Alcaraz
** Login   <alcara_m@epitech.net>
** 
** Started on  Mon Mar 18 18:42:04 2013 Marin Alcaraz
** Last update Wed Mar 20 16:34:05 2013 Marin Alcaraz
*/

#include "philosophers.h"

void 	philosopher_eating(t_philosopher *p)
{
	p->state = 'E';
	g_chopsticks[p->i] = 1;
	g_chopsticks[(p->i + 1) % 7] = 1;
	pthread_mutex_unlock(&g_choose);
	fprintf(stdout, "\e[1;%smPhilosopher %d : I'm eating now!\e[m\n", p->color, p->i);
	sleep(p->time_to_eat);
	p->rice -= p->hunger;
	if (p->rice < 0)
		p->rice = 0;
	fprintf(stdout, "\e[1;%smPhilosopher %d : I've finished eating %d rices (rest : %d rice)!\e[m\n", p->color,  p->i, p->hunger, p->rice);
	pthread_mutex_lock(&g_choose);
	g_chopsticks[p->i] = 0;
	g_chopsticks[(p->i + 1) % 7] = 0;
	pthread_mutex_unlock(&g_choose);
}

void    init_colors()
{
    g_dudes[0].color = "33";
    g_dudes[1].color = "31";
    g_dudes[2].color = "34";
    g_dudes[3].color = "35";
    g_dudes[4].color = "36";
    g_dudes[5].color = "32";
    g_dudes[6].color = "30";
}

void 	philosopher_thinking(t_philosopher *p)
{
	p->state = 'T';
	g_chopsticks[p->i] = 1;
	pthread_mutex_unlock(&g_choose);
	fprintf(stdout, "\e[1;%smPhilosopher %d : I'm thinking now!\e[m\n", p->color,  p->i);
	sleep(p->time_to_think);
	fprintf(stdout, "\e[1;%smPhilosopher %d : I've finished thinking!\e[m\n", p->color,  p->i);
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
	fprintf(stdout, "\e[1;%smPhilosopher %d : I'm going to relax\e[m\n", p->color,  p->i);
	sleep(p->time_to_rest);
	fprintf(stdout, "\e[1;%smPhilosopher %d : My energy is full!\e[m\n", p->color,  p->i);
}

void    *set_brain(void *arg)
{
	t_philosopher 	*p;
	int 		left;
	int 		right;
	char 		st;

	p = (t_philosopher*)arg;

	fprintf(stdout, "\e[1;%smPhilosopher %d : Came to the table!\e[m\n",p->color, p->i);
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
	fprintf(stdout, "\e[1;%smPhilosopher %d : Left the table!\e[m\n", p->color, p->i);
	return (NULL);
}

void        init_resources()
{
  int       i;

  i = 0;
  init_colors();
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
