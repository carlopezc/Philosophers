
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
    long    time_start;
}   t_main;

#endif