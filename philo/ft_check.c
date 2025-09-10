/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:11:47 by carlopez          #+#    #+#             */
/*   Updated: 2025/09/10 18:05:34 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

int	ft_check_death(t_philos *philo)
{
	long	die;

	pthread_mutex_lock(&philo->eat);
	die = ft_get_time_ms() - philo->last_meal;
	pthread_mutex_unlock(&philo->eat);
	if (die > philo->main->time_to_die)
	{
		pthread_mutex_lock(&philo->main->mute_main);
		philo->main->dead = true;
		pthread_mutex_unlock(&philo->main->mute_main);
		ft_print_actions(philo, DEAD);
		return (1);
	}
	return (0);
}

int	ft_check_meal_count(t_philos *philo, int *flag_meals, t_main *table)
{
	pthread_mutex_lock(&philo->mute_meals);
	if (philo->num_meal == table->num_meals)
		(*flag_meals)++;
	pthread_mutex_unlock(&philo->mute_meals);
	pthread_mutex_lock(&table->mute_main);
	if (table->num_philos == *flag_meals)
	{
		pthread_mutex_lock(&table->mute_all_meals);
		table->all_meals = true;
		pthread_mutex_unlock(&table->mute_all_meals);
		return (pthread_mutex_unlock(&table->mute_main), 1);
	}
	pthread_mutex_unlock(&table->mute_main);
	return (0);
}

int	ft_check_loop(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] && i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_is_digit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_check_args(int argc, char **argv)
{
	long	num;

	num = ft_atol(argv[1]);
	if (!ft_check_loop(argc, argv))
		return (printf("Error: non numeric argument\n"), 0);
	if (!(num > 0 && num <= 200))
		return (printf("Error: Invalid number of philos\n"), 0);
	return (1);
}
