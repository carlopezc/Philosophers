#include "ft_philosophers.h"

int ft_is_simulation_dead(t_main *main)
{
	int dead;

	pthread_mutex_lock(&main->mute_main);
	dead = main->dead;
	pthread_mutex_unlock(&main->mute_main);
	return (dead);
}

long	ft_atol(const char *nptr)
{
	int	i;
	int	sign;
	long	num;

	i = 0;
	sign = 1;
	num = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if ((nptr[i] == '-') || (nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		num = (num * 10) + (nptr[i++] - '0');
	return (sign * num);
}

int ft_is_digit(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

void    ft_print_actions(t_philos *philo, int action)
{
    int dead;

    dead = ft_is_simulation_dead(philo->main);
    pthread_mutex_lock(&(philo->main->mute_print));
    if (!dead && action == EAT)
        printf("%ld %d has eaten\n", ft_get_time_ms(), philo->id);
    else if (action == DEAD)
        printf("%ld %d died\n", ft_get_time_ms(), philo->id);
    else if (!dead && action == FORK)
        printf("%ld %d has taken a fork\n", ft_get_time_ms(), philo->id);
    else if (!dead && action == SLEEP)
        printf("%ld %d is sleeping\n", ft_get_time_ms(),  philo->id);
    else if (!dead && action == THINK)
        printf("%ld %d is thinking\n", ft_get_time_ms(), philo->id);
    pthread_mutex_unlock(&(philo->main->mute_print));
}