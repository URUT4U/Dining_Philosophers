/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:43:53 by nranna            #+#    #+#             */
/*   Updated: 2024/12/16 23:10:36 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	mtx_perror(int status, t_op opcode);

int	mutex_handler(pthread_mutex_t *mtx, t_op opcode)
{
	if (opcode == LOCK)
		return (mtx_perror(pthread_mutex_lock(mtx), opcode));
	else if (opcode == UNLOCK)
		return (mtx_perror(pthread_mutex_unlock(mtx), opcode));
	else if (opcode == INIT)
		return (mtx_perror(pthread_mutex_init(mtx, NULL), opcode));
	else if (opcode == DESTROY)
		return (mtx_perror(pthread_mutex_destroy(mtx), opcode));
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*DEBUG*/
static int	mtx_perror(int status, t_op opcode)
{
	if (status == 0)
		return (EXIT_SUCCESS);
	if (status == EINVAL)
	{
		if (opcode == INIT)
			error_return("Mutex initialization failed");
		else if (opcode == DESTROY)
			error_return("Mutex destruction failed");
		else if (opcode == LOCK)
			error_return("Mutex lock failed");
		else if (opcode == UNLOCK)
			error_return("Mutex unlock failed");
	}
	else if (status == EDEADLK)
		error_return("Deadlock detected");
	else if (status == EBUSY)
		error_return("Mutex is locked");
	else
		error_return("Mutex error");
	return (EXIT_FAILURE);
}
