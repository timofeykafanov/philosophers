/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:16:46 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/25 17:09:45 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define SUCCESS 0
# define ERROR 1

# define ERR_MESS_ARGS			"Error! Usage: %s <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]!\n"
# define ERR_MESS_NUM_DIGITS	"Error! The number of philosophers should \
contain only digits!\n"
# define ERR_MESS_NUMBER		"Error! The number of philosophers should \
be from 1 to 200!\n"
# define ERR_MESS_DIE_DIGITS	"Error! The time_to_die should contain \
only digits!\n"
# define ERR_MESS_DIE			"Error! The time_to_die can not be \
less than 1!\n"
# define ERR_MESS_EAT_DIGITS	"Error! The time_to_eat should contain \
only digits!\n"
# define ERR_MESS_EAT			"Error! The time_to_eat can not be \
less than 1!\n"
# define ERR_MESS_SLEEP_DIGITS	"Error! The time_to_sleep should contain \
only digits!\n"
# define ERR_MESS_SLEEP			"Error! The time_to_sleep can not be less \
than 1!\n"
# define ERR_MESS_MEALS_DIGITS	"Error! The number_of_meals should contain \
only digits!\n"
# define ERR_MESS_MEALS			"Error! The number_of_meals can not be less \
than 1!\n"

typedef struct s_data	t_data;

typedef struct s_philos
{
	t_data	*data;
	int		id;
	int		time_left;
	bool	alive;
	int		meals;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
}	t_philos;

typedef struct s_data
{
	int				thread;
	int				number;
	t_philos		*philos;
	int				time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int				number_of_meals;
	int				timestamp;
	pthread_t		*threads;
	pthread_mutex_t *fork;
}	t_data;

// utils.c

int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
void	ft_bzero(void *ptr, size_t num);

// validate.c

bool	validate_time_to_die(char *time_to_die);
bool	validate_time_to_eat(char *time_to_eat);
bool	validate_time_to_sleep(char *time_to_sleep);
bool	validate_number_of_meals(int argc, char **argv);
bool	validate_args(int argc, char **argv);

// validate_utils.c

bool	contains_inly_digits(char *number);
bool	validate_number(char *number);

#endif // PHILO_H
