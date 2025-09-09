/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:11:39 by carlopez          #+#    #+#             */
/*   Updated: 2025/09/09 16:11:41 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void    ft_eat_alone(t_philos *philo)
{
    pthread_mutex_lock(&philo->r_fork);
    ft_print_actions(philo, FORK);
    ft_usleep(philo->main->time_to_die - ft_elapsed_time(philo));
    pthread_mutex_lock(&philo->main->mute_print);
    printf("%ld %d died\n", ft_get_time_ms(), philo->id);
    pthread_mutex_unlock(&philo->main->mute_print);
    pthread_mutex_lock(&philo->main->mute_main);
    philo->main->dead = true;
    pthread_mutex_unlock(&philo->main->mute_main);
    pthread_mutex_unlock(&philo->r_fork);
}

void    ft_eat(t_philos *philo)
{
    if (philo->main->num_philos == 1)
        return (ft_eat_alone(philo));
   // if (!((philo->last_meal + philo->main->time_to_eat) * 0.5 > ft_get_time_ms()))
	 // 	usleep(100);
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->r_fork);
        ft_print_actions(philo, FORK);
        pthread_mutex_lock(philo->l_fork);
        ft_print_actions(philo, FORK);
    }
    else
    {
        pthread_mutex_lock(philo->l_fork);
        ft_print_actions(philo, FORK);
        pthread_mutex_lock(&philo->r_fork);
        ft_print_actions(philo, FORK);
    }
    pthread_mutex_lock(&philo->eat);
    philo->last_meal = ft_get_time_ms();
    pthread_mutex_unlock(&philo->eat);
    pthread_mutex_lock(&philo->mute_meals);
    philo->num_meal++;
    pthread_mutex_unlock(&philo->mute_meals);
    ft_print_actions(philo, EAT);
    ft_usleep(philo->main->time_to_eat);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(&philo->r_fork);
}

void    *ft_simulation(void *data)
{
    t_philos *philo;

    philo = data;
    pthread_mutex_lock(&(philo->main->mute_main));
    pthread_mutex_unlock(&(philo->main->mute_main));
    if (philo->id % 2 != 0)
        ft_usleep(philo->main->time_to_eat/2);
    while (!ft_is_simulation_dead(philo->main) && philo->main->num_meals != philo->num_meal)
    {
        ft_eat(philo);
        if (ft_is_simulation_dead(philo->main) || philo->main->num_meals == philo->num_meal)
            break ;
        ft_print_actions(philo, SLEEP);
        usleep(philo->main->time_to_sleep * 1000);
        ft_print_actions(philo, THINK);
        usleep(200);
    }
    return (NULL);
}