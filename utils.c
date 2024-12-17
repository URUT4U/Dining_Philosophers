/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:56:36 by nranna            #+#    #+#             */
/*   Updated: 2024/12/17 00:32:17 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_return(char *error)
{
	printf("%s\n", error);
	return (EXIT_FAILURE);
}

long	gettime(t_time time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (time == SEC)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else if (time == MILSEC)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (time == MICSEC)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else
		return (EXIT_FAILURE);
	return (42);
}

void	smart_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = gettime(MICSEC);
	while (gettime(MICSEC) - start < usec)
	{
		if (simulation_finished(table) == TRUE)
			break ;
		elapsed = gettime(MICSEC) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while (gettime(MICSEC) - start < usec)
				usleep(100);
		}
	}
	return ((void)0);
}

void	write_status(t_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MILSEC) - philo->table->start_time;
	if (get_bool(&philo->philo_mtx, &philo->full) == TRUE)
		return ;
	if (status == DEAD || simulation_finished(philo->table) == FALSE)
	{
		mutex_handler(&philo->table->printer_mtx, LOCK);
		if (status == EAT && !simulation_finished(philo->table))
			printf("%ld %d is eating\n", elapsed, philo->id);
		else if (status == SLEEP && !simulation_finished(philo->table))
			printf("%ld %d is sleeping\n", elapsed, philo->id);
		else if (status == THINK && !simulation_finished(philo->table))
			printf("%ld %d is thinking\n", elapsed, philo->id);
		else if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			&& !simulation_finished(philo->table))
			printf("%ld %d has taken a fork\n", elapsed, philo->id);
		else if (status == DEAD)
			printf("%ld %d died\n", elapsed, philo->id);
		mutex_handler(&philo->table->printer_mtx, UNLOCK);
	}
	return ;
}
