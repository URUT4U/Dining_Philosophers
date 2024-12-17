/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:03:58 by nranna            #+#    #+#             */
/*   Updated: 2024/12/16 17:13:30 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_handle(pthread_t *trd, void *(*f)(void *), void *data, t_op op)
{
	if (op == CREATE)
	{
		if (pthread_create(trd, NULL, f, data))
			return (error_return("Thread creation failed"));
	}
	else if (op == JOIN)
	{
		if (pthread_join(*trd, NULL))
			return (error_return("Thread join failed"));
	}
	else if (op == DETACH)
	{
		if (pthread_detach(*trd))
			return (error_return("Thread detach failed"));
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
