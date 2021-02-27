#include "phylo.h"

int check_values(t_arguments *args);

t_arguments* parse_args(int ac, char** av, t_arguments *args)
{
    args->number_of_args = ac;
    args->number_of_phylo = ft_atoi(av[1]);
    args->ttd = ft_atoi(av[2]);
    args->tte = ft_atoi(av[3]);
    args->tts = ft_atoi(av[4]);
    args->number_of_times_each_phylo_must_eat =  ac == 6? ft_atoi(av[5]) : 0;

    if (check_values(args) == 1)
        return (args);
    else
        return (NULL);
}

int check_values(t_arguments *args)
{
    int flag;

    flag = 1;
    if (args->number_of_phylo < 2)
        flag = 0;
    if (args->ttd < 1)
        flag = 0;
    if (args->tts < 1)
        flag = 0;
    if (args->tte < 1)
        flag = 0;
  	if (args->number_of_args == 6 && args->number_of_times_each_phylo_must_eat < 0)
	    flag = 0;
    return (flag);
}