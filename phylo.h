#ifndef PHYLO_H
#define PHYLO_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <pthread.h>
#include "phylo.h"
#include <sys/time.h>

typedef struct  s_arguments
{
	int             number_of_args;
    int             number_of_phylo;
    int             ttd;
    int             tte;
    int             tts;
    int             number_of_times_each_phylo_must_eat;
	pthread_mutex_t *mutex_array;
    int             meals_total;

    pthread_t       thread;
    pthread_mutex_t *one;
    pthread_mutex_t *two;
    int             phylo_index;
    struct timeval  *last_meal_time;

}               t_arguments;

t_arguments* parse_args(int ac, char** av, t_arguments *args);
void ft_sleep(unsigned int);
int					ft_atoi(const char *s);
unsigned int time_has_left(struct timeval *tv);
void phylo_death(t_arguments *args);
void print_local_time(void);
void phylo_eat(t_arguments * args);


#endif