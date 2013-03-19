/*
** philosophers.h for philosophers in /home/hero/Dropbox/EPITECH/II/UNIX System/philosophers
** 
** Made by Marin Alcaraz
** Login   <alcara_m@epitech.net>
** 
** Started on  Mon Mar 18 18:48:33 2013 Marin Alcaraz
** Last update Mon Mar 18 20:10:32 2013 Marin Alcaraz
*/

#ifndef PHILOSHOPERS_H_
# define PHILOSHOPERS_H_

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct      s_phylosopher
{
    pthread_t       handler;
    char            state;
    int             time_to_think;
    int             time_to_eat;
    int             time_to_rest;
    char            *name;
    int             rice;
    int             hunger;
}                   t_phylosopher;

pthread_mutex_t         g_chopsticks[7];
t_phylosopher           g_dudes[7];

void    init_resources(void);
void    wait_for(void);

#endif /* !PHILOSHOPERS_H_ */