#include "phylo.h"

unsigned int time_has_left(struct timeval *started)
{
    struct timeval now;
    struct timeval difference;
    
    gettimeofday(&now, NULL);
    difference.tv_sec = now.tv_sec - started->tv_sec;
    difference.tv_usec = now.tv_usec - started->tv_usec;
    gettimeofday(started, NULL);
    return (difference.tv_usec);//в микросекундах
}

void    phylo_death(t_arguments *args)
{
	print_local_time();
    printf("phylo %d is dead\n", args->phylo_index);
    exit(0);
}

void    print_local_time() 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("%ld.%06d ", tv.tv_sec % 100, tv.tv_usec);

}

void phylo_eat(t_arguments * args)
{
    	pthread_mutex_lock(args->one);
		print_local_time();
		printf("phylo %d has taken a left fork\n", args->phylo_index);
		pthread_mutex_lock(args->two);
		print_local_time();
		printf("phylo %d has taken two forks\n", args->phylo_index);
		print_local_time();
		printf("phylo %d is eating\n", args->phylo_index);
		ft_sleep(args->tte);
		++args->meals_total;
		pthread_mutex_unlock(args->one);
		pthread_mutex_unlock(args->two);
}

void update_last_meal_time(t_arguments *args, struct timeval *tv) 
{
	gettimeofday(tv, NULL);
	args->last_meal_time = tv;
}