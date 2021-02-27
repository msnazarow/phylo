#include "phylo.h"

t_arguments *parse_args(int ac, char **av, t_arguments *args);
void simulate();
int check_values(t_arguments *pArguments);
void init_forks(t_arguments *args);
t_arguments **init_phylos(t_arguments *args);
void *hello(void *v_args);

int main(int ac, char **av)
{
	t_arguments args;

	if (ac != 6 && ac != 5)
	{
		write(1, "Wrong arguments!\n", 17);
		return (1);
	}
	if (parse_args(ac, av, &args) != NULL)
	{
		init_forks(&args);
		simulate(init_phylos(&args));
	}
	else
	{
		write(1, "Invalid arguments\n", 18);
		return (1);
	}
	return 0;
}

void init_forks(t_arguments *args)
{
	int i;

	args->mutex_array = malloc(sizeof(pthread_mutex_t) * args->number_of_phylo);
	i = 0;
	while (i < args->number_of_phylo)
	{
		pthread_mutex_init(&args->mutex_array[i], NULL);
		i++;
	}
}

t_arguments **init_phylos(t_arguments *info)
{
	t_arguments **args;
	int i;

	args = malloc(sizeof(t_arguments *) * info->number_of_phylo);
	i = 0;
	while (i < info->number_of_phylo)
	{
		args[i] = malloc(sizeof(t_arguments));
		++i;
	}
	i = 0;
	while (i < info->number_of_phylo)
	{
		args[i]->number_of_args = info->number_of_args;
		args[i]->number_of_phylo = info->number_of_phylo;
		args[i]->ttd = info->ttd;
		args[i]->tte = info->tte;
		args[i]->tts = info->tts;
		args[i]->number_of_times_each_phylo_must_eat = info->number_of_times_each_phylo_must_eat;

		args[i]->thread = malloc(sizeof(pthread_t));
		args[i]->one = &info->mutex_array[i];
		args[i]->two = i + 1 == info->number_of_phylo ? &info->mutex_array[0] : &info->mutex_array[i + 1];
		args[i]->phylo_index = i;
		args[i]->meals_total = 0;
		++i;
	}
	return (args);
}

void simulate(t_arguments **args)
{
	int i;
	int status_addr;
	struct timeval tv_start;
	
	gettimeofday(&tv_start, NULL);
	i = 0;
	while (i < args[0]->number_of_phylo)
	{
		args[i]->last_meal_time = &tv_start;
		int result = pthread_create(&args[i]->thread, NULL, hello, args[i]);
		pthread_detach(args[i]->thread);
		i++;
	}
	i = 0;
	while (i < args[0]->number_of_phylo)
	{		
		if (time_has_left(args[i]->last_meal_time) > args[i]->ttd)
			phylo_death(args[i]);		
		//pthread_join(args[i]->thread, (void*)&status_addr);
		i++;
	}
}

void *hello(void *v_args)
{
	t_arguments *args = v_args;
	if (args->phylo_index % 2 == 0)
		ft_sleep(args->ttd * 0.9);
	 while (1)
	 {
		pthread_mutex_lock(args->one);
		pthread_mutex_lock(args->two);
		print_local_time();
		printf("phylo %d has taken forks\n", args->phylo_index);
		print_local_time();
		printf("phylo %d is eating\n", args->phylo_index);
		ft_sleep(args->tte);
		++args->meals_total;
		pthread_mutex_unlock(args->one);
		pthread_mutex_unlock(args->two);

		print_local_time();
		printf("phylo %d is sleeping\n", args->phylo_index);
		ft_sleep(args->tts);

		print_local_time();
		printf("phylo %d is thinking\n", args->phylo_index);
	 }
	return 0;
}