#include "phylo.h"

void ft_sleep(unsigned int i) 
{
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    tv1.tv_usec += i;
    while (1)
    {
        gettimeofday(&tv2, NULL);
        if (tv2.tv_usec >= tv1.tv_usec)
            return;
    }
}
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
int		    	ft_isspace(char c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	if ((uc >= 9 && uc <= 13) || c == ' ')
		return (1);
	else
		return (0);
}

static int			sign_check(char c)
{
	int sign;

	sign = 0;
	if (c == '+')
		sign = 1;
	else if (c == '-')
		sign = -1;
	return (sign);
}

static long long	get_number(const char *s)
{
	long long res;

	res = 0;
	while (ft_isdigit(*s) != 0)
	{
		res *= 10;
		res += (*s - '0');
		s++;
	}
	return (res);
}

int					ft_atoi(const char *s)
{
	int	sign;
	int	signcount;

	sign = 1;
	signcount = 0;
	if ((sign_check(*s)) != 0)
	{
		sign = sign_check(*s);
		signcount++;
		s++;
	}
	else if (ft_isspace(*s) != 0)
		while (ft_isspace(*s) != 0)
			s++;
	if (sign_check(*s) != 0 && signcount == 0)
	{
		sign = sign_check(*s);
		s++;
	}
	if (ft_isdigit(*s) != 0)
	{
		return (int)((get_number(s)) * sign);
	}
	return (0);
}