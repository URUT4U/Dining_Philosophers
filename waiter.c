/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:13:52 by nranna            #+#    #+#             */
/*   Updated: 2024/12/16 22:56:27 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_died(t_philo *philo);

void	*monitor_dinner(void *data)
{
	t_table	*table;
	long	*trd_run;
	long	ph;
	int		i;

	table = (t_table *)data;
	trd_run = &table->threads_running;
	ph = table->philo_amount;
	while (all_threads_running(&table->table_mtx, trd_run, ph) == FALSE)
		usleep(100);
	while (simulation_finished(table) == FALSE)
	{
		i = 0;
		while (i < table->philo_amount && !simulation_finished(table))
		{
			if (philo_died(table->philo + i) == TRUE)
			{
				set_bool(&table->table_mtx, &table->end_flag, TRUE);
				write_status(DEAD, &table->philo[i]);
			}
			i++;
		}
	}
	return (NULL);
}

int	all_threads_running(pthread_mutex_t *mtx, long *threads, long ph_nbr)
{
	int	ret;

	ret = FALSE;
	mutex_handler(mtx, LOCK);
	if (*threads == ph_nbr)
		ret = TRUE;
	mutex_handler(mtx, UNLOCK);
	return (ret);
}

int	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mtx, &table->end_flag));
}

static int	philo_died(t_philo *philo)
{
	long	elapsd;
	long	t_die;

	if (get_bool(&philo->philo_mtx, &philo->full) == TRUE)
		return (FALSE);
	elapsd = gettime(MILSEC) - get_long(&philo->philo_mtx, &philo->last_eaten);
	t_die = philo->table->time_die / 1e3;
	if (elapsd > t_die)
		return (TRUE);
	return (FALSE);
}

void	*mori(void *data)
{
	t_philo	*loner;

	loner = (t_philo *)data;
	spinlock_threads(loner->table);
	set_long(&loner->philo_mtx, &loner->last_eaten, gettime(MILSEC));
	increase_long(&loner->table->table_mtx, &loner->table->threads_running);
	write_status(TAKE_FIRST_FORK, loner);
	while (!simulation_finished(loner->table))
		usleep(200);
	return (NULL);
}
