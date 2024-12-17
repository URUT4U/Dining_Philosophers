/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:43:04 by nranna            #+#    #+#             */
/*   Updated: 2024/12/17 12:50:06 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h> //debug
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

typedef struct s_table	t_table;

typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DEAD,
}						t_status;

typedef enum e_time
{
	SEC,
	MILSEC,
	MICSEC,
}						t_time;

typedef enum e_op
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_op;

typedef struct s_fork
{
	int					id;
	int					destroyed;
	pthread_mutex_t		fork_mtx;
}						t_fork;

typedef struct s_philo
{
	int					id;
	int					full;
	long				meals_counter;
	long				last_eaten;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			trd_id;
	t_table				*table;
	pthread_mutex_t		philo_mtx;
}						t_philo;

struct					s_table
{
	long				time_die;
	long				time_eat;
	long				time_sleep;
	long				max_meals;
	long				start_time;
	long				philo_amount;
	long				threads_running;
	int					end_flag;
	int					all_threads_ready;
	t_fork				*fork;
	t_philo				*philo;
	pthread_t			waiter;
	pthread_mutex_t		table_mtx;
	pthread_mutex_t		printer_mtx;
};

int						error_return(char *error);
int						parser(t_table *table, char **argv);
int						thread_handle(pthread_t *trd, void *(*f)(void *),
							void *data, t_op op);
int						simulation_finished(t_table *table);
int						mutex_handler(pthread_mutex_t *mtx, t_op opcode);
void					data_init(t_table *table);
void					dinner_init(t_table *table);

long					get_long(pthread_mutex_t *mtx, long *value);
void					increase_long(pthread_mutex_t *mtx, long *value);
int						get_bool(pthread_mutex_t *mtx, int *not_bool);
void					set_long(pthread_mutex_t *mtx, long *value,
							long new_value);
void					set_bool(pthread_mutex_t *mtx, int *not_bool,
							int value);

void					spinlock_threads(t_table *table);
long					gettime(t_time time);
void					smart_usleep(long usec, t_table *table);
void					write_status(t_status status, t_philo *philo);
int						all_threads_running(pthread_mutex_t *mtx, long *threads,
							long ph_nbr);
void					*monitor_dinner(void *data);
void					*mori(void *data);
void					clean_table(t_table *table);
void					i_think(t_philo *phil, int not_bool);
void					unsync_philos(t_philo *phil);

#endif
