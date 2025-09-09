/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlopez <carlopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:12:11 by carlopez          #+#    #+#             */
/*   Updated: 2025/09/09 16:12:13 by carlopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

long	ft_get_time_ms(void)
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

void	ft_usleep(long ms)
{
	long	start;
	long	now;
	long	remaining;

	start = ft_get_time_ms();
	while (1)
	{
		now = ft_get_time_ms();
		remaining = ms - (now - start);
		if (remaining <= 0)
			break;
		if (remaining > 10)
			usleep(500);  // más eficiente para tiempos largos
		else
			usleep(100);  // más preciso para tramos cortos
	}
}

long	ft_elapsed_time(t_philos *philo)
{
	return (ft_get_time_ms() - philo->main->time_start);
}