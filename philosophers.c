/*
** philosophers.c for philosophers in /home/hero/Dropbox/EPITECH/II/UNIX System/philosophers
** 
** Made by Marin Alcaraz
** Login   <alcara_m@epitech.net>
** 
** Started on  Mon Mar 18 18:42:04 2013 Marin Alcaraz
** Last update Wed Mar 20 17:25:33 2013 Marin Alcaraz
*/
#include "philosophers.h"

int       	 	        g_chopsticks[7];
t_philosopher           g_dudes[7];
pthread_mutex_t 	    g_choose = PTHREAD_MUTEX_INITIALIZER;

void 	        philosopher_eating(t_philosopher *p)
{
	p->state = 'E';
	p->states[p->st_i] = p->state;
	p->st_i++;
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

void 	        philosopher_thinking(t_philosopher *p)
{
	p->state = 'T';
	p->states[p->st_i] = p->state;
	p->st_i++;
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
	p->states[p->st_i] = p->state;
	p->st_i++;
	fprintf(stdout, "\e[1;%smPhilosopher %d : I'm going to relax\e[m\n", p->color,  p->i);
	sleep(p->time_to_rest);
	fprintf(stdout, "\e[1;%smPhilosopher %d : My energy is full!\e[m\n", p->color,  p->i);
}

void                *set_brain(void *arg)
{
	t_philosopher 	*p;
	int 		    left;
	int 		    right;

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

int         main()
{
  srand(time(NULL));
  init_resources();
  wait_for();
  print_states_history();
  return (0);
}
