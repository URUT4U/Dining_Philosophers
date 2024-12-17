/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:54:24 by nranna            #+#    #+#             */
/*   Updated: 2024/12/16 23:54:12 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (parser(&table, argv) == EXIT_FAILURE)
			return (error_return("Parse error, wrong input"));
		data_init(&table);
		dinner_init(&table);
		clean_table(&table);
	}
	else
		return (error_return("Wrong input."));
	return (EXIT_SUCCESS);
}
