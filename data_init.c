/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:35:00 by nranna            #+#    #+#             */
/*   Updated: 2024/12/17 13:00:37 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_philos(t_table *table);
static void	give_forks(t_philo *philo, t_fork *fork, int i);

void	data_init(t_table *table)
{
	int	i;

	i = 0;
	table->end_flag = FALSE;
	table->all_threads_ready = FALSE;
	table->threads_running = 0;
	table->philo = (t_philo *)malloc(table->philo_amount * sizeof(t_philo));
	table->fork = (t_fork *)malloc(table->philo_amount * sizeof(t_fork));
	mutex_handler(&table->table_mtx, INIT);
	mutex_handler(&table->printer_mtx, INIT);
	while (i < table->philo_amount)
	{
		mutex_handler(&table->fork[i].fork_mtx, INIT);
		table->fork[i].id = i;
		table->fork->destroyed = FALSE;
		i++;
	}
	create_philos(table);
	return ((void)0);
}

static void	create_philos(t_table *table)
{
	int		i;
	t_philo	*phil;

	i = 0;
	while (i < table->philo_amount)
	{
		phil = &table->philo[i];
		phil->id = i + 1;
		phil->meals_counter = 0;
		phil->table = table;
		phil->full = FALSE;
		give_forks(phil, table->fork, i);
		mutex_handler(&phil->philo_mtx, INIT);
		i++;
	}
	return ((void)0);
}

static void	give_forks(t_philo *philo, t_fork *fork, int i)
{
	int	phil_nbr;

	phil_nbr = philo->table->philo_amount;
	if ((philo->id % 2) == 0)
	{
		philo->first_fork = &fork[i];
		philo->second_fork = &fork[(i + 1) % phil_nbr];
	}
	else
	{
		philo->first_fork = &fork[(i + 1) % phil_nbr];
		philo->second_fork = &fork[i];
	}
	return ((void)0);
}
