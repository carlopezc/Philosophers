/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:11:55 by carlopez          #+#    #+#             */
/*   Updated: 2025/09/09 16:11:56 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

int ft_init_philos(t_main *main)
{
    int i;

    i = -1;
    main->philos = (t_philos **)malloc(main->num_philos * sizeof(t_philos *));
    if (!main->philos)
        return (0);
    while (++i < main->num_philos)
    {
        main->philos[i] = (t_philos *)malloc(sizeof(t_philos));
        if (!main->philos[i])
            return (0);
        main->philos[i]->id = i + 1;
        main->philos[i]->dead = false;
        main->philos[i]->num_meal = 0;
        main->philos[i]->main = main;
        main->philos[i]->last_meal = 0;
        if (pthread_mutex_init(&main->philos[i]->r_fork, NULL) == -1)
            return (printf("Mutex failed\n"), 0);
        if (pthread_mutex_init(&main->philos[i]->mute_meals, NULL) == -1)
            return (printf("Mutex failed\n"), 0);
         if (pthread_mutex_init(&main->philos[i]->eat, NULL) == -1)
            return (printf("Mutex failed\n"), 0);
        if (i != 0)
                main->philos[i]->l_fork = &main->philos[i - 1]->r_fork;
    }
    if (main->num_philos > 1)
        main->philos[0]->l_fork = &main->philos[i - 1]->r_fork;
    return (1);

}

int ft_init_main(int argc, char **argv, t_main *main)
{
    main->num_philos = ft_atol(argv[1]);
    main->time_to_die = ft_atol(argv[2]);
    main->time_to_eat = (size_t)ft_atol(argv[3]);
    main->time_to_sleep = (size_t)ft_atol(argv[4]);
    main->time = 0;
    main->dead = 0;
    if (argc == 6)
        main->num_meals = ft_atol(argv[5]);
    else
        main->num_meals = -1;
    if (pthread_mutex_init(&(main->mute_print), NULL) == -1)
        return (printf("Mutex failed\n"), 0);
    if (pthread_mutex_init(&(main->mute_main), NULL) == -1)
        return (printf("Mutex failed\n"), 0);
    if (pthread_mutex_init(&(main->mute_all_meals), NULL) == -1)
        return (printf("Mutex failed\n"), 0);
    return (main->time_start = ft_get_time_ms(), ft_init_philos(main));
}

int ft_init_simulation(t_main *main)
{
    int         i;
    pthread_t	monitor_th;

    i = 0;
    pthread_mutex_lock(&(main->mute_main));
    while (i < main->num_philos)
    {
        //pthread_mutex_lock(&main->philos[i]->eat);
        //main->philos[i]->last_meal = ft_get_time_ms();
        //pthread_mutex_unlock(&main->philos[i]->eat);
        if (pthread_create(&main->philos[i]->thread, NULL, &ft_simulation, main->philos[i]))
            return (printf("Error creating thread\n"), 0);
        i++;
    }
    pthread_mutex_unlock(&(main->mute_main));
    pthread_create(&monitor_th, NULL, ft_monitor, main);
    pthread_join(monitor_th, NULL);
    i = 0;
    while (i < main->num_philos)
        pthread_join(main->philos[i++]->thread, NULL);
    return (1);
}