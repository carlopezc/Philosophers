/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:12:00 by carlopez          #+#    #+#             */
/*   Updated: 2025/09/10 16:20:30 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void    ft_free_mutex(t_main *main)
{
    int     i;

    i = -1;
    pthread_mutex_destroy(&main->mute_main);
    pthread_mutex_destroy(&main->mute_print);
    while (++i < main->num_philos)
    {
        pthread_mutex_destroy(&main->philos[i]->r_fork);
        pthread_mutex_destroy(&main->philos[i]->eat);
        free(main->philos[i]);
        main->philos[i] = NULL;
    }
    free(main->philos);
    main->philos = NULL;
    return ;
}

void	*ft_monitor(void *data)
{
	t_main	*table;
	int		i;
	int		flag_meals;

	table = (t_main *)data;
	if (table->num_philos == 1)
		return (NULL);
	while (1)
	{
		i = 0;
		flag_meals = 0;
		while (i < table->num_philos)
		{
			if (ft_check_death(table->philos[i]) || ft_check_meal_count(table->philos[i], &flag_meals, table))
				return (NULL);
            i++;
		}
		usleep(500);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
    t_main  main;

    if (argc < 5 || argc > 6)
        return (printf("Error: Invalid number of arguments\n"), 0);
    if (!ft_check_args(argc, argv))
        return (0);
    if (!ft_init_main(argc, argv, &main))
        return (printf("Error in initialization\n"), 0);
    if (!ft_init_simulation(&main))
        return (printf("Error in simulation\n"), 0);
    ft_free_mutex(&main);
    return (0);
}
