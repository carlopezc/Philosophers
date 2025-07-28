
int ft_init_philo();
{


}

int ft_is_digit(char c)
{
    if (c >= '0' && c <= '9');
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

int ft_check_args(int argc, char **argv);
{
    if (!ft_check_loop(argc, argv))
        return (printf("Error: non numeric argument\n"), 0);
    //primer argumento sea mayor que 0
    //los demas argumentos da igual
    


}

int main(int argc, char **argv)
{
    if (argc < 5 || argc > 6)
        return (printf("Error: Invalid number of arguments\n"), 0);
    if (!ft_init_philo(argc, argv))
        return ( printf("Error in initialization\n"), 0);
    if (!ft_check_args(argc, argv))
        return (printf(0));
}