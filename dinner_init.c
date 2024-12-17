/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:48:50 by nranna            #+#    #+#             */
/*   Updated: 2024/12/17 12:46:41 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*dinner(void *data);
static void	i_eat(t_philo *phil);

void	dinner_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	if (table->max_meals == 0)
		return ((void)0);
	else if (table->philo_amount == 1)
		thread_handle(&table->philo[0].trd_id, mori, &table->philo[0], CREATE);
	else
	{
		while (++i < table->philo_amount)
		{
			philo = table->philo + i;
			thread_handle(&philo->trd_id, dinner, philo, CREATE);
		}
	}
	thread_handle(&table->waiter, monitor_dinner, table, CREATE);
	table->start_time = gettime(MILSEC);
	set_bool(&table->table_mtx, &table->all_threads_ready, TRUE);
	i = -1;
	while (++i < table->philo_amount)
		thread_handle(&table->philo[i].trd_id, NULL, NULL, JOIN);
	set_bool(&table->table_mtx, &table->end_flag, TRUE);
	thread_handle(&table->waiter, NULL, NULL, JOIN);
}

static void	*dinner(void *data)
{
	t_philo	*phil;

	phil = (t_philo *)data;
	spinlock_threads(phil->table);
	set_long(&phil->philo_mtx, &phil->last_eaten, gettime(MILSEC));
	increase_long(&phil->table->table_mtx, &phil->table->threads_running);
	unsync_philos(phil);
	while (simulation_finished(phil->table) == FALSE)
	{
		if (get_bool(&phil->philo_mtx, &phil->full) == TRUE)
			break ;
		i_eat(phil);
		write_status(SLEEP, phil);
		smart_usleep(phil->table->time_sleep, phil->table);
		i_think(phil, FALSE);
	}
	return (NULL);
}

static void	i_eat(t_philo *phil)
{
	int	i;

	i = 0;
	if (simulation_finished(phil->table) == FALSE)
	{
		mutex_handler(&phil->first_fork->fork_mtx, LOCK);
		write_status(TAKE_FIRST_FORK, phil);
		mutex_handler(&phil->second_fork->fork_mtx, LOCK);
		write_status(TAKE_SECOND_FORK, phil);
		i = phil->meals_counter + 1;
		set_long(&phil->philo_mtx, &phil->meals_counter, i);
		write_status(EAT, phil);
		smart_usleep(phil->table->time_eat, phil->table);
		set_long(&phil->philo_mtx, &phil->last_eaten, gettime(MILSEC));
		if (phil->table->max_meals > 0
			&& phil->meals_counter == phil->table->max_meals)
			set_bool(&phil->philo_mtx, &phil->full, TRUE);
		mutex_handler(&phil->first_fork->fork_mtx, UNLOCK);
		mutex_handler(&phil->second_fork->fork_mtx, UNLOCK);
	}
	return ((void)0);
}

void	i_think(t_philo *phil, int not_bool)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!not_bool)
		write_status(THINK, phil);
	if (phil->table->philo_amount % 2 == 0)
		return ((void)0);
	t_eat = phil->table->time_eat;
	t_sleep = phil->table->time_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	smart_usleep(t_think * 0.42, phil->table);
	return ((void)0);
}
