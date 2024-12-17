/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:02:38 by nranna            #+#    #+#             */
/*   Updated: 2024/12/16 23:08:49 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int			validate(char **str);
static int			ft_atol(const char *str);

int	parser(t_table *table, char **argv)
{
	if (validate(argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	table->philo_amount = ft_atol(argv[1]);
	table->time_die = ft_atol(argv[2]) * 1e3;
	table->time_eat = ft_atol(argv[3]) * 1e3;
	table->time_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_sleep < 6e4 || table->time_eat < 6e4
		|| table->time_sleep < 6e4)
		return (EXIT_FAILURE);
	if (argv[5])
		table->max_meals = ft_atol(argv[5]);
	else
		table->max_meals = -1;
	return (EXIT_SUCCESS);
}

static int	validate(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] < '0' || str[i][j] > '9')
				return (EXIT_FAILURE);
			j++;
		}
		if (j > 10)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	ft_atol(const char *str)
{
	long	nbr;
	long	i;

	nbr = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			nbr = (nbr * 10) + (str[i] - '0');
			i++;
		}
	}
	return (nbr);
}
