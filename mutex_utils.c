/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:07:12 by nranna            #+#    #+#             */
/*   Updated: 2024/12/16 20:30:39 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *mtx, int *not_bool, int value)
{
	mutex_handler(mtx, LOCK);
	*not_bool = value;
	mutex_handler(mtx, UNLOCK);
}

int	get_bool(pthread_mutex_t *mtx, int *not_bool)
{
	int	value;

	mutex_handler(mtx, LOCK);
	value = *not_bool;
	mutex_handler(mtx, UNLOCK);
	return (value);
}

void	set_long(pthread_mutex_t *mtx, long *value, long new_value)
{
	mutex_handler(mtx, LOCK);
	*value = new_value;
	mutex_handler(mtx, UNLOCK);
}

long	get_long(pthread_mutex_t *mtx, long *value)
{
	long	new_value;

	mutex_handler(mtx, LOCK);
	new_value = *value;
	mutex_handler(mtx, UNLOCK);
	return (new_value);
}

void	increase_long(pthread_mutex_t *mtx, long *value)
{
	mutex_handler(mtx, LOCK);
	(*value)++;
	mutex_handler(mtx, UNLOCK);
}
