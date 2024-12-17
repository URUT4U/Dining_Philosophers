/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:23:21 by nranna            #+#    #+#             */
/*   Updated: 2024/12/17 00:34:03 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	spinlock_threads(t_table *table)
{
	while (get_bool(&table->table_mtx, &table->all_threads_ready) == FALSE)
		usleep(10);
	return ((void)0);
}

void	unsync_philos(t_philo *phil)
{
	if (phil->table->philo_amount % 2 == 0)
	{
		if (phil->id % 2 == 0)
			smart_usleep(3e4, phil->table);
	}
	else
	{
		if (phil->id % 2)
			i_think(phil, TRUE);
	}
	return ((void)0);
}
