/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:32:58 by nranna            #+#    #+#             */
/*   Updated: 2024/12/17 12:58:14 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_table(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_amount)
	{
		philo = table->philo + i;
		mutex_handler(&philo->philo_mtx, DESTROY);
		if (philo->first_fork->destroyed == FALSE)
		{
			mutex_handler(&philo->first_fork->fork_mtx, DESTROY);
			philo->first_fork->destroyed = TRUE;
		}
		if (philo->second_fork && philo->second_fork != philo->first_fork
			&& philo->second_fork->destroyed == FALSE)
		{
			mutex_handler(&philo->second_fork->fork_mtx, DESTROY);
			philo->second_fork->destroyed = TRUE;
		}
	}
	mutex_handler(&table->table_mtx, DESTROY);
	mutex_handler(&table->printer_mtx, DESTROY);
	free(table->fork);
	free(table->philo);
	return ((void)0);
}
