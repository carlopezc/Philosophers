#include "ft_philosophers.h"

long	get_time_ms(void)
{
	struct timeval	tv;
	static time_t	start_time;

	if (start_time == 0)
	{
		gettimeofday(&tv, NULL);
		start_time = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	}
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - start_time);
}


int is_simulation_dead(t_main *main)
{
	int dead;

	pthread_mutex_lock(&main->mute_main);
	dead = main->dead;
	pthread_mutex_unlock(&main->mute_main);
	return (dead);
}

void	ft_usleep(long ms)
{
	long	start;
	long	now;
	long	remaining;

	start = get_time_ms();
	while (1)
	{
		now = get_time_ms();
		remaining = ms - (now - start);
		if (remaining <= 0)
			break;
		if (remaining > 10)
			usleep(500);  // más eficiente para tiempos largos
		else
			usleep(100);  // más preciso para tramos cortos
	}
}

long	elapsed_time(t_philos *philo)
{
	return (get_time_ms() - philo->main->time_start);
}
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
int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	num;

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

int ft_init_philos(t_main *main)
{
    int i;

    i = -1;
    main->philos = (t_philos **)malloc(main->num_philos * sizeof(t_philos *));
    if (!main->philos)
        return (0);
    while (++i < main->num_philos)
    {
        main->philos[i] = (t_philos *)malloc(main->num_philos * sizeof(t_philos));
        if (!main->philos[i])
            return (0);
        main->philos[i]->id = i + 1;
        main->philos[i]->dead = false;
        main->philos[i]->num_meal = 0;
        main->philos[i]->main = main;
        main->philos[i]->last_meal = 0;
        if (pthread_mutex_init((&main->philos[i]->r_fork), NULL) == -1)
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
    main->num_philos = ft_atoi(argv[1]);
    main->time_to_die = (long)ft_atoi(argv[2]);
    main->time_to_eat = (size_t)ft_atoi(argv[3]);
    main->time_to_sleep = (size_t)ft_atoi(argv[4]);
    main->time = 0;
    if (argc == 6)
        main->num_meals = ft_atoi(argv[5]);
    else
        main->num_meals = -1;
    if (pthread_mutex_init(&(main->mute_print), NULL) == -1)
        return (0);
    if (pthread_mutex_init(&(main->mute_main), NULL) == -1)
        return (0);
    return (main->time_start = get_time_ms(), ft_init_philos(main));
}

int ft_is_digit(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

int ft_check_loop(int argc, char **argv)
{
    int i;
    int j;

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

int ft_check_args(int argc, char **argv)
{
    if (!ft_check_loop(argc, argv))
        return (printf("Error: non numeric argument\n"), 0);
    if (!(ft_atoi(argv[1]) > 0 && ft_atoi(argv[1]) <= 200))
        return (printf("Error: Invalid number of philos\n"), 0);
    return (1);
}

void    ft_print_actions(t_philos *philo, size_t time, int action)
{
    (void)time;
   
    pthread_mutex_lock(&(philo->main->mute_print));
    if (!is_simulation_dead(philo->main) && action == EAT)
        printf("%ld %d has eaten\n", get_time_ms(), philo->id);
    else if (action == DEAD)
        printf("%ld %d died\n", get_time_ms(), philo->id);
    else if (!is_simulation_dead(philo->main) && action == FORK)
        printf("%ld %d has taken a fork\n",get_time_ms(), philo->id);
    else if (!is_simulation_dead(philo->main) && action == SLEEP)
        printf("%ld %d is sleeping\n",get_time_ms(),  philo->id);
    else if (!is_simulation_dead(philo->main) && action == THINK)
        printf("%ld %d is thinking\n", get_time_ms(), philo->id);
    pthread_mutex_unlock(&(philo->main->mute_print));
}
/*
void    ft_print_actions(t_philos *philo, size_t time, int action)
{
    (void)time;
    printf("print actions\n");
    pthread_mutex_lock(&(philo->main->mute_print));
    if (!is_simulation_dead(philo->main) && action == EAT && !is_all_meals_done(philo->main))
        printf("%ld %d has eaten\n", get_time_ms(), philo->id);
    else if (action == DEAD && !philo->main->all_meals)
        printf("%ld %d died\n", get_time_ms(), philo->id);
    else if (!is_simulation_dead(philo->main) && action == FORK && !is_all_meals_done(philo->main))
        printf("%ld %d has taken a fork\n",get_time_ms(), philo->id);
    else if (!(philo->main->dead) && action == SLEEP && !philo->main->all_meals)
        printf("%ld %d is sleeping\n",get_time_ms(),  philo->id);
    else if (!(philo->main->dead) && action == THINK && !philo->main->all_meals)
        printf("%ld %d is thinking\n", get_time_ms(), philo->id);
    pthread_mutex_unlock(&(philo->main->mute_print));
}*/


void    ft_eat_alone(t_philos *philo)
{
    pthread_mutex_lock(&philo->r_fork);
    ft_print_actions(philo, philo->main->time, FORK);
    usleep(philo->main->time_to_die);
    pthread_mutex_lock(&philo->main->mute_print);
    printf("%ld %d died\n", get_time_ms(), philo->id);
    pthread_mutex_unlock(&philo->main->mute_print);
    pthread_mutex_lock(&philo->main->mute_main);
    philo->main->dead = true;
    pthread_mutex_unlock(&philo->main->mute_main);
    pthread_mutex_unlock(&philo->r_fork);
}

void    ft_eat(t_philos *philo)
{
    if (philo->main->num_philos == 1)
    {
        ft_eat_alone(philo);
        return ;
    }
    if (!((philo->last_meal + philo->main->time_to_eat) * 0.5 > get_time_ms()))
	    	usleep(100);
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->r_fork);
        ft_print_actions(philo, philo->main->time, FORK);
        pthread_mutex_lock(philo->l_fork);
        ft_print_actions(philo, philo->main->time, FORK);
    }
    else
    {
        pthread_mutex_lock(philo->l_fork);
        ft_print_actions(philo, philo->main->time, FORK);
        pthread_mutex_lock(&philo->r_fork);
        ft_print_actions(philo, philo->main->time, FORK);
    }
    pthread_mutex_lock(&philo->eat);
    philo->last_meal = get_time_ms();
    philo->num_meal++;
    pthread_mutex_unlock(&philo->eat);
    ft_print_actions(philo, philo->main->time, EAT);
    ft_usleep(philo->main->time_to_eat);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(&philo->r_fork);
}

int is_dead(t_philos *philo)
{
    long	die;

    pthread_mutex_lock(&philo->eat);
    die = get_time_ms() - philo->last_meal;
    pthread_mutex_unlock(&philo->eat);
    if (die > philo->main->time_to_die)
    {
        pthread_mutex_lock(&philo->main->mute_main);
        philo->main->dead = true;
        pthread_mutex_unlock(&philo->main->mute_main);
        ft_print_actions(philo, philo->main->time, DEAD);
        return (0);
    }
    return (1);
}

void    *ft_simulation(void *data)
{
    t_philos *philo;

    philo = data;
    pthread_mutex_lock(&(philo->main->mute_main));
    pthread_mutex_unlock(&(philo->main->mute_main));
    if (philo->id % 2 != 0)
        ft_usleep(philo->main->time_to_eat);
    while (!is_simulation_dead(philo->main) && philo->main->num_meals != philo->num_meal)
    {
        ft_eat(philo);
        ft_print_actions(philo, philo->main->time, SLEEP);
        ft_usleep(philo->main->time_to_sleep);
        ft_print_actions(philo, philo->main->time, THINK);
    }
    return (NULL);
}

static int	check_meal_count(t_philos *philo, int *flag_meals, t_main *table)
{
	pthread_mutex_lock(&philo->eat);
	if (philo->num_meal == table->num_meals)
		(*flag_meals)++;
	pthread_mutex_unlock(&philo->eat);
	pthread_mutex_lock(&table->mute_main);
	if (table->num_philos == *flag_meals)
    {
        pthread_mutex_lock(&philo->eat);
        table->all_meals = true;
        pthread_mutex_unlock(&philo->eat);
		return (pthread_mutex_unlock(&table->mute_main), 1);
    }
	pthread_mutex_unlock(&table->mute_main);
	return (0);
}

static int	check_death(t_philos *philo)
{
	if (!is_dead(philo))
		return (1);
	return (0);
}

void	*monitor(void *data)
{
	t_main	*table;
	int		i;
	int		flag_meals;

	table = (t_main *)data;
	if (table->num_philos == 1)
		return (NULL);
	while (1)
	{
		i = -1;
		flag_meals = 0;
		while (++i < table->num_philos)
		{
			if (check_meal_count(table->philos[i], &flag_meals, table))
				return (NULL);
			if (check_death(table->philos[i]))
				return (NULL);
		}
		usleep(1);
	}
	return (NULL);
}
int ft_init_simulation(t_main *main)
{
    int         i;
    pthread_t	monitor_th;

    i = 0;
    pthread_create(&monitor_th, NULL, monitor, main);
    pthread_mutex_lock(&(main->mute_main));
    while (i < main->num_philos)
    {
        if (pthread_create(&main->philos[i]->thread, NULL, &ft_simulation, main->philos[i]))
            return (printf("Error creating thread\n"), 0);
        i++;
    }
    pthread_mutex_unlock(&(main->mute_main));
    pthread_join(monitor_th, NULL);
    i = 0;
    while (i < main->num_philos)
        pthread_join(main->philos[i++]->thread, NULL);
    return (1);
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
