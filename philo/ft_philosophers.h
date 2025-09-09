/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:12:06 by carlopez          #+#    #+#             */
/*   Updated: 2025/09/09 16:12:07 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILOSOPHERS_H
#define FT_PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mtx;

enum
{
    EAT,
    THINK,
    DEAD,
    FORK,
    SLEEP
};

typedef struct s_philos
{
    int id;
    bool dead;
    int num_meal;
    long    last_meal;
    t_mtx   r_fork;
    t_mtx   *l_fork;
    t_mtx   eat;
    t_mtx   mute_meals;
    pthread_t   thread;
    struct s_main   *main;
}   t_philos;

typedef struct s_main
{
    int num_philos;
    long time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    size_t  time;
    int num_meals;
    t_philos    **philos;
    bool    dead;
    bool    all_meals;
    t_mtx   mute_print;
    t_mtx   mute_main;
    t_mtx mute_all_meals;
    long    time_start;
}   t_main;

void    ft_print_actions(t_philos *philo, int action);
long	ft_get_time_ms(void);
void	ft_usleep(long ms);
int ft_is_simulation_dead(t_main *main);
long	ft_elapsed_time(t_philos *philo);
int ft_is_digit(char c);
long	ft_atol(const char *nptr);
void    *ft_simulation(void *data);
void	*ft_monitor(void *data);
int	ft_check_meal_count(t_philos *philo, int *flag_meals, t_main *table);
int ft_check_death(t_philos *philo);
int ft_check_args(int argc, char **argv);
int ft_init_main(int argc, char **argv, t_main *main);
int ft_init_simulation(t_main *main);

#endif